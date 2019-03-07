#ifndef TOWER_HANDLER_H
#define TOWER_HANDLER_H

#include "vec2.h"
#include "magic_types.h"
#include "colors.h"
#include "utils.h"
#include "timer.h"
#include "range.h"

typedef enum
{
	basic_leaf_tower,
	snowball_tower,
	flame_spinner_tower
} tower_type;

typedef struct
{
	vec2_t pos;
	int range; // Range in number of tiles.
	magic_type magic;
	color_t draw_col;
	range_t damage;
	timer_t refire;
} tower_t;

void tower_handler_init();
void tower_handler_destroy();
void tower_handler_update();
void tower_handler_draw();

bool_t attempt_place_tower( tower_t t );

tower_t create_tower( tower_type type,float x,float y );

void draw_tower( const tower_t* t );
void draw_tower_radius( const tower_t* t );
vec2_t world_pos_2_tile_pos( vec2_t world_pos );
bool_t tower_menu_is_open();

#endif