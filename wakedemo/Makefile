# makfile configuration
CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/ 

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c

all:wakedemo.elf

#additional rules for files
wakedemo.elf: ${COMMON_OBJECTS} wakedemo.o wdt_handler.o lcdutils.o font-8x12.o font-11x16.o drawKunai.o p1_interrupt_handler.o led.o buzzer.o switches.o stateMachines.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd 

lcdutils.o: lcdutils.c lcdutils.h

drawKunai.o: drawKunai.s drawKunai.h

#drawKunaiC.o: drawKunai.h

stateMachines.o: led.h switches.h

buzzer.o: buzzer.h

load: wakedemo.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf
