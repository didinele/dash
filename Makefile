AS=i686-elf-as
CC=i686-elf-g++
LD=i686-elf-gcc
ASFLAGS=-g3
CFLAGS=-c -Isrc/include -ffreestanding -g -Wall -Wextra -fno-exceptions -fno-rtti
LDFLAGS=-T linker.ld -ffreestanding -nostdlib -lgcc -g

OBJECTS=src/kernel.o src/kernel_heap.o src/boot.o
HEADERS=$(wildcard src/*.hpp)

LINK_LIST=$(OBJECTS)

.PHONY: build
build: dash.bin

.PHONY: run
run: build
	qemu-system-i386 -kernel dash.bin

dash.bin: $(LINK_LIST)
	$(LD) $(LDFLAGS) -o $@ $^	

%.o: %.as
	$(AS) $(ASFLAGS) -o $@ $<

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -rf src/*.o dash.bin

.PHONY: format
format:
	clang-format -style=file -verbose -i src/*.cpp src/include/*.hpp
