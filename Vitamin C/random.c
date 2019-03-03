#include "random.h"
#include <stdlib.h>
#include <time.h>
#include "utils.h"

void random_init()
{
	srand( ( uint )time( NULL ) );
}

float random_range( float min,float max )
{
	// Generate random floating point value 0.0f-1.0f.
	const float rng = ( float )rand() / ( float )RAND_MAX;

	return( ( rng * ( max - min ) ) + min );
}
