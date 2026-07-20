PROJECT = main
CPU ?= cortex-m3
BOARD ?= stm32vldiscovery

ifeq ($(OS),Windows_NT)
RM = cmd /C del /Q /F
else
RM = rm -f
endif

qemu:
	arm-none-eabi-as -mthumb -mcpu=$(CPU) -g -c main.S -o main.o
	arm-none-eabi-ld -Tmap.ld main.o -o main.elf
	arm-none-eabi-objdump -D -S main.elf > main.elf.lst
	qemu-system-arm -S -M $(BOARD) -cpu $(CPU) -nographic -kernel $(PROJECT).elf -gdb tcp::1234

gdb:
	gdb-multiarch -q $(PROJECT).elf -ex "target remote localhost:1234"

clean:
	-$(RM) *.out *.elf *.lst .gdb_history *.debug *.o