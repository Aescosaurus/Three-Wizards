#include "vec2.h"
#include <math.h>
#include <assert.h>

vec2_t create_vec2( float x,float y )
{
	vec2_t temp;
	temp.x = x;
	temp.y = y;
	return( temp );
}

float vec2_get_length( vec2_t v )
{
	return( sqrtf( ( v.x * v.x ) + ( v.y * v.y ) ) );
}

vec2_t vec2_add( vec2_t lhs,vec2_t rhs )
{
	vec2_t temp = lhs;

	temp.x += rhs.x;
	temp.y += rhs.y;

	return( temp );
}

vec2_t vec2_sub( vec2_t lhs,vec2_t rhs )
{
	vec2_t temp = lhs;

	temp.x -= rhs.x;
	temp.y -= rhs.y;

	return( temp );
}

vec2_t vec2_mul( vec2_t lhs,float rhs )
{
	vec2_t temp = lhs;

	temp.x *= rhs;
	temp.y *= rhs;

	return( temp );
}

vec2_t vec2_div( vec2_t lhs,float rhs )
{
	assert( rhs != 0.0f );

	vec2_t temp = lhs;

	temp.x /= rhs;
	temp.y /= rhs;

	return( temp );
}
