#include "surface.h"
#include <Windows.h>
#include <stdio.h>
#include <assert.h>

surface_t surface_create( const string_t file_path )
{
	surface_t temp;
	FILE* bitmap_file = NULL;

	BITMAPFILEHEADER bmp_file_header;
	char* file_header_insert = ( char* )&bmp_file_header;

	BITMAPINFOHEADER bmp_info_header;
	char* info_header_insert = ( char* )&bmp_info_header;

	// We'll fill these later.
	int y_start;
	int y_end;
	int dy;
	int padding;

	// Open file and make sure it worked.
	if( fopen_s( &bitmap_file,file_path,"r" ) != 0 )
	{
		printf( "Failed to load image: %s",file_path );
		assert( FALSE );
	}

	// Fill bitmap file header.
	for( int i = 0; i < sizeof( bmp_file_header ); ++i )
	{
		file_header_insert[i] = fgetc( bitmap_file );
	}

	// Fill bitmap info header.
	for( int i = 0; i < sizeof( bmp_info_header ); ++i )
	{
		info_header_insert[i] = fgetc( bitmap_file );
	}

	assert( bmp_info_header.biBitCount == 24 );
	assert( bmp_info_header.biCompression == BI_RGB );

	temp.width = bmp_info_header.biWidth;

	// Account for reverse row order or whatever.
	if( bmp_info_header.biHeight < 0 )
	{
		temp.height = -bmp_info_header.biHeight;
		y_start = 0;
		y_end = temp.height;
		dy = 1;
	}
	else
	{
		temp.height = bmp_info_header.biHeight;
		y_start = temp.height - 1;
		y_end = -1;
		dy = -1;
	}

	temp.pixels = vector_create( temp.width * temp.height,
		sizeof( color_t ) );

	for( int i = 0; i < temp.width * temp.height; ++i )
	{
		color_t* col = malloc( sizeof( color_t ) );
		*col = color_black();
		vector_add_element( &temp.pixels,col );
	}

	// Go to the right place in the file.
	fseek( bitmap_file,bmp_file_header.bfOffBits,SEEK_SET );

	padding = ( 4 - ( temp.width * 3 ) % 4 ) % 4;

	for( int y = y_start; y != y_end; y += dy )
	{
		for( int x = 0; x < temp.width; ++x )
		{
			surface_put_pixel( &temp,x,y,make_rgb(
				fgetc( bitmap_file ),
				fgetc( bitmap_file ),
				fgetc( bitmap_file ) ) );
		}
		fseek( bitmap_file,padding,SEEK_CUR );
	}

	return( temp );
}

void surface_destroy( surface_t* surf )
{
	vector_delete( &surf->pixels );
}

void surface_put_pixel( surface_t* surf,int x,int y,color_t c )
{
	color_t* pixel = vector_at( &surf->pixels,
		y * surf->width + x );
	*pixel = c;
}

color_t surface_get_pixel( const surface_t * surf,int x,int y )
{
	const color_t* pixel = vector_cat( &surf->pixels,
		y * surf->width + x );
	return( *pixel );
}
