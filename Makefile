CROSS_COMPILE=riscv64-linux-gnu-

timer: build/timer.o build/sbi.o build/boot.o build/interrupts.o timer.ld
	${CROSS_COMPILE}ld -T timer.ld --no-dynamic-linker -static -nostdlib \
		-o build/timer build/timer.o build/sbi.o build/boot.o build/interrupts.o

build/boot.o: boot.s
	${CROSS_COMPILE}as -march=rv64gc -mabi=lp64 -c boot.s -o build/boot.o

build/%.o: src/%.c
	${CROSS_COMPILE}gcc -march=rv64gc -mabi=lp64 -c $< -o $@

clean:
	rm build/*
