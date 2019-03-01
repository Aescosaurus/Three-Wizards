#include "rect.h"

rect_t create_rect( int x,int y,int width,int height )
{
	rect_t temp;

	temp.x = x;
	temp.y = y;
	temp.width = width;
	temp.height = height;

	return( temp );
}
