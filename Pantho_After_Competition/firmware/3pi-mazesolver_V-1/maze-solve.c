/*
 * This file contains the maze-solving strategy.
 */

#include <pololu/3pi.h>
#include "follow-segment.h"
#include "turn.h"


void maze_solve(int speed)
{
	unsigned int sensors[5];
	uint16_t destination = 0;
	const int line_th = 400; //minimum 200
	char Right_trigged = 0, Left_trigged = 0, Forward_trigged = 0; 
	
	while(1)
	{
		follow_segment(speed);
		//delay_ms(10);
		
		read_line(sensors,IR_EMITTERS_ON);
	
		///////////////////////////////////////////////////////////////////////////////////////////////////////
		
		if(sensors[0] > line_th)  //left trigging 
		{
			set_motors(speed,speed);  //can be divide by a factor
			destination = 0;
			while ((sensors[0] > line_th) || (sensors[4] > line_th))
			{
				read_line(sensors,IR_EMITTERS_ON);
				delay_us(50);
				if ((sensors[4] > line_th) && (Right_trigged == 0))
				{
					Right_trigged=1;
				}
				if ((sensors[0] > line_th) && (sensors[4] > line_th))
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
			delay_ms(20);  //delay can be changed  //******************************************************
			read_line(sensors,IR_EMITTERS_ON);
			if ((sensors[1] > line_th) || (sensors[2] > line_th) || (sensors[3] > line_th))
			{
				Forward_trigged = 1;
			}
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
		else if (sensors[4] > line_th) //right trigging
		{
			set_motors(speed,speed);  //can be divide by a factor
			destination = 0;
			while ((sensors[0] > line_th) || (sensors[4] > line_th))
			{
				read_line(sensors,IR_EMITTERS_ON);
				delay_us(50);
				if ((sensors[0] > line_th) && (Left_trigged == 0))
				{
					Left_trigged=1;
				}
				if ((sensors[0] > line_th) && (sensors[4] > line_th))
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
			delay_ms(20);  //delay can be changed  //******************************************************
			read_line(sensors,IR_EMITTERS_ON);
			if ((sensors[1] > line_th) || (sensors[2] > line_th) || (sensors[3] > line_th))
			{
				Forward_trigged = 1;
			}
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
		else if ((sensors[1] < (line_th)) && (sensors[2] < (line_th)) && (sensors[3] < (line_th)))//-100
		{
			set_motors(speed,speed);
			//reverse_operation(speed);
			turn('U',speed);
		}
		
		///////////////////////////////////////////////////////////////////////////////////////////////////////
		
	}
}