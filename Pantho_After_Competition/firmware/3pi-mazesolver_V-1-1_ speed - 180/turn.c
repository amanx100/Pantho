/*
 * Code to perform various types of turns.  The delays here had to be
 * calibrated for the 3pi's motors.
 */

#include <pololu/3pi.h>
#include "follow-segment.h"

void turn(char dir, int speed)
{
	unsigned int sensors[5];
	
	if (dir == 'L')
	{
		set_motors(-80,80);
		while(sensors[0] < 100)
		{
			read_line(sensors,IR_EMITTERS_ON);
			delay_us(10);
		}
		while(sensors[1] < 100)
		{
			read_line(sensors,IR_EMITTERS_ON);
			delay_us(10);
		}
		while(sensors[2] < 100)
		{
			read_line(sensors,IR_EMITTERS_ON);
			delay_us(10);
		}
		while(sensors[3] < 100)
		{
			read_line(sensors,IR_EMITTERS_ON);
			delay_us(10);
		}
		
		follow_segment(speed);
	}
	else if (dir == 'R')
	{
		set_motors(80,-80);
		while(sensors[4] < 100)
		{
			read_line(sensors,IR_EMITTERS_ON);
			delay_us(10);
		}
		while(sensors[3] < 100)
		{
			read_line(sensors,IR_EMITTERS_ON);
			delay_us(10);
		}
		while(sensors[2] < 100)
		{
			read_line(sensors,IR_EMITTERS_ON);
			delay_us(10);
		}
		while(sensors[1] < 100)
		{
			read_line(sensors,IR_EMITTERS_ON);
			delay_us(10);
		}
		follow_segment(speed);
	}
	else if (dir == 'S')
	{
		set_motors(80,80);
	}
	else if (dir == 'U')
	{
		set_motors(80,-80);
		while(sensors[4] < 100)
		{
			read_line(sensors,IR_EMITTERS_ON);
			delay_us(10);
		}
		while(sensors[3] < 100)
		{
			read_line(sensors,IR_EMITTERS_ON);
			delay_us(10);
		}
		while(sensors[2] < 100)
		{
			read_line(sensors,IR_EMITTERS_ON);
			delay_us(10);
		}
		while(sensors[3] < 100)
		{
			read_line(sensors,IR_EMITTERS_ON);
			delay_us(10);
		}
		follow_segment(speed);
	}
	else if (dir == 'D')
	{
		
	}
	

}