#include "sbi.h"

/*
  Uses OpenSBI to print to the debug console.
  https://github.com/riscv-non-isa/riscv-sbi-doc/blob/master/src/ext-debug-console.adoc
 */
struct SbiRet debug_print(char *message, int len) {
  struct SbiRet return_status;
  
  asm(
      "li a7, 0x4442434E\n\t"               // SBI Extension ID in a7
      "li a6, 0x00\n\t"                     // Function ID in a6
      "li a2, 0\n\t"                        // Argument 3 (message address)
      "mv a1, %2\n\t"                       // Argument 2 (message address)
      "mv a0, %3\n\t"                       // Argument 1 (message size)
      "ecall\n\t"                           // Call into SBI
      "mv %0, a0\n\t"                       // Error code
      "mv %1, a1\n"                         // Status code
      : "=r"(return_status.error), "=r"(return_status.value) // outputs
      : "r"(message), "r"(len)                               // inputs
      : "a0", "a1", "a2", "a6", "a7");                       // clobbered

  return return_status;
}


struct SbiRet set_timer_in_near_future() {
  struct SbiRet return_status;
  
  asm(
      "rdtime t0\n\t"           // t0 = current time
      "li t1, 10000000\n\t"     // t1 = 10000000
      "add a0, t0, t1\n\t"      // a0 = t0 + t1
      "li a7, 0x54494D45\n\t"   // SBI Timer Extension ID
      "li a6, 0x00\n\t"         // Set Timer Function ID
      "ecall\n\t"               // Call into SBI
      "mv %0, a0\n\t"           // Error code
      "mv %1, a1\n"             // Status code
      : "=r"(return_status.error), "=r"(return_status.value)  // outputs
      : // no inputs
      : "a0", "a1", "a6", "a7", "t0", "t1" // clobbered
      );

  return return_status;
}
