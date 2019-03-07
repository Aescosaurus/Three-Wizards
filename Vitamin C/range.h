#ifndef RANGE_H
#define RANGE_H

typedef struct
{
	int min;
	int max;
} range_t;

range_t create_range( int min,int max );
int rand_range_val( range_t r );

#endif