#include "sbi.h"
#include "interrupts.h"
    
struct Callbacks {
    void (*stimer)(void);
} callbacks;

__attribute__((interrupt ("supervisor")))
__attribute__((aligned(4)))
void s_mode_interrupt_handler(void) {
    unsigned long scause;
    asm volatile("csrr %0, scause" : "=r"(scause));
    
    // get bit XLEN-1, which is 1 for interrupts
    unsigned long interrupt = scause >> (sizeof(unsigned long)*8 - 1);
    unsigned long code      = scause & (~0UL >> 1);

    if(!interrupt) return;

    switch(code) {
        case CAUSE_STIMER:
            clear_timer_pending_bit();
            callbacks.stimer();
    }
}

void set_stimer_callback(void *callback) {
    callbacks.stimer = callback;    
}

void setup_s_mode_interrupt() {
    void *handler_ptr = &s_mode_interrupt_handler;
    /*
    * CSRW: CRS Write
    * CSRSI CRS Write Immediate
    * STVEC: S Mode Trap Vector
    * SSTATUS: Supervisor Mode Status Register
    * 2: 10 in binary. Set bit 1, which is SIE (Supervisor Interrupt Enable)
    */
    asm(
        "csrw stvec, %0\n\t"  // Set the interrupt address for S-mode
        "csrsi sstatus, 2"    // Set the S-level interrupt enable flag (SIE)
        :                     // no outputs
        : "r"(handler_ptr)    // inputs
        :                     // nothing clobbered
        );
}

void enable_s_mode_timer_interrupt() {
  /*
   * This uses intermidate register t1, because CSRS only accepts
   * 5-bit immediate, and 32 (100000) needs 6 bits.
   *
   * Bit 5 is STIE: Supervisor Timer Interrupt Enable
   */
  asm(
      "li t1, 32\n\t"   // 32: 100000. Bit 5 = timer interrupt
      "csrs sie, t1\n"  // Timer interrupt enable flag: STIE
      : // no outputs
      : // no inputs
      : "t1" // clobbered
      );
}

void clear_timer_pending_bit() {
  /*
   * Clear bit 5 (Timer interrupt pending) in SIP (Supervisor Interrupt Pending)
   */
  asm(
      "li t0, 32\n\t"
      "csrc sip, t0\n"
      ::: /* Clobbered registers: */ "t0"
      );
}

