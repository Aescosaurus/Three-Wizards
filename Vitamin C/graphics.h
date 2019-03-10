#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "window.h"
#include "colors.h"
#include "rect.h"
#include "surface.h"
#include "sprite_effect.h"

// Initialize graphics state.
void init_graphics( SDL_Renderer* rend );
// Call at the beginning of the frame.
void begin_frame();
// Present pixels to the screen.
void end_frame();
// Free memory related to graphics.
void free_graphics();

// Put a pixel with color c on the screen at x, y.
void put_pixel( int x,int y,color_t c );
// Blend pixel onto screen with alpha(0.0f-1.0f).
void put_pixel_alpha( int x,int y,color_t c,float alpha );
void draw_rect( int x,int y,int width,int height,color_t c );
void draw_rect_alpha( int x,int y,int width,int height,
	color_t c,float alpha );
void draw_sprite( int x,int y,const surface_t* surf );
void draw_sprite_2( int x,int y,const surface_t* surf,
	sprite_effect_t eff );

// Get pixel format for color functions.
const SDL_PixelFormat* get_pixel_format();
color_t get_pixel( int x,int y );
const rect_t* get_screen_rect();

#define ScreenWidth ( 1920 / 2 )
#define ScreenHeight ( 1080 / 2 )

#endif