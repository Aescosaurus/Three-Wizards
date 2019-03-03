#include "game.h"
#include "tile_map.h"
#include "vector.h"
#include "enemy_handler.h"

// ---------------User Variables Go Here---------------- //

// ----------------------------------------------------- //

void initialize_game()
{
	create_map( "Maps/Map1.txt" );
	enemy_handler_init();
}

void update_model()
{
	enemy_handler_update();
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
