/*
 * This file contains the maze-solving strategy.
 */

#include <pololu/3pi.h>
#include "follow-segment.h"
#include <string.h>
#include "turn.h"

char directions_solved[500];	// directions stuck array
uint16_t  node_number = 0;



uint8_t sensor_data(void)
{
	unsigned int sensors[5], edge_th = 400, line_th = 200;
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


void process_u(void)
{
	int i;
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
}

void process_loop(void)
{
	int i;
	for (i=0;directions_solved[i];i++)
	{
		if ((directions_solved[i] == 'l') && (directions_solved[i+1] == 'l') && (directions_solved[i+2] == 'l'))
		{
			directions_solved[i-1] = 'u';
			

			while (directions_solved[i+4])
			{
				directions_solved[i] = directions_solved[i+4];
				i++;
			}
			directions_solved[i] = '\0';
			i=0;
		}
	}
}

void process_array(void)
{
	int i;
	uint16_t length_sln_prev=0;
	
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
	
	while(1)
	{
		length_sln_prev = strlen(directions_solved);
		
		process_u();
		
		//process_loop();
		
		if (length_sln_prev == strlen(directions_solved))
		{
			break;
		}
	}
}


void evaluate_direction(uint16_t speed)
{
	char evaluation = 0;
	evaluation = directions_solved[node_number];
	node_number = node_number + 1;
	
	if (evaluation == 's')
	{
		turn('S',speed);
	}
	else if (evaluation == 'u')
	{
		turn('U',speed);
	}
	else if (evaluation == 'l')
	{
		turn('L',speed);
	}
	else if (evaluation == 'r')
	{
		turn('R',speed);
	}
	else
	{
		set_motors(0,0);
		while(1);
	}
}


void destination_operation(int speed)
{
	directions_solved[node_number] = '\0';
	turn('D',speed);
	process_array();
}


void maze_solve(int speed)
{
	uint16_t destination = 0;
	const signed int speed_node = 100;
	char sensor_data_hold = 0, Right_trigged = 0, Left_trigged = 0, Forward_trigged = 0; 

///////////////////////////////////////////////////////////////////////////////////////////////////////
//****** Explore the path *****************************************************************************
///////////////////////////////////////////////////////////////////////////////////////////////////////

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
					if (destination > 50)   // destination triggering
					{
						destination = 0x00;
						destination_operation(speed);
						goto solv_maze;
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
				directions_solved[node_number] = 'l';
				node_number = node_number + 1;
				turn('L',speed);
				Right_trigged = 0;
				Forward_trigged = 0;
			}
			else if ((Right_trigged == 0) && (Forward_trigged == 1))
			{
				directions_solved[node_number] = 'l';
				node_number = node_number + 1;
				turn('L',speed);
				Right_trigged = 0;
				Forward_trigged = 0;
			}
			else if ((Right_trigged == 1) && (Forward_trigged == 0))
			{
				directions_solved[node_number] = 'l';
				node_number = node_number + 1;
				turn('L',speed);
				Right_trigged = 0;
				Forward_trigged = 0;
			}
			else if ((Right_trigged == 1) && (Forward_trigged == 1))
			{
				directions_solved[node_number] = 'l';
				node_number = node_number + 1;
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
					if (destination > 50)   // destination triggering
					{
						destination = 0x00;
						destination_operation(speed);
						goto solv_maze;
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
				directions_solved[node_number] = 'r';
				node_number = node_number + 1;
				turn('R',speed);
				Left_trigged = 0;
				Forward_trigged = 0;
			}
			else if ((Left_trigged == 0) && (Forward_trigged == 1))
			{
				directions_solved[node_number] = 's';
				node_number = node_number + 1;
				turn('S',speed);
				Left_trigged = 0;
				Forward_trigged = 0;
			}
			else if ((Left_trigged == 1) && (Forward_trigged == 0))
			{
				directions_solved[node_number] = 'l';
				node_number = node_number + 1;
				turn('L',speed);
				Left_trigged = 0;
				Forward_trigged = 0;
			}
			else if ((Left_trigged == 1) && (Forward_trigged == 1))
			{
				directions_solved[node_number] = 'l';
				node_number = node_number + 1;
				turn('L',speed);
				Left_trigged = 0;
				Forward_trigged = 0;
			}
		}
		else if (sensor_data_hold == 0b00000) //-100
		{	
			directions_solved[node_number] = 'u';
			node_number = node_number + 1;
			turn('U',speed);
		}	
	}
	
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//****** Follow the Solved path************************************************************************
	///////////////////////////////////////////////////////////////////////////////////////////////////////

solv_maze:

node_number = 0x00;

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
					if (destination > 50)   // destination triggering
					{
						set_motors(0,0);
						while(1);
					}
				}
			}
			evaluate_direction(speed);
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
					if (destination > 50)   // destination triggering
					{
						set_motors(0,0);
						while(1);
					}
				}
			}
			evaluate_direction(speed);
		}
		else if (sensor_data_hold == 0b00000) //-100
		{	
			evaluate_direction(speed);
		}	
	}
}