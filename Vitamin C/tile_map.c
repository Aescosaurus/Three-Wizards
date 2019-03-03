#include "tile_map.h"

#include <stdio.h>
#include <assert.h>

char* tile_map_data = NULL;

void create_map( const string_t path )
{
	tile_map_data = ( char* )malloc( TILE_COUNT *
		sizeof( char ) );
	load_map( path );
}

void destroy_map()
{
	free( tile_map_data );
	tile_map_data = NULL;
}

void load_map( const string_t path )
{
	FILE* map_file = NULL;
	int data_counter = 0;

	if( fopen_s( &map_file,path,"r" ) != 0 )
	{
		printf( "Failed to load file: %s",path );
		assert( FALSE );
	}

	for( char c = fgetc( map_file );
		c != EOF && data_counter < TILE_COUNT;
		c = fgetc( map_file ) )
	{
		switch( c )
		{
		case tile_empty: case tile_wall: case tile_tower:
		case tile_path: case tile_path_start:
			tile_map_data[data_counter++] = c;
			break;
		case '\n':
			break;
		default: // You will never get this!
			assert( FALSE );
			break;
		}

		assert( data_counter <= TILE_COUNT );
	}

	fclose( map_file );
}

void draw_map()
{
	for( int y = 0; y < N_Y_TILES; ++y )
	{
		for( int x = 0; x < N_X_TILES; ++x )
		{
			color_t col;
			switch( get_tile( x,y ) )
			{
			case '0': col = color_black(); break;
			case '1': col = color_cyan(); break;
			case '2': col = color_gray(); break;
			case '3': col = color_red(); break;
			case '4': col = color_orange(); break;
			case '5': col = color_gray(); break;
			}

			draw_rect( x * TILE_SIZE,y * TILE_SIZE,
				TILE_SIZE,TILE_SIZE,col );
		}
	}
}

char get_tile( int x,int y )
{
	assert( x >= 0 );
	assert( x < N_X_TILES );
	assert( y >= 0 );
	assert( y < N_Y_TILES );
	return( tile_map_data[y * N_X_TILES + x] );
}

bool_t tile_exists( int x,int y )
{
	return( x >= 0 && x < N_X_TILES &&
		y >= 0 && y < N_Y_TILES );
}
