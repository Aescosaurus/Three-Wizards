#ifndef SPRITE_EFFECT_H
#define SPRITE_EFFECT_H

#include "colors.h"

struct sprite_effect_s;

typedef struct
{
	void( *func )( int,int,color_t,color_t,
		struct sprite_effect_s );
} sprite_effect_func_t;

// There's a good reason to do it this way and it has to do
//  with forward declaration stuff.
struct sprite_effect_s
{
	sprite_effect_func_t func_to_use; // TODO: Rename this!
	color_t col1;
	// color_t col2;
	// int ival1;
	// float fval1;
};
typedef struct sprite_effect_s sprite_effect_t;

sprite_effect_t sprite_effect_copy();
sprite_effect_t sprite_effect_chroma( color_t chroma );

// c_src = surface pixel
// c_dst = screen pixel
void sprite_effect_copy_func( int x,int y,color_t c_src,
	color_t c_dst,sprite_effect_t eff );
void sprite_effect_chroma_func( int x,int y,color_t c_src,
	color_t c_dst,sprite_effect_t eff );

#endif