#ifndef SURFACE_H
#define SURFACE_H

#include "utils.h"
#include "vector.h"
#include "colors.h"

typedef struct
{
	int width;
	int height;
	vector_t pixels;
} surface_t;

surface_t surface_create( const string_t file_path );
void surface_destroy( surface_t* surf );

void surface_put_pixel( surface_t* surf,int x,int y,color_t c );
color_t surface_get_pixel( const surface_t* surf,int x,int y );

#endif