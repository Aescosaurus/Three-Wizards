#ifndef TOWER_HANDLER_H
#define TOWER_HANDLER_H

#include "vec2.h"
#include "magic_types.h"
#include "colors.h"
#include "utils.h"
#include "timer.h"
#include "range.h"
#include "rect.h"
#include "enemy_handler.h"

typedef enum
{
	basic_leaf_tower,
	snowball_tower,
	flame_spinner_tower
} tower_type;

typedef struct
{
	vec2_t pos;
	tower_type type;
	int range; // Range in number of tiles.
	magic_type magic;
	color_t draw_col;
	range_t damage;
	timer_t refire;
} tower_t;

#define BULLET_SIZE 16

typedef struct
{
	rect_t hitbox;
	vec2_t vel;
	tower_type type;
	color_t col;
	timer_t lifetimer;
	float speed;
	bool_t alive;
	int damage;
} bullet_t;

void tower_handler_init();
void tower_handler_destroy();
void tower_handler_update( vector_t* enemies,
	float dt );
void tower_handler_draw();

bool_t attempt_place_tower( tower_t t );

tower_t create_tower( tower_type type,float x,float y );
void update_tower( tower_t* t,const vector_t* enemies,
	float dt );

void create_bullet( tower_type type,vec2_t pos,
	color_t col,vec2_t vel,int damage );
void update_bullet( bullet_t* b,float dt );
void draw_bullet( const bullet_t* b );

void draw_tower( const tower_t* t );
void draw_tower_radius( const tower_t* t );
vec2_t world_pos_2_tile_pos( vec2_t world_pos );
bool_t tower_menu_is_open();
const enemy_t* find_closest_enemy( vec2_t pos,
	const vector_t* enemies );

#endif