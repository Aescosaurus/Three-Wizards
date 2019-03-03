#ifndef RECT_H
#define RECT_H

#include "utils.h"
#include "vec2.h"

typedef struct
{
	float  x;
	float  y;
	float  width;
	float  height;
} rect_t;

rect_t create_rect( float x,float y,
	float width,float height );

bool_t rect_contains_point( const rect_t* r,const vec2_t* v );
bool_t rect_overlaps_point( const rect_t* r,const vec2_t* v );

#endif