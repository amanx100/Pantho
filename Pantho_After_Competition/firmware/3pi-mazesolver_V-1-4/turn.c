/*
 * Code to perform various types of turns.  The delays here had to be
 * calibrated for the 3pi's motors.
 */

#include <pololu/3pi.h>
#include "follow-segment.h"
#include "maze-solve.h"

void turn(char dir, int speed)
{
	uint8_t sensor_data_save = 0x00;
	const signed int speed_break = -230, break_time = 20, zero_time = 20, turn_th=300, edge_th=500, turn_speed = 60;
	unsigned int sensors[5];
	uint16_t align_time = 0, align_time_ld = 5;
	
	if (dir == 'L')
	{
		delay_ms(25);
		set_motors(0,0);
		delay_ms(10);
		set_motors(-200,-200);
		delay_ms(10);
		set_motors(0,0);
		delay_ms(50);
		
		set_motors(-80,80);
		
		while(!(sensor_data_save & 0b10000))
		{
			sensor_data_save = sensor_data_verified();
		}
		while(sensor_data_save & 0b10000)
		{
			sensor_data_save = sensor_data_verified();
		}
		while(!(sensor_data_save & 0b00010))
		{
			sensor_data_save = sensor_data_verified();
		}
		
		set_motors(0,0);
		delay_ms(30);
		set_motors(100,-100);
		delay_ms(10);
		set_motors(0,0);
		delay_ms(50);
		//follow_segment(80);
		//follow_segment(120);
		//set_motors(speed,speed);
	}
	else if (dir == 'R')
	{
		delay_ms(25);
		set_motors(0,0);
		delay_ms(10);
		set_motors(-200,-200);
		delay_ms(10);
		set_motors(0,0);
		delay_ms(50);
		
		set_motors(80,-80);
		
		while(!(sensor_data_save & 0b00001))
		{
			sensor_data_save = sensor_data_verified();
		}
		while(sensor_data_save & 0b00001)
		{
			sensor_data_save = sensor_data_verified();
		}
		while(!(sensor_data_save & 0b01000))
		{
			sensor_data_save = sensor_data_verified();
		}
		set_motors(0,0);
		delay_ms(30);
		set_motors(100,-100);
		delay_ms(10);
		set_motors(0,0);
		delay_ms(50);
		//follow_segment(80);
		//follow_segment(120);
		//set_motors(speed,speed);

	}
	else if (dir == 'S')
	{
		delay_ms(25);
		set_motors(0,0);
		delay_ms(10);
		set_motors(-200,-200);
		delay_ms(10);
		set_motors(0,0);
		delay_ms(50);
	}
	else if (dir == 'U')
	{
		delay_ms(25);
		set_motors(0,0);
		delay_ms(10);
		set_motors(-200,-200);
		delay_ms(10);
		set_motors(0,0);
		delay_ms(50);
		
		set_motors(-60,60);
		
		while(!(sensor_data_save & 0b10000))
		{
			sensor_data_save = sensor_data_verified();
		}
		while(sensor_data_save & 0b10000)
		{
			sensor_data_save = sensor_data_verified();
		}
		while(!(sensor_data_save & 0b00010))
		{
			sensor_data_save = sensor_data_verified();
		}
		
		set_motors(0,0);
		delay_ms(30);
		set_motors(100,-100);
		delay_ms(10);
		set_motors(0,0);
		delay_ms(50);
		//follow_segment(80);
		//follow_segment(120);
		//set_motors(speed,speed);
	}
	else if (dir == 'D')
	{
		
	}
	

}