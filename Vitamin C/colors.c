#include "colors.h"
#include <assert.h>
#include "random.h"

const SDL_PixelFormat* colors_pixel_format = NULL;

void init_colors( const SDL_PixelFormat* pixel_format )
{
	colors_pixel_format = pixel_format;
}

color_t make_rgb( uchar r,uchar g,uchar b )
{
	assert( r >= 0 );
	assert( g >= 0 );
	assert( b >= 0 );
	assert( r <= 256 );
	assert( g <= 256 );
	assert( b <= 256 );

	return( SDL_MapRGB( colors_pixel_format,r,g,b ) );
}

color_t rand_color()
{
	const uint r = ( uint )random_range( 0.0f,255.0f );
	const uint g = ( uint )random_range( 0.0f,255.0f );
	const uint b = ( uint )random_range( 0.0f,255.0f );

	return( make_rgb( r,g,b ) );
}

int get_r( color_t c )
{
	Uint8 r;
	Uint8 g;
	Uint8 b;
	SDL_GetRGB( c,colors_pixel_format,&r,&g,&b );
	return( ( int )r );
}

int get_g( color_t c )
{
	Uint8 g;
	Uint8 r;
	Uint8 b;
	SDL_GetRGB( c,colors_pixel_format,&r,&g,&b );
	return( ( int )g );
}

int get_b( color_t c )
{
	Uint8 b;
	Uint8 r;
	Uint8 g;
	SDL_GetRGB( c,colors_pixel_format,&r,&g,&b );
	return( ( int )b );
}

color_t color_white()
{
	return( make_rgb( 255,255,255 ) );
}

color_t color_black()
{
	return( make_rgb( 0,0,0 ) );
}

color_t color_gray()
{
	return( make_rgb( 127,127,127 ) );
}

color_t color_light_gray()
{
	return( make_rgb( 191,191,191 ) );
}

color_t color_dark_gray()
{
	return( make_rgb( 63,63,63 ) );
}

color_t color_red()
{
	return( make_rgb( 255,0,0 ) );
}

color_t color_orange()
{
	return( make_rgb( 255,127,0 ) );
}

color_t color_yellow()
{
	return( make_rgb( 255,255,0 ) );
}

color_t color_green()
{
	return( make_rgb( 0,255,0 ) );
}

color_t color_cyan()
{
	return( make_rgb( 0,255,255 ) );
}

color_t color_blue()
{
	return( make_rgb( 0,0,255 ) );
}

color_t color_magenta()
{
	return( make_rgb( 255,0,255 ) );
}
