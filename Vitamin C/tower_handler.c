#include "tower_handler.h"
#include "vector.h"
#include "tile_map.h"
#include "utils.h"
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
	preview_tower->pos = mouse_get_pos();
}

void tower_handler_draw()
{
	// for i in towers draw each tower

	draw_tower( preview_tower );
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

void draw_tower( tower_t* t )
{
	draw_rect( ( int )t->pos.x,( int )t->pos.y,
		TILE_SIZE,TILE_SIZE,t->draw_col );
}
