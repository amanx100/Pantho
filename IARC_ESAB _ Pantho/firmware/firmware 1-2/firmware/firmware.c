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
//#include "myusart.h"
//#include <math.h>
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
	uint8_t sn_data_1=0;
sn_dt:
	sn_data_1 = PINC;

		if ( (~sn_data_1) & 0b10000001)
		{
			goto sn_dt;
		}
		else
		{
			return (sn_data_1 & 0b01111110);
		}
}

void turn_U(uint16_t speed)
{
	_delay_ms(250);
	stay_stop();
	_delay_ms(50);
	set_speed_R(speed + 40); //40
	set_speed_L(speed + 60); //70
	left_rotate();
	_delay_ms(150);
	set_speed_R(speed -25); //40
	set_speed_L(speed); //70
	//set_speed_RL(speed-25);
	while((sensor_data() & (3<<5)) != (3<<5));
	while((sensor_data() & (3<<4)) != (3<<4));
	//while(sensor_data() != (3<<3));
	stay_stop();
	_delay_ms(50);
	set_speed_RL(speed);
	go_forward();
}

void turn_left(uint16_t speed)
{
	stay_stop();
	_delay_ms(50);
	set_speed_R(speed + 20); //40
	set_speed_L(speed + 30); //70
	left_rotate();
	_delay_ms(70);
	set_speed_R(speed -25); //40
	set_speed_L(speed); //70
	while((sensor_data() & (3<<5)) != (3<<5));
	while((sensor_data() & (3<<4)) != (3<<4));
	//while(sensor_data() != (3<<3));
	stay_stop();
	_delay_ms(50);
	set_speed_RL(speed);
	go_forward();
}

void turn_right(uint16_t speed)
{
	stay_stop();
	_delay_ms(50);
	set_speed_R(speed + 30); //40
	set_speed_L(speed + 20); //70
	right_rotate();
	_delay_ms(70);
	set_speed_R(speed); //40
	set_speed_L(speed - 35); //70
	while((sensor_data() & (3<<1)) != (3<<1));
	while((sensor_data() & (3<<2)) != (3<<2));
	//while(sensor_data() != (3<<3));
	stay_stop();
	_delay_ms(50);
	set_speed_RL(speed);
	go_forward();
}


// ********************************************************************************************************************************
// main function is started from here *********************************************************************************************
// ********************************************************************************************************************************

int main(void)
{
	uint16_t speed=325;
	uint8_t sensor_data_hold=0, sensor_data_temp=0;//, speed_grad_count=0;
	
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
			set_speed_R(speed - 175);  //previously 150
		}
		else if ((sensor_data_hold & (1<<4)) == (1<<4))
		{
			set_speed_L(speed - 175);  //previously 150
		}
		// end line follow
		
		
		if (sensor_data_hold == (63<<1))	// right and left both trig // T shape trig
		{
T_point:
			set_speed_RL(speed);
			while(1)
			{
				_delay_ms(40);
				sensor_data_temp = sensor_data();

					if ((sensor_data_temp == (3<<2)) || (sensor_data_temp == (3<<3)) || (sensor_data_temp == (3<<4)) || (sensor_data_temp == 0x00)) // previously (sensor_data_temp == 0x00)
					{
						//update path data
						turn_left(speed);
						break;
					}
					else
					{
						_delay_ms(40);
						sensor_data_temp = sensor_data();
						if (sensor_data_temp == (63<<1))
						{
							stay_stop();
						}
						else
						{
							go_backward();
							_delay_ms(100);
							turn_left(speed);
						}
						//update path data
						break;
					}			
			}
		}
		
		else if ((sensor_data_hold == (7<<4)) || (sensor_data_hold == (15<<3)) || (sensor_data_hold == (31<<2)))	//left turn trig  //can be use else if later
		{
			_delay_ms(60);  //pass 0.5 cm
			sensor_data_hold = sensor_data();
			if ((sensor_data_hold == (7<<4)) || (sensor_data_hold == (15<<3)) || (sensor_data_hold == (31<<2)))
			{
				//speed = 300;
				set_speed_RL(speed);  // this line is mandatory do not forget it
				while(1)
				{
					sensor_data_temp = sensor_data();
					
					if (!(sensor_data_temp & (1<<6)))
					{
						//update path data
						turn_left(speed);
						break;
					}
				}
			}
			else
			{
				goto T_point;
			}
		}
		
		else if ((sensor_data_hold == (7<<1)) || (sensor_data_hold == (15<<1)) || (sensor_data_hold == (31<<1)))	//right turn trig //else if later
		{
			_delay_ms(110);  //20 for pass 0.5 cm
			sensor_data_hold = sensor_data();
			if ((sensor_data_hold == (7<<1)) || (sensor_data_hold == (15<<1)) || (sensor_data_hold == (31<<1)))
			{
				set_speed_RL(speed);  // this line is mandatory do not forget it
				while(1)
				{
					sensor_data_temp = sensor_data();
					
					if (!(sensor_data_temp & (1<<1)))
					{
						//update path data
						_delay_ms(30); // 35 is not bad
						sensor_data_temp = sensor_data();
						if (sensor_data_temp == 0x00)
						{
							//update path data
							turn_right(speed);
							break;
						}
						else if ((sensor_data_temp == (3<<2)) || (sensor_data_temp == (3<<3)) || (sensor_data_temp == (3<<4)))
						{
							//update path data
							break;
						}
					}
				}
			}
			else
			{
				goto T_point;
			}
		}
		
		else if (sensor_data_hold == 0x00)
		{
			// update data
			turn_U(speed);
		}
    }
}