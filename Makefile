

#compiler
CC = avr-gcc
OBJCOPY = avr-objcopy

#my project
TARGET = snake
OBJECTS = snake.o uart.o cmd.o

# is going to rebuild them if changed
HEADERS = uart.h cmd.h

#the microcontroller and paramaters
MCU = atmega328p
F_CPU = 16000000LU
BAUD = 9600

TARGET_ARCH = -mmcu=$(MCU)

WERRORS = -Werror=int-conversion
#compiler/linker options
CFLAGS = -g -Wall $(WERRORS) -Os -DF_CPU=$(F_CPU) -DBAUD=$(BAUD) $(TARGET_ARCH)

#targets
all: $(TARGET).elf ;

$(TARGET).elf: $(OBJECTS)
	$(CC) $(TARGET_ARCH) -o $@ $^

%.o: %.c Makefile $(HEADERS)
	$(CC) -c $(CFLAGS) -o $@ $<

flash: $(TARGET).elf
	avrdude -c arduino -P /dev/ttyACM0 -p m328p -U flash:w:$<
