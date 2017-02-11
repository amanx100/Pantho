/*
 * Code to perform various types of turns.  The delays here had to be
 * calibrated for the 3pi's motors.
 */

#include <pololu/3pi.h>
#include "follow-segment.h"

void turn(char dir, int speed)
{
	const signed int speed_break = -230, break_time = 10, zero_time = 20, turn_th=300, edge_th=500, turn_speed = 60;
	unsigned int sensors[5];
	uint16_t align_time = 0, align_time_ld = 5;
	
	if (dir == 'L')
	{
		set_motors(0,0);
		delay_ms(zero_time);
		set_motors(speed_break,speed_break);
		delay_ms(break_time);
		set_motors(0,0);
		delay_ms(break_time);
		
		set_motors(-turn_speed,turn_speed);
		
		while(sensors[0] < edge_th)
		{
			read_line(sensors,IR_EMITTERS_ON);
			delay_us(10);
		}
		while(sensors[0] > edge_th)
		{
			read_line(sensors,IR_EMITTERS_ON);
			delay_us(10);
		}
	}
	else if (dir == 'R')
	{
		set_motors(0,0);
		delay_ms(zero_time);
		set_motors(speed_break,speed_break);
		delay_ms(break_time);
		set_motors(0,0);
		delay_ms(break_time);
		
		set_motors(turn_speed,-turn_speed);
		
		while(sensors[4] < edge_th)
		{
			read_line(sensors,IR_EMITTERS_ON);
			delay_us(10);
		}
		while(sensors[4] > edge_th)
		{
			read_line(sensors,IR_EMITTERS_ON);
			delay_us(10);
		}

	}
	else if (dir == 'S')
	{

	}
	else if (dir == 'U')
	{
		set_motors(0,0);
		delay_ms(zero_time);
		set_motors(speed_break,speed_break);
		delay_ms(break_time);
		set_motors(0,0);
		delay_ms(break_time);
		
		set_motors(turn_speed,-turn_speed);
		
		while(sensors[4] < edge_th)
		{
			read_line(sensors,IR_EMITTERS_ON);
			delay_us(10);
		}
		while(sensors[4] > edge_th)
		{
			read_line(sensors,IR_EMITTERS_ON);
			delay_us(10);
		}
	}
	else if (dir == 'D')
	{
		
	}
	

}