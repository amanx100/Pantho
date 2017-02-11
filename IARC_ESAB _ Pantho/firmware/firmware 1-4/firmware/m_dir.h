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
	PORTB = 0x05;
	TCCR1B |= (1<<1);
}

void go_backward(void)
{
	PORTB = 0x0A;
	TCCR1B |= (1<<1);
}

void right_rotate(void)
{
	PORTB = 0x09;
	TCCR1B |= (1<<1);
}

void left_rotate(void)
{
	PORTB = 0x06;
	TCCR1B |= (1<<1);
}

void stay_stop(void)
{
	PORTB = 0x00;
	TCCR1B &= ~(1<<1);
}

#endif /* M_DIR_H_ */