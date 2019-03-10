#include "game.h"
#include "tile_map.h"
#include "enemy_handler.h"
#include "frame_timer.h"
#include "tower_handler.h"
#include "ordered_map.h"

// ---------------User Variables Go Here---------------- //
ordered_map_t map;
// ----------------------------------------------------- //

void initialize_game()
{
	frame_timer_init();
	create_map( "Maps/Map1.txt" );
	enemy_handler_init();
	tower_handler_init();

	map = ordered_map_create();
	ordered_map_insert( &map,ordered_map_create_pair(
		"hi","bop" ) );
	ordered_map_insert( &map,ordered_map_create_pair(
		"test","blep" ) );
	ordered_map_insert( &map,ordered_map_create_pair(
		"hello","twelve" ) );
	ordered_map_insert( &map,ordered_map_create_pair(
		"cup","cake" ) );

	const string_t str = ordered_map_find( &map,"cup" );
	printf( "%s",str );
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

	ordered_map_destroy( &map );
}
