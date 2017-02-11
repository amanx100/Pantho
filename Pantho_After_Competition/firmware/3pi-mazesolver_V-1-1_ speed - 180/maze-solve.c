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
	const signed int line_th = 300, edge_th=500, speed_node = 50, speed_break = -230, break_time = 10, zero_time = 20; //minimum 200
	char Right_trigged = 0, Left_trigged = 0, Forward_trigged = 0; 
	
	
temp_strt:
	while(1)
	{
		follow_segment(speed);
		//delay_ms(10);
		
		read_line(sensors,IR_EMITTERS_ON);
	
		///////////////////////////////////////////////////////////////////////////////////////////////////////
		
		if(sensors[0] > edge_th)  //left trigging 
		{
			set_motors(speed_node,speed_node);  //can be divide by a factor
			destination = 0;
			while ((sensors[0] > edge_th) || (sensors[4] > edge_th))
			{
				read_line(sensors,IR_EMITTERS_ON);
				delay_us(50);
				if ((sensors[4] > edge_th) && (Right_trigged == 0))
				{
					Right_trigged=1;
				}
				if ((sensors[0] > edge_th) && (sensors[4] > edge_th))
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
			read_line(sensors,IR_EMITTERS_ON);
			if (sensors[2] > line_th)
			{
				Forward_trigged = 1;
			}
			//temporary pgm
			set_motors(0,0);
			delay_ms(zero_time);
			set_motors(speed_break,speed_break);
			delay_ms(break_time);
			set_motors(0,0);
			clear();
			lcd_goto_xy(0,1);
			print_character('1');
			lcd_goto_xy(1,1);
			if (Forward_trigged) print_character('1');
			else print_character('0');
			lcd_goto_xy(2,1);
			if (Right_trigged) print_character('1');
			else print_character('0');
			
			//set_motors(-speed,-speed);
			//delay_ms(10);
			
			while(!button_is_pressed(BUTTON_B));
			wait_for_button_release(BUTTON_B);
			Right_trigged = 0;
			Forward_trigged = 0;
			delay_ms(1000);
			goto temp_strt;
			
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
		else if (sensors[4] > edge_th) //right trigging
		{
			set_motors(speed_node,speed_node);  //can be divide by a factor
			destination = 0;
			while ((sensors[0] > edge_th) || (sensors[4] > edge_th))
			{
				read_line(sensors,IR_EMITTERS_ON);
				delay_us(50);
				if ((sensors[0] > edge_th) && (Left_trigged == 0))
				{
					Left_trigged=1;
				}
				if ((sensors[0] > edge_th) && (sensors[4] > edge_th))
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
			read_line(sensors,IR_EMITTERS_ON);
			if (sensors[2] > line_th)
			{
				Forward_trigged = 1;
			}
			//temporary pgm
			set_motors(0,0);
			delay_ms(zero_time);
			set_motors(speed_break,speed_break);
			delay_ms(break_time);
			set_motors(0,0);
			clear();
			lcd_goto_xy(0,1);
			if (Left_trigged) print_character('1');
			else print_character('0');
			lcd_goto_xy(1,1);
			if (Forward_trigged) print_character('1');
			else print_character('0');
			lcd_goto_xy(2,1);
			print_character('1');
			
			//set_motors(-speed,-speed);
			//delay_ms(10);
			
			while(!button_is_pressed(BUTTON_B));
			wait_for_button_release(BUTTON_B);
			Left_trigged = 0;
			Forward_trigged = 0;
			delay_ms(1000);
			goto temp_strt;
			
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
			set_motors(0,0);
			delay_ms(zero_time);
			set_motors(speed_break,speed_break);
			delay_ms(break_time);
			set_motors(0,0);
			clear();
			lcd_goto_xy(0,1);
			print_character('0');
			lcd_goto_xy(1,1);
			print_character('0');
			lcd_goto_xy(2,1);
			print_character('0');
			
			while(!button_is_pressed(BUTTON_B));
			wait_for_button_release(BUTTON_B);
			Left_trigged = 0;
			Right_trigged = 0;
			Forward_trigged = 0;
			delay_ms(1000);
			goto temp_strt;
			
			//reverse_operation(speed);
			turn('U',speed);
		}
		
		///////////////////////////////////////////////////////////////////////////////////////////////////////
		
	}
}