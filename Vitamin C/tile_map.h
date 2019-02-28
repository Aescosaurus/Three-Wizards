#ifndef TILE_MAP_H
#define TILE_MAP_H

#include "utils.h"
#include "graphics.h"

typedef enum
{
	tile_empty = '0',
	tile_wall = '1'
} tile_type;

void create_map( const string_t path );
void destroy_map();
void load_map( const string_t path );
void draw_map();
tile_type get_tile( int x,int y );

#define TILE_SIZE 60
#define N_X_TILES ( ScreenWidth / TILE_SIZE )
#define N_Y_TILES ( ScreenHeight / TILE_SIZE )

#endif