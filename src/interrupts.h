#pragma once

#define CAUSE_STIMER 5

void set_stimer_callback(void *callback);

void setup_s_mode_interrupt();

void enable_s_mode_timer_interrupt();

void clear_timer_pending_bit();
