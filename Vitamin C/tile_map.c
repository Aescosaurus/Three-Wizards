#include "tile_map.h"

#include <stdio.h>
#include <assert.h>

tile_type* tile_map_data = NULL;

void create_map( const string_t path )
{
	tile_map_data = malloc( N_X_TILES * N_Y_TILES * sizeof( tile_type ) );
	load_map( path );
}

void destroy_map()
{
	free( tile_map_data );
}

void load_map( const string_t path )
{
	FILE* map_file = NULL;
	int data_counter = 0;

	free( tile_map_data );

	if( fopen_s( &map_file,path,"r" ) != 0 )
	{
		printf( "Failed to load file: %s",path );
		assert( FALSE );
	}

	for( char c = fgetc( map_file );
		c != EOF;
		c = fgetc( map_file ) )
	{
		switch( c )
		{
		case ( char )tile_empty:
		case ( char )tile_wall:
			tile_map_data[data_counter] = ( tile_type )c;
			break;
		case '\n':
			break;
		default: // You will never get this!
			assert( FALSE );
			break;
		}

		++data_counter;
	}

	fclose( map_file );
}

void draw_map()
{
	for( int y = 0; y < N_Y_TILES; ++y )
	{
		for( int x = 0; x < N_X_TILES; ++x )
		{
			color_t col = ( get_tile( x,y ) == tile_empty )
				? color_black() : color_blue();

			draw_rect( x * TILE_SIZE,y * TILE_SIZE,
				TILE_SIZE,TILE_SIZE,col );
		}
	}
}

tile_type get_tile( int x,int y )
{
	return( tile_map_data[y * N_X_TILES + x] );
}
