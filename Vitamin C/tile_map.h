#ifndef TILE_MAP_H
#define TILE_MAP_H

#include "utils.h"
#include "graphics.h"

void create_map( const string_t path );
void destroy_map();
void load_map( const string_t path );
void draw_map();
char get_tile( int x,int y );

#define TILE_SIZE 30
#define N_X_TILES ( ScreenWidth / TILE_SIZE )
#define N_Y_TILES ( ScreenHeight / TILE_SIZE )
#define TILE_COUNT ( N_X_TILES * N_Y_TILES )

#endif