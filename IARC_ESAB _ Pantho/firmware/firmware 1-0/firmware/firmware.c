/*
 * firmware.c
 *
 * Created: 2/13/2015 11:52:53 PM
 *  Author: Aman
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#include "myusart.h"
#include <util/delay.h>
#include "m_dir.h"
//#include <math.h>
uint32_t wheel_feedback_R=0, wheel_feedback_L=0;
char ch_buffer[40];

ISR(INT0_vect)
{
	wheel_feedback_L = wheel_feedback_L + 1;
	//sprintf(ch_buffer,"left data: %d \n\r",(uint16_t)wheel_feedback_L);
	//usart_putstr(ch_buffer);
}

ISR(INT1_vect)
{
	wheel_feedback_R = wheel_feedback_R + 1;
	//sprintf(ch_buffer,"right data: %d \n\r",(uint16_t)wheel_feedback_R);
	//usart_putstr(ch_buffer);
}


void set_speed_R(uint16_t speed_b)
{
	OCR1B = speed_b;
}

void set_speed_L(uint16_t speed_a)
{
	OCR1A = speed_a;
}

uint8_t sensor_data(void)
{
	uint8_t sn_data_1=0, sn_data_2=0;
sn_dt:
	sn_data_1 = PINC;
	_delay_us(3500);
	sn_data_2 = PINC;
	if (sn_data_1 == sn_data_2)
	{
		_delay_us(3500);
		sn_data_2 = PINC;
		if (sn_data_1 == sn_data_2)
		{
			return sn_data_1;
		}
		else goto sn_dt;
	}
	else goto sn_dt;
}

int main(void)
{

	uint16_t speed=1000;// LS=100, RS=100;
	
	PORTA = 03;
	DDRA = 00;
	
	PORTB=0x00;
	DDRB=0x0F;
	
	PORTC=0xFF;
	DDRC=0x00;
	
	PORTD=0x00;
	DDRD=0x30;
	
	//Timer Counter1 Initialization
	TCCR1A=0xA2;
	TCCR1B=0x18;
	TCNT1=0x0000;
	ICR1H=0x03;
	ICR1L=0xE8; //03E8=1000 in decimal
	OCR1A=speed;
	OCR1B=speed;
	
	usart_init(9600); //USART Initialization
	
	
	//start interrupt settings
	GICR |= (1<<INT0)|(1<<INT1);				// Enable INT0 and INT1
	MCUCSR |= 0x00;
	MCUCR = 0x00;				// Trigger INT2 settings
	MCUCR |= (1<<ISC00)|(1<<ISC10);	//trigger int0 and int1 on any change
	GIFR = (1<<INTF0)|(1<<INTF1);				//Interrupt flag 2 is cleared by writing a logical one into INTF
	sei();							//Global Interrupt enable
	
	
	
	start_tour:
	while (PINA & (1<<PA0));
	_delay_ms(1000);
	go_forward();
	
    while(1)
    {

		if (!((sensor_data()&(1<<3)) && (sensor_data()&(1<<4))))
		{
			if (sensor_data() & (1<<3))
			{
				set_speed_R(800);
				while(!((sensor_data()&(1<<3)) && (sensor_data()&(1<<4))))
				{
					if (sensor_data() == 0x00)
					{
						break;
					}
				}
				set_speed_R(speed);
			}
			else if (sensor_data() & (1<<4))
			{
				set_speed_L(800);
				while(!((sensor_data()&(1<<3)) && (sensor_data()&(1<<4))))
				{
					if (sensor_data() == 0x00)
					{
						break;
					}
				}
				set_speed_L(speed);
			}
			
		}
		
		if (sensor_data() == 0x00)
		{
			break;
		}
    }
	
	stay_stop();
	
	while(1)
	{
		if (sensor_data() == 24)
		{
			goto start_tour;
		}
	}
}