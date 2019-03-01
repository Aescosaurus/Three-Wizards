#ifndef RECT_H
#define RECT_H

typedef struct
{
	int x;
	int y;
	int width;
	int height;
} rect_t;

rect_t create_rect( int x,int y,int width,int height );

#endif