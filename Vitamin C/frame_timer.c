#include "frame_timer.h"
#include <time.h>

clock_t frame_timer_last;

void frame_timer_init()
{
	frame_timer_last = clock();
}

float frame_timer_mark()
{
	const clock_t old = frame_timer_last;
	frame_timer_last = clock();
	return( ( ( float )( frame_timer_last - old ) ) /
		1000.0f );
	// return( frame_timer_last - old );
}
