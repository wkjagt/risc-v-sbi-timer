#include "sbi.h"
#include "interrupts.h"


#define HELLO_TIMER_MSG "Hello from the timer interrupt!\n"
#define MAIN_THREAD_MSG "Main thread still running.\n"

void timer_callback(void) {
    set_timer_in_near_future();
    debug_print(HELLO_TIMER_MSG, sizeof(HELLO_TIMER_MSG));
}

int main() {
    set_stimer_callback(&timer_callback);

    setup_s_mode_interrupt();
    set_timer_in_near_future();
    enable_s_mode_timer_interrupt();

    while (1) {
        debug_print(MAIN_THREAD_MSG, sizeof(MAIN_THREAD_MSG));
        for (int i = 0; i < 300000000; i++); // Simulate a delay
    }
}
