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
#include <string.h>
#include <util/delay.h>
#include "m_dir.h"
#include "myusart.h"

char directions_solved[500];	// directions stuck array
uint16_t  node_number = 0, Time_x2ms = 0;

uint16_t min_up_time = 100; // Set here the minimum time to update or read the stuck array

//**********************************************************************************************************
//  Interrupt Sub rutine  **********************************************************************************
//**********************************************************************************************************

ISR(TIMER0_OVF_vect)
{
	if (Time_x2ms < 500)
	{
		Time_x2ms = Time_x2ms + 1;
	}
}

//**********************************************************************************************************
//   General functions are started from here  **************************************************************
//**********************************************************************************************************

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
sn_dt:
	if ((PIND & (1<<PD2)) && (PIND & (1<<PD3)))
	{
		return PINC;
	}
	else goto sn_dt;
}

void process_array(void)
{
	int i;
	strrev(directions_solved);
	
	for (i=0;directions_solved[i];i++)
	{
		if (directions_solved[i] == 'l')
		{
			directions_solved[i] = 'r';
		}
		else if (directions_solved[i] == 'r')
		{
			directions_solved[i] = 'l';
		}
	}
	
	usart_putstr("\r\rReversed Data: ");
	usart_putstr(directions_solved);
	
	for (i=0;directions_solved[i];i++)
	{
		if (directions_solved[i] == 'u')
		{
			if (directions_solved[i-1] == 'r' && directions_solved[i+1] == 's')
			{
				directions_solved[i-1] = 'l';
			}
			else if (directions_solved[i-1] == 's' && directions_solved[i+1] == 'r')
			{
				directions_solved[i-1] = 'l';
			}
			else if (directions_solved[i-1] == 'l' && directions_solved[i+1] == 'r')
			{
				directions_solved[i-1] = 'u';
			}
			else if (directions_solved[i-1] == 'r' && directions_solved[i+1] == 'r')
			{
				directions_solved[i-1] = 's';
			}
			else if (directions_solved[i-1] == 'r' && directions_solved[i+1] == 'l')
			{
				directions_solved[i-1] = 'u';
			}
			else if (directions_solved[i-1] == 'l' && directions_solved[i+1] == 's')
			{
				directions_solved[i-1] = 'r';
			}
			else if (directions_solved[i-1] == 'l' && directions_solved[i+1] == 'l')
			{
				directions_solved[i-1] = 's';
			}
			else if (directions_solved[i-1] == 's' && directions_solved[i+1] == 'l')
			{
				directions_solved[i-1] = 'r';
			}
			else if (directions_solved[i-1] == 's' && directions_solved[i+1] == 's')
			{
				directions_solved[i-1] = 'u';
			}

			
			while (directions_solved[i+2])
			{
				directions_solved[i] = directions_solved[i+2];
				i++;
			}
			directions_solved[i] = '\0';
			i=0;
		}
	}
	
	usart_putstr("\r\rSolved Data: ");
	usart_putstr(directions_solved);
	usart_putstr("\r\rSolved Data Practical: ");
}

void turn_U(uint16_t speed)
{
	_delay_ms(300);
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
	uint16_t sensor_data_hold;
	stay_stop();
	process_array();
	_delay_ms(1000);
	go_backward();
	set_speed_RL(speed + 200);
	_delay_ms(50);
	set_speed_RL(speed);
	sensor_data_hold = sensor_data();
	while((sensor_data_hold & (1<<6)) || (sensor_data_hold & (1<<1)))
	{
		sensor_data_hold = sensor_data();
	}
	stay_stop();
	_delay_ms(100);
	go_forward();
	set_speed_RL(speed + 200);
	_delay_ms(50);
	//set_speed_RL(speed);
	set_speed_RL(speed+20);
	_delay_ms(400);
	left_rotate();
	set_speed_L(speed + 300); //70
	_delay_ms(50);
	set_speed_R(speed-50); //-50
	set_speed_L(speed+30);
	_delay_ms(100);
	while((sensor_data() & (3<<5)) != 0x00);
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
	set_speed_L(speed + 300);
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
	directions_solved[node_number] = 'l';
	node_number = node_number + 1;
	usart_putchar('l');
}

void right_operation(uint16_t speed)
{
	turn_right(speed);
	directions_solved[node_number] = 'r';
	node_number = node_number + 1;
	usart_putchar('r');
}

void left_forward_operation(uint16_t speed)
{
	turn_left(speed);
	directions_solved[node_number] = 'l';
	node_number = node_number + 1;
	usart_putchar('l');
}

void right_forward_operation(uint16_t speed)
{
	set_speed_RL(speed);
	go_forward();
	directions_solved[node_number] = 's';
	node_number = node_number + 1;
	usart_putchar('s');
}

void left_right_operation(uint16_t speed)
{
	turn_left(speed);
	directions_solved[node_number] = 'l';
	node_number = node_number + 1;
	usart_putchar('l');
}

void left_right_forward_operation(uint16_t speed)
{
	turn_left(speed);
	directions_solved[node_number] = 'l';
	node_number = node_number + 1;
	usart_putchar('l');
}

void reverse_operation(uint16_t speed)
{
	turn_U(speed);
	directions_solved[node_number] = 'u';
	node_number = node_number + 1;
	usart_putchar('u');
}

void destination_operation(uint16_t speed)
{
	directions_solved[node_number] = '\0';
	turn_U_destination(speed);
	usart_putchar('e');
}


void evaluate_direction(char dir,uint16_t speed)
{
	if (Time_x2ms >= min_up_time)
	{
		char evaluation = 0;
		evaluation = directions_solved[node_number];
		node_number = node_number + 1;
		
		usart_putchar(evaluation);
		
		if (evaluation == 's')
		{
			set_speed_RL(speed);
			go_forward();
		}
		else if (evaluation == 'u')
		{
			turn_U(speed);
		}
		else if (evaluation == 'l')
		{
			turn_left(speed);
		}
		else if (evaluation == 'r')
		{
			turn_right(speed);
		}
		else
		{
			stay_stop();
			usart_putstr("\r\rEnd Stuck!!!\r\r\r-------------------------------------------------------\r\r\r\r");
			while(1);
		}
		
		Time_x2ms = 0x00;
	}
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
	
	//Timer Counter0 initialization
	TCCR0=0x03; // 125k Hz at normal top 0xFF
	TCNT0=0x00;
	OCR0=0x00;
	
	//Timer Counter1 Initialization
	TCCR1A=0xA2;
	TCCR1B=0x18;
	TCNT1=0x0000;
	ICR1H=0x03;
	ICR1L=0xE8; //03E8=1000 in decimal
	OCR1A=speed;
	OCR1B=speed;
	
	
	//USART Initialization
	usart_init(9600); 
	usart_putstr("\rI am ready!!\r");
	
	
	// Timer Interrupt Mask register settings
	TIMSK=0x01;
	sei();//global interrupt enable
	
	
	//start_tour:
	while (PINA & (1<<PA0));
	usart_putstr("start tour :)\r\rStuck Data: ");
	_delay_ms(500);
	go_forward();
	set_speed_RL(speed+200);
	_delay_ms(60);
	set_speed_RL(speed);
	sensor_data_hold = sensor_data();
	while ((sensor_data_hold & (1<<6)) || (sensor_data_hold & (1<<1)))
	{
		sensor_data_hold = sensor_data();
	}
	//************************************************************************************************************************
	// main while loop is started from here **********************************************************************************
	//************************************************************************************************************************	
    while(1)  //while loop 1
    {

		sensor_data_hold = sensor_data();  //normally read
		
		// start line follow
		if ((sensor_data_hold & (3<<3)) == (3<<3))
		{
			set_speed_RL(speed);
		}
		else if (sensor_data_hold & 0b00001000)
		{
			set_speed_R(speed - 150);  //previously 150
		}
		else if (sensor_data_hold & 0b00010000)
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
						//while (PINA & (1<<PA0));
						goto solv_maze;
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
						//while (PINA & (1<<PA0));
						goto solv_maze;
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
	
//**********************************************************************************************************
//********* Solving the maze from here *********************************************************************
//**********************************************************************************************************

solv_maze:

	node_number = 0x00;

	sensor_data_hold = sensor_data();  //normally read

	// start line follow
	if ((sensor_data_hold & (3<<3)) == (3<<3))
	{
		set_speed_RL(speed);
	}
	else if (sensor_data_hold & 0b00001111)
	{
		set_speed_R(speed - 200);  //previously 150
	}
	else if (sensor_data_hold & 0b11110000)
	{
		set_speed_L(speed - 200);  //previously 150
	}
	// end line follow
	
	while(1)
	{
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
				if ((sensor_data_hold & 0b01111110) == 0b01111110)
				{
					destination = destination + 1;
					if (destination > 7000)   // destination triggering
					{
						destination = 0x00;
						stay_stop();
						while(1);
					}
				}
				
			}
			_delay_ms(100);  //delay can be changed
			evaluate_direction(1,speed);
		}
		else if ((sensor_data_hold & 0b00001111) == 0b00001111)
		{
			set_speed_RL(speed);
			destination = 0x00;
			while((sensor_data_hold & (1<<6)) || (sensor_data_hold & (1<<1))) // can be changed to 8 sensor system
			{
				_delay_us(50);
				sensor_data_hold = sensor_data();
				if ((sensor_data_hold & 0b01111110) == 0b01111110)
				{
					destination = destination + 1;
					if (destination > 7000)   // destination triggering
					{
						destination = 0x00;
						stay_stop();
						while(1);
					}
				}
			}
			_delay_ms(100);  //delay can be changed
			evaluate_direction(2,speed);
		}
		else if ((sensor_data_hold & 0b01111110) == 0x00)
		{
			evaluate_direction(7,speed);
			//reverse_operation(speed);
		}
	}
}