#include "game.h"
#include "tile_map.h"

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
}

void destruct_game()
{
	destroy_map();
}
