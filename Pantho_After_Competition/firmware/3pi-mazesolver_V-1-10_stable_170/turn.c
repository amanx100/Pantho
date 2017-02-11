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
	
	if (dir == 'L')
	{
		delay_ms(17); //25
		set_motors(0,0);
		delay_ms(10);
		set_motors(-200,-200);
		delay_ms(10);
		set_motors(0,0);
		delay_ms(20);
		
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
		delay_ms(10); //30
		set_motors(100,-100);
		delay_ms(10);
		set_motors(0,0);
		delay_ms(20);
		//follow_segment(80);
		//follow_segment(120);
		//set_motors(speed,speed);
	}
	else if (dir == 'R')
	{
		delay_ms(17);  //25
		set_motors(0,0);
		delay_ms(10);
		set_motors(-200,-200);
		delay_ms(10);
		set_motors(0,0);
		delay_ms(20);
		
		set_motors(60,-60);
		
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
		//delay_ms(7); // external 
		set_motors(0,0);
		delay_ms(10);//30
		set_motors(-100,100);
		delay_ms(10);
		set_motors(0,0);
		delay_ms(20);
		//follow_segment(80);
		//follow_segment(120);
		//set_motors(speed,speed);

	}
	else if (dir == 'S')
	{
		//delay_ms(25);
		//set_motors(0,0);
		//delay_ms(10);
		//set_motors(-200,-200);
		//delay_ms(10);
		//set_motors(0,0);
		//delay_ms(50);
		////follow_segment(speed);
	}
	else if (dir == 'U')
	{
		delay_ms(25);
		set_motors(0,0);
		delay_ms(10);
		set_motors(-200,-200);
		delay_ms(10);
		set_motors(0,0);
		delay_ms(20);
		
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
		delay_ms(20);//30
		set_motors(100,-100);
		delay_ms(10);
		set_motors(0,0);
		delay_ms(20);
		//follow_segment(80);
		//follow_segment(120);
		//set_motors(speed,speed);
	}
	else if (dir == 'D')
	{
		uint16_t sensor_data_hold;
		set_motors(0,0);
		delay_ms(50);
		//set_motors(-100,-100);
		//delay_ms(50);
		//set_motors(0,0);
		//process_array();
		delay_ms(500);
		set_motors(-50,-50);
		sensor_data_hold = sensor_data_verified();
		while((sensor_data_hold & 0b10001) == 0b10001)
		{
			sensor_data_hold = sensor_data_verified();
		}
		set_motors(0,0);
		delay_ms(50);
		set_motors(50,50);
		delay_ms(150);
		//set_motors(-100,-100);
		//delay_ms(50);
		set_motors(0,0);
		delay_ms(50);
		set_motors(-60,60);
		delay_ms(50);
		while((sensor_data_verified() & 0b10000) != 0x00);
		while((sensor_data_verified() & 0b10000) != 0b10000);
		while((sensor_data_verified() & 0b00010) != 0b00010);
		////while(sensor_data() & (3<<3)) != (3<<3));
		//delay_ms(20);
		//set_motors(0,0);
		//delay_ms(50);
		
		set_motors(0,0);
		delay_ms(20); //30
		set_motors(100,-100);
		delay_ms(10);
		set_motors(0,0);
		delay_ms(50);
	}
	

}