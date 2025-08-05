#include "header.h"
#include <lpc21xx.h>

void delay_us(unsigned int us){
	unsigned int i;
	for(i=0;i<us*15;i++);
}

void servo_pulse(unsigned int us){
	IOSET0=SERVO_PIN;
	delay_us(us);
	IOCLR0= SERVO_PIN;
	delay_ms(20-(us/1000));
}

void servo_unlock() {
    int i;
	for(i=0;i<50;i++){
		servo_pulse(2000);
	}
}

void servo_lock() {
	int i;
	for(i=0;i<50;i++){
    servo_pulse(1000);
}
	}
