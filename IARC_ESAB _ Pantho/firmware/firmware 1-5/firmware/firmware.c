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
#include <util/delay.h>
#include "m_dir.h"

//**************************************************************************************************************
//  Functions are started from here  ***************************************************************************
//**************************************************************************************************************

void set_speed_R(uint16_t speed_R)
{
	OCR1B = speed_R;
}

void set_speed_L(uint16_t speed_L)
{
	OCR1A = speed_L;
}

void set_speed_RL(uint16_t speed_RL)
{
	set_speed_R(speed_RL);
	set_speed_L(speed_RL);
}

uint8_t sensor_data(void)
{
	return PINC;
}

void turn_U(uint16_t speed)
{
	_delay_ms(200);
	left_rotate();
	set_speed_L(speed + 300); //70
	_delay_ms(50);
	set_speed_R(speed-50); //-50
	set_speed_L(speed+30);
	//_delay_ms(100);
	while((sensor_data() & (3<<5)) != (3<<5));
	while((sensor_data() & (3<<4)) != (3<<4));
	while((sensor_data() & (3<<3)) != (3<<3));
	//while(sensor_data() != (3<<3));
	go_forward();
	set_speed_R(speed);
	set_speed_L(speed +300);
	_delay_ms(50);
	set_speed_RL(speed);
}

void turn_U_destination(uint16_t speed)
{
	stay_stop();
}

void turn_left(uint16_t speed)
{
	left_rotate();
	set_speed_L(speed + 300); //70
	_delay_ms(50);
	set_speed_R(speed-50); //-50
	set_speed_L(speed+30);
	//_delay_ms(100);
	while((sensor_data() & (3<<5)) != (3<<5));
	while((sensor_data() & (3<<4)) != (3<<4));
	//while((sensor_data() & (3<<3)) != (3<<3));
	//while(sensor_data() != (3<<3));
	go_forward();
	set_speed_R(speed);
	set_speed_L(speed +300);
	_delay_ms(50);
	set_speed_RL(speed);
}

void turn_right(uint16_t speed)
{
	right_rotate();
	set_speed_R(speed + 300); //40
	_delay_ms(50);
	set_speed_L(speed-50); //-50
	set_speed_R(speed+30);
	//_delay_ms(100);
	while((sensor_data() & (3<<1)) != (3<<1));
	while((sensor_data() & (3<<2)) != (3<<2));
	//while((sensor_data() & (3<<3)) != (3<<3));
	//while(sensor_data() != (3<<3));
	go_forward();
	set_speed_L(speed);
	set_speed_R(speed + 300);
	_delay_ms(50);
	set_speed_RL(speed);
}

void left_operation(uint16_t speed)
{
	turn_left(speed);
}

void right_operation(uint16_t speed)
{
	turn_right(speed);
}

void left_forward_operation(uint16_t speed)
{
	turn_left(speed);
}

void right_forward_operation(uint16_t speed)
{
	set_speed_RL(speed);
	go_forward();
}

void left_right_operation(uint16_t speed)
{
	turn_left(speed);
}

void left_right_forward_operation(uint16_t speed)
{
	turn_left(speed);
}

void reverse_operation(uint16_t speed)
{
	turn_U(speed);
}

void destination_operation(uint16_t speed)
{
	stay_stop();
	_delay_ms(2000);
	turn_U_destination(speed);
}


// ********************************************************************************************************************************
// main function is started from here *********************************************************************************************
// ********************************************************************************************************************************

int main(void)
{
	uint16_t speed=300, destination=0;
	uint8_t sensor_data_hold=0, Right_trigged=0, Left_trigged=0, Forward_trigged=0;//, speed_grad_count=0;
	
	//port pin initialization
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
	
	//usart_init(9600); //USART Initialization
	
	//start_tour:
	while (PINA & (1<<PA0));
	_delay_ms(1000);
	go_forward();
	set_speed_RL(speed+200);
	_delay_ms(60);
	set_speed_RL(speed);
	//************************************************************************************************************************
	// main while loop is started from here **********************************************************************************
	//************************************************************************************************************************	
    while(1)  //while loop 1
    {
//start_over_while_1:

		sensor_data_hold = sensor_data();  //normally read
		
		// start line follow
		if ((sensor_data_hold & (3<<3)) == (3<<3))
		{
			set_speed_RL(speed);
		}
		else if ((sensor_data_hold & (1<<3)) == (1<<3))
		{
			set_speed_R(speed - 150);  //previously 150
		}
		else if ((sensor_data_hold & (1<<4)) == (1<<4))
		{
			set_speed_L(speed - 150);  //previously 150
		}
		// end line follow
		
		
		if ((sensor_data_hold & 0b11110000) == 0b11110000)
		{
			set_speed_RL(speed);
			destination=0x00;
			while((sensor_data_hold & (1<<6)) || (sensor_data_hold & (1<<1))) // can be changed to 8 sensor system
			{
				_delay_us(50);
				sensor_data_hold = sensor_data();
				if (sensor_data_hold & (1<<1))
				{
					Right_trigged=1;
				}
				if ((sensor_data_hold & 0b01111110) == 0b01111110)
				{
					destination = destination + 1;
					if (destination > 7000)   // destination triggering
					{
						destination = 0x00;
						destination_operation(speed);
						//goto start_test_operation;
					}
				}
				
			}
			_delay_ms(100);  //delay can be changed
			sensor_data_hold = sensor_data();
			if ((sensor_data_hold & 0b01111110))
			{
				Forward_trigged = 1;
			}
			//decide from probable 4 way
			if ((Right_trigged == 0) && (Forward_trigged == 0))
			{
				left_operation(speed);
				Right_trigged = 0;
				Forward_trigged = 0;
			}
			else if ((Right_trigged == 0) && (Forward_trigged == 1))
			{
				left_forward_operation(speed);
				Right_trigged = 0;
				Forward_trigged = 0;
			}
			else if ((Right_trigged == 1) && (Forward_trigged == 0))
			{
				left_right_operation(speed);
				Right_trigged = 0;
				Forward_trigged = 0;
			}
			else if ((Right_trigged == 1) && (Forward_trigged == 1))
			{
				left_right_forward_operation(speed);
				Right_trigged = 0;
				Forward_trigged = 0;
			}
		}
		else if ((sensor_data_hold & 0b00001111) == 0b00001111)
		{
			set_speed_RL(speed);
			destination = 0x00;
			while((sensor_data_hold & (1<<6)) || (sensor_data_hold & (1<<1))) // can be changed to 8 sensor system
			{
				_delay_us(50);
				sensor_data_hold = sensor_data();
				if (sensor_data_hold & (1<<6))  // must change for 8 system
				{
					Left_trigged=1;
				}
				if ((sensor_data_hold & 0b01111110) == 0b01111110)
				{
					destination = destination + 1;
					if (destination > 7000)   // destination triggering
					{
						destination = 0x00;
						destination_operation(speed);
						//goto start_test_operation;
					}
				}
			}
			_delay_ms(100);  //delay can be changed
			sensor_data_hold = sensor_data();
			if ((sensor_data_hold & 0b01111110))
			{
				Forward_trigged = 1;
			}
			//decide from probable 4 way
			if ((Left_trigged == 0) && (Forward_trigged == 0))
			{
				right_operation(speed);
				Left_trigged = 0;
				Forward_trigged = 0;
			}
			else if ((Left_trigged == 0) && (Forward_trigged == 1))
			{
				right_forward_operation(speed);
				Left_trigged = 0;
				Forward_trigged = 0;
			}
			else if ((Left_trigged == 1) && (Forward_trigged == 0))
			{
				left_right_operation(speed);
				Left_trigged = 0;
				Forward_trigged = 0;
			}
			else if ((Left_trigged == 1) && (Forward_trigged == 1))
			{
				left_right_forward_operation(speed);
				Left_trigged = 0;
				Forward_trigged = 0;
			}
		}
		else if ((sensor_data_hold & 0b01111110) == 0x00)
		{
			reverse_operation(speed);
		}
    }
}