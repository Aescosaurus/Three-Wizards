#include "range.h"
#include "random.h"

range_t create_range( int min,int max )
{
	range_t temp;
	temp.min = min;
	temp.max = max;
	return( temp );
}

int rand_range_val( range_t r )
{
	const float rand = random_range( ( float )r.min,
		( float )r.max );

	return( ( int )rand );
}
