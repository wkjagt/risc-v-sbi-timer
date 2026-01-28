#!/usr/bin/zsh

OPENSBI='/home/willem/code/github.com/riscv-software-src/opensbi/build/platform/generic/firmware/fw_dynamic.bin'
KERNEL='build/timer'

qemu-system-riscv64 -machine virt -kernel "$KERNEL" -bios "$OPENSBI" -nographic
