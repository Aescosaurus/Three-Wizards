#include "range.h"

range_t create_range( int min,int max )
{
	range_t temp;
	temp.min = min;
	temp.max = max;
	return( temp );
}
