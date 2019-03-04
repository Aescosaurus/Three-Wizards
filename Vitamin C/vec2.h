#ifndef VEC2_H
#define VEC2_H

typedef struct
{
	float x;
	float y;
} vec2_t;

vec2_t create_vec2( float x,float y );
float vec2_get_length( vec2_t v );
vec2_t vec2_add( vec2_t lhs,vec2_t rhs );
vec2_t vec2_sub( vec2_t lhs,vec2_t rhs );
vec2_t vec2_mul( vec2_t lhs,float rhs );
vec2_t vec2_div( vec2_t lhs,float rhs );

#endif