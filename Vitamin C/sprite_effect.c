#include "sprite_effect.h"
#include "graphics.h"

sprite_effect_t sprite_effect_copy()
{
	sprite_effect_t temp = { 0 };
	temp.func_to_use.func = sprite_effect_copy_func;

	return( temp );
}

sprite_effect_t sprite_effect_chroma( color_t chroma )
{
	sprite_effect_t temp = { 0 };
	temp.func_to_use.func = sprite_effect_chroma_func;

	temp.col1 = chroma;
	return( temp );
}

void sprite_effect_copy_func( int x,int y,color_t c_src,
	color_t c_dst,sprite_effect_t eff )
{
	put_pixel( x,y,c_src );
}

void sprite_effect_chroma_func( int x,int y,color_t c_src,
	color_t c_dst,sprite_effect_t eff )
{
	if( c_src != eff.col1 )
	{
		put_pixel( x,y,c_src );
	}
}
