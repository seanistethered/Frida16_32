# Makefile

CC := clang
CF := $(shell find ./cpu2 -name '*.c')
OUTPUT := frida816_emu

all: compile execute clean

compile:
	$(CC) $(CF) -o $(OUTPUT)

execute:
	chmod +x $(OUTPUT)
	./$(OUTPUT)

clean:
	rm $(OUTPUT)
