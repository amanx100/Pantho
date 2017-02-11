/*
 * This file contains the maze-solving strategy.
 */

#include <pololu/3pi.h>
#include "follow-segment.h"
#include "turn.h"

uint8_t sensor_data(void)
{
	unsigned int sensors[5], edge_th = 400, line_th = 400;
	uint8_t sn_dta = 0x00;
	read_line(sensors,IR_EMITTERS_ON);
	if (sensors[0] > edge_th)	sn_dta |= (1<<4);
	else						sn_dta &= ~(1<<4);
	if (sensors[1] > line_th)	sn_dta |= (1<<3);
	else						sn_dta &= ~(1<<3);
	if (sensors[2] > line_th)	sn_dta |= (1<<2);
	else						sn_dta &= ~(1<<2);
	if (sensors[3] > line_th)	sn_dta |= (1<<1);
	else						sn_dta &= ~(1<<1);
	if (sensors[4] > edge_th)	sn_dta |= (1<<0);
	else						sn_dta &= ~(1<<0);
	
	return sn_dta;
}

uint8_t sensor_data_verified(void)
{
	uint8_t snsr_data;
re_data:
	snsr_data = sensor_data();
	delay_us(20);
	if (snsr_data == sensor_data())
	{
		return snsr_data;
	}
	else goto re_data;
}



void maze_solve(int speed)
{
	uint16_t destination = 0;
	const signed int speed_node = 50, speed_break = -230, break_time = 10, zero_time = 20; //minimum 200
	char sensor_data_hold = 0, Right_trigged = 0, Left_trigged = 0, Forward_trigged = 0; 
	temp_strt:
	while(1)
	{
		follow_segment(speed);
		
		sensor_data_hold = sensor_data_verified();
		
		if(sensor_data_hold & 0b10000)  //left trigging 
		{
			set_motors(speed_node,speed_node);  //can be divide by a factor
			destination = 0;
			while (sensor_data_hold & 0b10001)
			{
				sensor_data_hold = sensor_data_verified();

				if ((sensor_data_hold & 0b00001) && (Right_trigged == 0))
				{
					Right_trigged=1;
				}
				if (sensor_data_hold == 0b11111)
				{
					destination = destination + 1;
					if (destination > 5000)   // destination triggering
					{
						destination = 0x00;
						set_motors(0,0);
						while(1);
						//destination_operation(speed);
						//while (PINA & (1<<PA0));
						//goto solv_maze;
					}
				}
			}
			//delay_ms(20);  //delay can be changed  //******************************************************
			sensor_data_hold = sensor_data_verified();
			if (sensor_data_hold & 0b00100)
			{
				Forward_trigged = 1;
			}
			//temporary pgm
			
			//decide from probable 4 way
			if ((Right_trigged == 0) && (Forward_trigged == 0))
			{
				//left_operation(speed);
				turn('L',speed);
				Right_trigged = 0;
				Forward_trigged = 0;
			}
			else if ((Right_trigged == 0) && (Forward_trigged == 1))
			{
				//left_forward_operation(speed);
				turn('L',speed);
				Right_trigged = 0;
				Forward_trigged = 0;
			}
			else if ((Right_trigged == 1) && (Forward_trigged == 0))
			{
				//left_right_operation(speed);
				turn('L',speed);
				Right_trigged = 0;
				Forward_trigged = 0;
			}
			else if ((Right_trigged == 1) && (Forward_trigged == 1))
			{
				//left_right_forward_operation(speed);
				turn('L',speed);
				Right_trigged = 0;
				Forward_trigged = 0;
			}
		}
		else if (sensor_data_hold & 0b00001) //right trigging
		{
			set_motors(speed_node,speed_node);  //can be divide by a factor
			destination = 0;
			while (sensor_data_hold & 0b10001)
			{
				sensor_data_hold = sensor_data_verified();

				if ((sensor_data_hold & 0b10000) && (Left_trigged == 0))
				{
					Left_trigged=1;
				}
				if (sensor_data_hold == 0b11111)
				{
					destination = destination + 1;
					if (destination > 5000)   // destination triggering
					{
						destination = 0x00;
						set_motors(0,0);
						while(1);
						//destination_operation(speed);
						//while (PINA & (1<<PA0));
						//goto solv_maze;
					}
				}
			}
			//delay_ms(20);  //delay can be changed  //******************************************************
			sensor_data_hold = sensor_data_verified();
			if (sensor_data_hold & 0b00100)
			{
				Forward_trigged = 1;
			}
			//temporary pgm
			
			//decide from probable 4 way
			if ((Left_trigged == 0) && (Forward_trigged == 0))
			{
				//right_operation(speed);
				turn('R',speed);
				Left_trigged = 0;
				Forward_trigged = 0;
			}
			else if ((Left_trigged == 0) && (Forward_trigged == 1))
			{
				//right_forward_operation(speed);
				turn('S',speed);
				Left_trigged = 0;
				Forward_trigged = 0;
			}
			else if ((Left_trigged == 1) && (Forward_trigged == 0))
			{
				//left_right_operation(speed);
				turn('L',speed);
				Left_trigged = 0;
				Forward_trigged = 0;
			}
			else if ((Left_trigged == 1) && (Forward_trigged == 1))
			{
				//left_right_forward_operation(speed);
				turn('L',speed);
				Left_trigged = 0;
				Forward_trigged = 0;
			}
		}
		else if (sensor_data_hold == 0b00000) //-100
		{	
			//reverse_operation(speed);
			turn('U',speed);
		}	
	}
}