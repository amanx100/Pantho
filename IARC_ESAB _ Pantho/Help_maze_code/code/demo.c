#include<avr/io.h>
#include<util/delay.h>
int main()
{
	short num = 1;				//variable to keep track of status
	short num2 = 1;
	short counter = 0;
	char directions[10];
	
	short counter123 = 0;				//variable to keep track of elements in directions array
	/* Direction specs:
	 * 'l' => left
	 * 'r' => right
	 * 'u' => U-turn
	 * 's' => straight
	 * 'e' => end of maze!!
	*/
	unsigned char checker;		//to check if a u turn is recorded
	
	//motors as outputs
	DDRD |= (1<<4)|(1<<5)|(1<<6)|(1<<7);
	
	//beeper as output
	DDRC |= (1<<3);
	
					
	/*
 	* Sensor 1 connected to PA0
 	* Sensor 2 connected to PA1
 	* Sensor 3 connected to PA2
 	* Sensor 4 connected to PA3
 	* Sensor 5 connected to PA4
 	*/
	
	
	DDRA &= (~((1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)));
	
	//enable pullup
	
	PORTA |= (1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4);
	
	while(1)
	{
		
		{								//block to assign status to num
			if((PINA & (1<<0)) != 0)
			{
				num &= (~(1<<4));
			}
			else
			{
				num |= (1<<4);
			}


			if((PINA & (1<<1)) != 0)
			{
				num &= (~(1<<3));
			}
			else
			{
				num |= (1<<3);
			}

			if((PINA & (1<<2)) != 0)
			{
				num &= (~(1<<2));
			}
			else
			{
				num |= (1<<2);
			}

			if((PINA & (1<<3)) != 0)
			{
				num &= (~(1<<1));
			}
			else
			{
				num |= (1<<1);
			}

			if((PINA & (1<<4)) != 0)
			{
				num &= (~(1<<0));
			}
			else
			{
				num |= (1<<0);
			}
		}					//end of status assigning block
		

		{  //line following code
			if(num == 4)
			{
				//00100->full speed forward
				PORTD |= (1<<5)|(1<<7);
				PORTD &= (~((1<<4)|(1<<6)));
				_delay_ms(7);
				PORTD = 0x00;
				_delay_ms(5);
			}
			else if((num == 12) || (num == 8))
			{
				//01100 or 01000->take a mild left
				PORTD |= (1<<5);
				PORTD &= (~(1<<4));
				_delay_us(10);
				PORTD = 0x00;
				PORTD |= (1<<7);
				PORTD &= (~(1<<6));
				_delay_us(20);
				PORTD = 0x00;
			}
			else if((num == 2) || (num == 6))
			{
				//00010 or 00110->Take a mild right
				PORTD |= (1<<7);
				PORTD &= (~(1<<6));
				_delay_us(10);
				PORTD = 0x00;
				PORTD |= (1<<5);
				PORTD &= (~(1<<4));
				_delay_us(20);
				PORTD = 0x00;
			}
			
		}	//end of line following code
		
		{		//turns and intersection
			if((num == 28) || (num == 24))
			{
				//left turn
				_delay_ms(1000);
				//go ahead a bit
				PORTD |= (1<<5)|(1<<7);
				PORTD &= (~((1<<4)|(1<<6)));
				_delay_ms(07);
				PORTD = 0x00;
				//now take a turn till middle sensor is on black again...
				while(1)
				{
					PORTD |= (1<<7);
					PORTD &= (~(1<<6));
					_delay_us(10);
					PORTD = 0x00;
					if((PINA & (1<<2)) == 0)
						break;		//break out of while loop
				}		//left turn completed!!!
				//record this turn now....
				directions[counter123] = 'l';
				counter123++;
				
			}
			
			//<!--------------EDIT-------------!>
			
			else if((num == 7) || (num == 3))
			{
				//can be a right only turn or a straight-right intersection
				//move forward a bit
				_delay_ms(1000);
				PORTD |= (1<<5)|(1<<7);
				PORTD &= (~((1<<4)|(1<<6)));
				_delay_ms(25);
				PORTD = 0x00;
				//scan sensors again
				_delay_ms(1000);
		
				if((PINA & (1<<0)) != 0)
					if((PINA & (1<<1)) != 0)
						if((PINA & (1<<2)) != 0)
							if((PINA & (1<<3)) != 0)
								if((PINA & (1<<4)) != 0)
								{
									//was a right only turn
									//move back for 20ms
									PORTD |= (1<<4)|(1<<6);
									PORTD &= (~((1<<5)|(1<<7)));
									_delay_ms(26);
									PORTD = 0x00;
									_delay_ms(1000);
									PORTD |= (1<<5)|(1<<6);
									PORTD &= (~((1<<4)|(1<<7)));
									_delay_ms(7);
									PORTD = 0x00;
							
									//now take a right
							
										while(1)
										{
											PORTD |= (1<<5);
											PORTD &= (~(1<<4));
											_delay_us(10);
											PORTD = 0x00;
											
											if((PINA & (1<<2)) == 0)
											{
												_delay_ms(2);
												break;		//break out of while loop
											}
										}
										directions[counter123] = 'r';
										counter123++;
										

								}
		
				else
				{
					//was a straight only road...
					directions[counter123] = 's';
					counter123++;
					continue;
				}
		
			}			//end of right turn else if
			
			
			//<!------------EDIT::END-----------!>
			
			
			
		}		//turns and intersection end
	
		{		//T-intersection,+ intersection and END
			//$$$$$$$$$$$$$$$$$$$$$$$$$-----EDIT-------$$$$$$$$$$$$$$$$$$$//
			
			if(num == 0)
			{
				//11111->intersection of the above types
				//move forward by a small amount

				PORTD |= (1<<5)|(1<<7);
				PORTD &= (~((1<<4)|(1<<6)));
				_delay_ms(25);

				//re-scan sensors


					{								//block to assign status to num
						if((PINA & (1<<0)) != 0)
						{
							num2 &= (~(1<<4));
						}
						else
						{
							num2 |= (1<<4);
						}


						if((PINA & (1<<1)) != 0)
						{
							num2 &= (~(1<<3));
						}
						else
						{
							num2 |= (1<<3);
						}

						if((PINA & (1<<2)) != 0)
						{
							num2 &= (~(1<<2));
						}
						else
						{
							num2 |= (1<<2);
						}

						if((PINA & (1<<3)) != 0)
						{
							num2 &= (~(1<<1));
						}
						else
						{
							num2 |= (1<<1);
						}

						if((PINA & (1<<4)) != 0)
						{
							num2 &= (~(1<<0));
						}
						else
						{
							num2 |= (1<<0);
						}
					}					//end of status assigning block

					if(num2 == 0)
					{
						//11111->stop....end of maze

						PORTD = 0x00;
						PORTC |= (1<<3);			//buzzer on
						_delay_ms(2000);
						PORTC &= (~(1<<3));			//buzzer off
						
						directions[counter123] = 'e';
						counter123++;
						
						break;
					}		//end of "Maze-end" block
					else
					{
						//take a left as it is a default...
						PORTD |= (1<<4)|(1<<6);
						PORTD &= (~((1<<5)|(1<<7)));
						_delay_ms(18);
						PORTD = 0x00;

						while(1)
						{
							PORTD |= (1<<7);
							PORTD &= (~((1<<4)|(1<<5)|(1<<6)));
							_delay_ms(1);
							PORTD = 0x00;
							_delay_us(10);

							if((PINA & (1<<2))==0)
							{
								break;		//break out of while loop
							}
						}
						directions[counter123] = 'l';
						counter123++;

						//left turn complete
						
					}		//end of else

			}
			
			//$$$$$$$$$$$$$$$$$$$$$$$$$-----EDIT-------$$$$$$$$$$$$$$$$$$$//
		}
	
		{		//condition for U-Turns
			//edit here
			
			if(num == 31)
			{
				counter = counter + 1;
				if((counter == 1)||(counter == 2))
				{
					PORTD |= (1<<5)|(1<<7);
					PORTD &= (~((1<<4)|(1<<6)));
					_delay_ms(1);
					continue;
				}
				directions[counter123] = 'u';
				counter++;
				
				
			}
			
		}
	}
	
	
	//now array copying....
	char path[10];
	{
		short len = counter123-1;
		short m = 0;			//loop tracking variable
		short n = 0;			//assigning variable
		for(;m<=len;m++)
		{
			if(directions[m] != 'u')
			{
				//simply copy over
				path[n] = directions[m];
				n++;
			}
			
			else
			{
				//check for possiblities  lul = s,lus = r,sul = r
				if(path[n-1] == 's')
				{
					//replace by r straight off
					path[n-1] = 'r';
					//don't change n
				}
				else if(path[n-1] == 'l')
				{
					if(directions[m+1] == 'l')
					{
						m = m + 1;
						path[n-1] = 's';
					}
					else if(directions[m+1] == 's')
					{
						m = m + 1;
						path[n-1] = 'r';
					}
				}
			}
		}
	}	//array copying done!!!!!!!!!
	
	//we'll wait for 20 seconds
	_delay_ms(20000);
	
	//and now move along the necessary path.......
	short loopy = 0;
	while(1)
	{
			{								//block to assign status to num
				if((PINA & (1<<0)) != 0)
				{
					num &= (~(1<<4));
				}
				else
				{
					num |= (1<<4);
				}


				if((PINA & (1<<1)) != 0)
				{
					num &= (~(1<<3));
				}
				else
				{
					num |= (1<<3);
				}

				if((PINA & (1<<2)) != 0)
				{
					num &= (~(1<<2));
				}
				else
				{
					num |= (1<<2);
				}

				if((PINA & (1<<3)) != 0)
				{
					num &= (~(1<<1));
				}
				else
				{
					num |= (1<<1);
				}

				if((PINA & (1<<4)) != 0)
				{
					num &= (~(1<<0));
				}
				else
				{
					num |= (1<<0);
				}
			}					//end of status assigning block


			{  //line following code
				if(num == 4)
				{
					//00100->full speed forward
					PORTD |= (1<<5)|(1<<7);
					PORTD &= (~((1<<4)|(1<<6)));
					_delay_ms(7);
					PORTD = 0x00;
					_delay_ms(5);
				}
				else if((num == 12) || (num == 8))
				{
					//01100 or 01000->take a mild left
					PORTD |= (1<<5);
					PORTD &= (~(1<<4));
					_delay_us(10);
					PORTD = 0x00;
					PORTD |= (1<<7);
					PORTD &= (~(1<<6));
					_delay_us(20);
					PORTD = 0x00;
				}
				else if((num == 2) || (num == 6))
				{
					//00010 or 00110->Take a mild right
					PORTD |= (1<<7);
					PORTD &= (~(1<<6));
					_delay_us(10);
					PORTD = 0x00;
					PORTD |= (1<<5);
					PORTD &= (~(1<<4));
					_delay_us(20);
					PORTD = 0x00;
				}

			}	//end of line following code
		
			//now turns and intersections
			if(num == 28 || num == 24 || num ==  7 || num == 3 || num == 0 || num == 31)
			{
				PORTD = 0x00;
				_delay_ms(10);
				//follow path array
				if(path[loopy] == 'l')
				{
					//Take left here
					
					
					_delay_ms(1000);
					//go ahead a bit
					PORTD |= (1<<5)|(1<<7);
					PORTD &= (~((1<<4)|(1<<6)));
					_delay_ms(07);
					PORTD = 0x00;
					//now take a turn till middle sensor is on black again...
					while(1)
					{
						PORTD |= (1<<7);
						PORTD &= (~(1<<6));
						_delay_us(10);
						PORTD = 0x00;
						if((PINA & (1<<2)) == 0)
							break;		//break out of while loop
					}		//left turn completed!!!
					
					loopy++;
				}
				else if(path[loopy] == 'r')
				{
					//take right here
					PORTD |= (1<<5)|(1<<7);
					PORTD &= (~((1<<4)|(1<<6)));
					_delay_ms(07);
					PORTD = 0x00;
					while(1)
					{
						PORTD |= (1<<5);
						PORTD &= (~(1<<4));
						_delay_us(10);
						PORTD = 0x00;
						
						if((PINA & (1<<2)) == 0)
						{
							_delay_ms(2);
							break;		//break out of while loop
						}
					}
					
					
					loopy++;
				}
				else if(path[loopy] == 's')
				{
					//go straight
					PORTD |= (1<<5)|(1<<7);
					PORTD &= (~((1<<4)|(1<<6)));
					_delay_ms(30);
					PORTD = 0x00;
					loopy++;
				}
				else if(loopy == 'e')
				{
					//stop
					PORTD = 0x00;
					loopy++;
					break;
				}
				
			}

	}
}