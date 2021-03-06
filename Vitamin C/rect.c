#include "rect.h"

rect_t create_rect( float x,float y,
	float width,float height )
{
	rect_t temp;

	temp.x = x;
	temp.y = y;
	temp.width = width;
	temp.height = height;

	return( temp );
}

bool_t rect_contains_point( const rect_t* r,const vec2_t* v )
{
	return( v->x > r->x &&
		v->x < r->x + r->width &&
		v->y > r->y &&
		v->y < r->y + r->height );
}

bool_t rect_contains_rect( const rect_t* r1,const rect_t* r2 )
{
	return( r1->x > r2->x &&
		r1->x + r1->width < r2->x + r2->width &&
		r1->y > r2->y &&
		r1->y + r1->height < r2->y + r2->height );
}

bool_t rect_overlaps_point( const rect_t* r,const vec2_t* v )
{
	return( v->x >= r->x &&
		v->x <= r->x + r->width &&
		v->y >= r->y &&
		v->y <= r->y + r->height );
}

bool_t rect_overlaps( const rect_t* r1,const rect_t* r2 )
{
	return( r1->x + r1->width > r2->x &&
		r1->x < r2->x + r2->width &&
		r1->y + r1->height > r2->y &&
		r1->y < r2->y + r2->height );
}

vec2_t rect_get_center( const rect_t* r )
{
	return( create_vec2( r->x + r->width / 2.0f,
		r->y + r->height / 2.0f ) );
}
