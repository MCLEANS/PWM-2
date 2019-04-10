/*
 * PWM pinLogic.cpp
 *
 * Created: 4/9/2019 5:23:06 PM
 * Author : MCLEANS
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define servo1 PINB0
#define servo2 PINB1
#define servoDirection DDRB
#define servoPort PORTB
#define upperRange 19999
#define lowerRange 800
#define middlePos 13000
#define leftPos 19900
#define rightPos 1000


int main(void)
{	
	servoDirection|=(1<<servo1);
	servoDirection|=(1<<servo2);
	
	//set global interrupts
	
	//set waveform generation mode/PRESCALER(no prescaler)
	TCCR1A|=(1<<WGM11);
	TCCR1B|=(1<<WGM12)|(1<<WGM13)|(1<<CS10);
	TIMSK|=(1<<OCIE1A);
	
	ICR1=19999;
	sei();
	
   
    while (1) 
    {
		if(TCNT1>=lowerRange && TCNT1<=upperRange){
			if(TCNT1>=rightPos && bit_is_set(servoPort,servo1)) servoPort&=~(1<<servo1);
			if(TCNT1>=leftPos && bit_is_set(servoPort,servo2)) servoPort&=~(1<<servo2);
		}
	}
}

ISR(TIMER1_COMPA_vect){
	servoPort|=(1<<servo1);
	servoPort|=(1<<servo2);
}