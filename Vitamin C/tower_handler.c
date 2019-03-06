#include "tower_handler.h"
#include "vector.h"
#include "tile_map.h"
#include "mouse.h"

vector_t tower_vec;
tower_t preview_tower;
bool_t tower_menu_open = FALSE;
vec2_t menu_draw_pos;

void tower_handler_init()
{
	tower_vec = vector_create( 2,sizeof( tower_t ) );
	
	preview_tower = create_snowball_tower();
}

void tower_handler_destroy()
{
	vector_delete( &tower_vec );
}

void tower_handler_update()
{
	if( tower_menu_open )
	{
		// Select tower to place here.
	}
	else
	{
		preview_tower.pos = world_pos_2_tile_pos(
			mouse_get_pos() );

		if( mouse_left_is_pressed() )
		{
			attempt_place_tower( preview_tower );
		}
	}
	
	// Handle open/closing tower select menu.
	if( mouse_right_is_pressed() )
	{
		if( !tower_menu_open )
		{
			tower_menu_open = TRUE;
			menu_draw_pos = mouse_get_pos();
		}
	}
	else
	{
		tower_menu_open = FALSE;
	}
}

void tower_handler_draw()
{
	if( tower_menu_open )
	{
		const int menu_width = TILE_SIZE * 5;
		const int menu_height = TILE_SIZE * 5;
		draw_rect( ( int )menu_draw_pos.x - menu_width / 2,
			( int )menu_draw_pos.y - menu_height / 2,
			menu_width,menu_height,
			color_red() );
	}
	else
	{
		for( int i = 0; i < vector_count( &tower_vec ); ++i )
		{
			const tower_t* t = vector_at( &tower_vec,i );

			draw_tower( t );
		}

		draw_tower( &preview_tower );
		draw_tower_radius( &preview_tower );
	}
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

void draw_tower_radius( const tower_t* t )
{
	const int grid_x = ( int )t->pos.x / TILE_SIZE;
	const int grid_y = ( int )t->pos.y / TILE_SIZE;
	const int rad = ( int )( t->range );
	const int rad_sq = ( int )( t->range * t->range );
	const color_t draw_col = tile_exists( grid_x,grid_y ) &&
		( get_tile( grid_x,grid_y ) == tile_empty )
		? color_green() : color_red();

	for( int y = grid_y - rad; y < grid_y + rad; ++y )
	{
		for( int x = grid_x - rad; x < grid_x + rad; ++x )
		{
			// const vec2_t cur_pos = world_pos_2_tile_pos(
			// 	create_vec2( ( float )x,( float )y ) );
			const int x_diff = x - grid_x;
			const int y_diff = y - grid_y;

			if( x_diff * x_diff + y_diff * y_diff <
				rad_sq && tile_exists( x,y ) )
			{
				draw_rect_alpha( x * TILE_SIZE,
					y * TILE_SIZE,
					TILE_SIZE,TILE_SIZE,
					draw_col,0.2f );
			}
		}
	}
}

vec2_t world_pos_2_tile_pos( vec2_t world_pos )
{
	int x_pos = ( int )world_pos.x;
	int y_pos = ( int )world_pos.y;

	while( x_pos % TILE_SIZE != 0 ) --x_pos;
	while( y_pos % TILE_SIZE != 0 ) --y_pos;

	return( create_vec2( ( float )x_pos,( float )y_pos ) );
}

bool_t tower_menu_is_open()
{
	return( tower_menu_open );
}
