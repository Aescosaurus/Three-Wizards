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

// Returns whether r contains v.
bool_t rect_contains_point( const rect_t* r,const vec2_t* v );
// Returns whether r1 is contained by r2.
bool_t rect_contains_rect( const rect_t* r1,const rect_t* r2 );
// Returns whether r overlaps with v.
bool_t rect_overlaps_point( const rect_t* r,const vec2_t* v );
// Returns whether r1 and r2 overlap.
bool_t rect_overlaps( const rect_t* r1,const rect_t* r2 );
// Get the center position of a rectangle(SUPER USEFUL).
vec2_t rect_get_center( const rect_t* r );

#endif