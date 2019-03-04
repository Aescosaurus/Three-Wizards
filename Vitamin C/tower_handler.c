#include "tower_handler.h"
#include "vector.h"
#include "tile_map.h"
#include "mouse.h"

vector_t tower_vec;
tower_t* preview_tower = NULL;

void tower_handler_init()
{
	tower_vec = vector_create( 2,sizeof( tower_t ) );
	
	preview_tower = malloc( sizeof( tower_t ) );
	*preview_tower = create_snowball_tower();
}

void tower_handler_destroy()
{
	vector_delete( &tower_vec );
	
	free( preview_tower );
}

void tower_handler_update()
{
	preview_tower->pos = world_pos_2_tile_pos(
		mouse_get_pos() );

	if( mouse_left_is_pressed() )
	{
		attempt_place_tower( *preview_tower );
	}
}

void tower_handler_draw()
{
	for( int i = 0; i < vector_count( &tower_vec ); ++i )
	{
		const tower_t* t = vector_at( &tower_vec,i );

		draw_tower( t );
	}

	draw_tower( preview_tower );
}

bool_t attempt_place_tower( tower_t t )
{
	bool_t result = FALSE;
	const int tower_x = ( int )t.pos.x / TILE_SIZE;
	const int tower_y = ( int )t.pos.y / TILE_SIZE;

	if( get_tile( tower_x,tower_y ) == tile_empty )
	{
		tower_t* temp = malloc( sizeof( tower_t ) );
		*temp = t;
		vector_add_element( &tower_vec,temp );

		// This spot now contains a tower.
		set_tile( tower_x,tower_y,tile_tower );
		result = TRUE;
	}
	else
	{
		result = FALSE;
	}

	return( result );
}

tower_t create_snowball_tower()
{
	tower_t tow;

	tow.pos = create_vec2( 0.0f,0.0f );
	tow.range = 5;
	tow.magic = magic_water;
	tow.draw_col = color_blue();

	return( tow );
}

void draw_tower( const tower_t* t )
{
	draw_rect( ( int )t->pos.x,( int )t->pos.y,
		TILE_SIZE,TILE_SIZE,t->draw_col );
}

vec2_t world_pos_2_tile_pos( vec2_t world_pos )
{
	int x_pos = ( int )world_pos.x;
	int y_pos = ( int )world_pos.y;

	while( x_pos % TILE_SIZE != 0 ) --x_pos;
	while( y_pos % TILE_SIZE != 0 ) --y_pos;

	return( create_vec2( ( float )x_pos,( float )y_pos ) );
}