#include "graphics.h"
#include <assert.h>

SDL_Renderer* gfx_renderer = NULL;
SDL_Surface* screen_surface = NULL;
rect_t screen_rect_area;

void init_graphics( SDL_Renderer* rend )
{
	gfx_renderer = rend;

	const int r_mask = 0xff000000;
	const int g_mask = 0x00ff0000;
	const int b_mask = 0x0000ff00;
	const int a_mask = 0x000000ff;

	screen_surface = SDL_CreateRGBSurface( 0,
		ScreenWidth,ScreenHeight,32,
		r_mask,g_mask,b_mask,a_mask );

	SDL_LockSurface( screen_surface );

	screen_rect_area = create_rect( 0.0f,0.0f,
		ScreenWidth,ScreenHeight );
}

void begin_frame()
{
	SDL_RenderClear( gfx_renderer );
}

void end_frame()
{
	SDL_Texture* tex = SDL_CreateTextureFromSurface(
		gfx_renderer,screen_surface );

	SDL_RenderCopy( gfx_renderer,tex,NULL,NULL );

	SDL_DestroyTexture( tex );

	SDL_RenderPresent( gfx_renderer );

	// Much better than the old way!
	SDL_FillRect( screen_surface,NULL,make_rgb( 0,0,0 ) );
}

void free_graphics()
{
	SDL_FreeSurface( screen_surface );
}

void put_pixel( int x,int y,color_t c )
{
	assert( x >= 0 );
	assert( y >= 0 );
	assert( x < ScreenWidth );
	assert( y < ScreenHeight );

	Uint8* p = ( Uint8* )screen_surface->pixels +
		y * screen_surface->pitch +
		x * get_pixel_format()->BytesPerPixel;

	*( Uint32* )p = c;
}

void put_pixel_alpha( int x,int y,color_t c,float alpha )
{
	assert( alpha >= 0.0f );
	assert( alpha <= 1.0f );

	const color_t c2 = get_pixel( x,y );
	const float r = ( float )( get_r( c2 ) - get_r( c ) );
	const float g = ( float )( get_g( c2 ) - get_g( c ) );
	const float b = ( float )( get_b( c2 ) - get_b( c ) );
	const color_t blended = make_rgb
	(
		( int )( r * ( 1.0f - alpha ) ) + get_r( c ),
		( int )( g * ( 1.0f - alpha ) ) + get_g( c ),
		( int )( b * ( 1.0f - alpha ) ) + get_b( c )
	);

	put_pixel( x,y,blended );
}

void draw_rect( int x,int y,int width,int height,color_t c )
{
	for( int y_c = y; y_c < y + height; ++y_c )
	{
		for( int x_c = x; x_c < x + width; ++x_c )
		{
			put_pixel( x_c,y_c,c );
		}
	}
}

void draw_rect_alpha( int x,int y,int width,int height,
	color_t c,float alpha )
{
	for( int y_c = y; y_c < y + height; ++y_c )
	{
		for( int x_c = x; x_c < x + width; ++x_c )
		{
			put_pixel_alpha( x_c,y_c,c,alpha );
		}
	}
}

void draw_sprite( int x,int y,surface_t* surf )
{
	for( int y_c = y; y_c < y + surf->height; ++y_c )
	{
		for( int x_c = x; x_c < x + surf->width; ++x_c )
		{
			put_pixel( x_c,y_c,surface_get_pixel( surf,
				x_c - x,y_c - y ) );
		}
	}
}

const SDL_PixelFormat* get_pixel_format()
{
	return( screen_surface->format );
}

color_t get_pixel( int x,int y )
{
	assert( x >= 0 );
	assert( y >= 0 );
	assert( x < ScreenWidth );
	assert( y < ScreenHeight );

	Uint8* p = ( Uint8* )screen_surface->pixels +
		y * screen_surface->pitch +
		x * get_pixel_format()->BytesPerPixel;

	return( *( Uint32* )p );
}

const rect_t* get_screen_rect()
{
	return( &screen_rect_area );
}
