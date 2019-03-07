#include "timer.h"

timer_t create_timer( float max_time )
{
	timer_t temp;
	temp.start = 0.0f;
	temp.max_time = max_time;
	return( temp );
}

void timer_update( timer_t* t,float dt )
{
	t->start += dt;
}

void timer_reset( timer_t* t )
{
	t->start = 0.0f;
}

bool_t timer_is_done( const timer_t* t )
{
	return( t->start >= t->max_time );
}
