#include "game.h"
#include "tile_map.h"
#include "mouse.h"

// ---------------User Variables Go Here---------------- //

// ----------------------------------------------------- //

void initialize_game()
{
	create_map( "Maps/Map1.txt" );
}

void update_model()
{
}

void compose_frame()
{
	draw_map();
	if( mouse_left_is_pressed() )
	{
		draw_rect( mouse_get_pos_x(),
			mouse_get_pos_y(),15,15,color_cyan() );
	}
}

void destruct_game()
{
	destroy_map();
}
