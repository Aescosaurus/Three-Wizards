#ifndef TIMER_H
#define TIMER_H

#include "utils.h"

typedef struct
{
	float start;
	float max_time;
} timer_t;

timer_t create_timer( float max_time );

void timer_update( timer_t* t,float dt );
void timer_reset( timer_t* t );

bool_t timer_is_done( const timer_t* t );

#endif