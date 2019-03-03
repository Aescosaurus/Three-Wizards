#include "game.h"
#include "tile_map.h"
#include "vector.h"
#include "enemy_handler.h"
#include "frame_timer.h"
#include <stdio.h>

// ---------------User Variables Go Here---------------- //

// ----------------------------------------------------- //

void initialize_game()
{
	frame_timer_init();
	create_map( "Maps/Map1.txt" );
	enemy_handler_init();
}

void update_model()
{
	const float dt = frame_timer_mark();
	// printf( "%f\n",dt );

	enemy_handler_update( dt );
}

void compose_frame()
{
	draw_map();
	enemy_handler_draw();
}

void destruct_game()
{
	destroy_map();
	enemy_handler_destroy();
}
