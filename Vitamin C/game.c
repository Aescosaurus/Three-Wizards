#include "game.h"
#include "tile_map.h"
#include "enemy_handler.h"
#include "frame_timer.h"
#include "tower_handler.h"
#include "codex.h"
#include <assert.h>

// ---------------User Variables Go Here---------------- //

// ----------------------------------------------------- //

void initialize_game()
{
	frame_timer_init();
	codex_init();

	create_map( "Maps/Map1.txt" );
	enemy_handler_init();
	tower_handler_init();
}

void update_model()
{
	float dt = frame_timer_mark();
	if( dt > 1.0f ) dt = 0.0f;

	if( tower_menu_is_open() ) dt = 0.0f;

	enemy_handler_update( dt );
	tower_handler_update( get_enemy_vec(),dt );
}

void compose_frame()
{
	draw_map();
	enemy_handler_draw();
	tower_handler_draw();
}

void destruct_game()
{
	destroy_map();
	enemy_handler_destroy();
	tower_handler_destroy();
	codex_destroy();
}
