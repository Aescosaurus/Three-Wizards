#include "game.h"
#include "tile_map.h"
#include "enemy_handler.h"
#include "frame_timer.h"
#include "tower_handler.h"
#include "surface.h"

// ---------------User Variables Go Here---------------- //
surface_t test_surf;
// ----------------------------------------------------- //

void initialize_game()
{
	frame_timer_init();
	create_map( "Maps/Map1.txt" );
	enemy_handler_init();
	tower_handler_init();

	test_surf = surface_create( "Images/Test.bmp" );
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

	draw_sprite( 15,15,&test_surf );
}

void destruct_game()
{
	destroy_map();
	enemy_handler_destroy();
	tower_handler_destroy();
	surface_destroy( &test_surf );
}
