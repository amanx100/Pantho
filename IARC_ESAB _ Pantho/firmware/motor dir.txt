/*
 * m_dir.h
 *
 * Created: 2/15/2015 10:37:45 AM
 *  Author: Aman
 */ 


#ifndef M_DIR_H_
#define M_DIR_H_


void go_forward(void)
{
	PORTB |= (1<<PD0);
	PORTB &= ~(1<<PD1);
	PORTB |= (1<<PD2);
	PORTB &= ~(1<<PD3);
	
	TCCR1B |= (1<<1);
}

void go_backward(void)
{
	PORTB &= ~(1<<PD0);
	PORTB |= (1<<PD1);
	PORTB &= ~(1<<PD2);
	PORTB |= (1<<PD3);
	
	TCCR1B |= (1<<1);
}

void right_rotate(void)
{
	PORTB |= (1<<PD0);
	PORTB &= ~(1<<PD1);
	PORTB &= ~(1<<PD2);
	PORTB |= (1<<PD3);
	
	TCCR1B |= (1<<1);
}

void left_rotate(void)
{
	PORTB &= ~(1<<PD0);
	PORTB |= (1<<PD1);
	PORTB |= (1<<PD2);
	PORTB &= ~(1<<PD3);
	
	TCCR1B |= (1<<1);
}

void stay_stop(void)
{
	PORTB &= ~(1<<PD0);
	PORTB &= ~(1<<PD1);
	PORTB &= ~(1<<PD2);
	PORTB &= ~(1<<PD3);
	
	TCCR1B &= ~(1<<1);
}



#endif /* M_DIR_H_ */