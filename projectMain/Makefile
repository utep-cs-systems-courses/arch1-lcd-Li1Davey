# makfile configuration

COMMON_OBJECTS  = main.o buzzer.o switch.o stateMachine.o libLcd.a
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -Os -I../h
LDFLAGS 	= -L/opt/ti/msp430_gcc/include -L../lib

#switch the compiler (for the internal make rules)

CC              = msp430-elf-gcc
AS              = msp430-elf-as
AR              = msp430-elf-ar

all: libLcd.a main.elf 

#additional rules for files
main.elf: ${COMMON_OBJECTS} lightControl-c.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ ../lib/libTimer.a

main-s.elf: ${COMMON_OBJECTS} lightControl-s.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ ../lib/libTimer.a

libLcd.a: font-11x16.o font-5x7.o font-8x12.o lcdutils.o lcddraw.o
	$(AR) crs $@ $^

install: libLcd.a
	mkdir -p ../h ../lib
	mv $^ ../lib
	cp *.h ../h

load: main.elf
	msp430loader.sh  $^

load2: main-s.elf
	msp430loader.sh  $^

clean: $^
	rm -f libLcd.a *.o *.elf



buzzer.o: buzzer.h
switch.o: switch.h stateMachine.h
stateMachine.o: stateMachine.h buzzer.h led.h switch.h sheetMusic.h lcdutils.h lcddraw.h
main.o: buzzer.h led.h switch.h stateMachine.h lcdutils.h lcddraw.h
lightControl-c.o: led.h
lightControl-s.o: led.h

wdInterruptHandler.o: stateMachine.h

lcddraw.o: lcddraw.c lcddraw.h lcdutils.h
lcdutils.o: lcdutils.c lcdutils.h
