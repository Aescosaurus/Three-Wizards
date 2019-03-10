#ifndef ENEMY_HANDLER_H
#define ENEMY_HANDLER_H

#include "vector.h"
#include "utils.h"
#include "vec2.h"
#include "rect.h"
#include "colors.h"
#include "surface.h"

#define ENEMY_MOVE_SPEED 80.1f
#define ENEMY_SIZE 15

typedef struct
{
	rect_t hitbox;
	vec2_t target;
	vec2_t vel;
	int cur_tile_index;
	color_t draw_col;
	int hp;
	surface_t* surf;
} enemy_t;

void enemy_handler_init();
void enemy_handler_destroy();

void enemy_handler_update( float dt );
void enemy_handler_draw();

// Set next target location of en to target.
void enemy_retarget( enemy_t* en,const rect_t* target );
void create_enemy();

vec2_t get_next_path_pos( int cur_x,int cur_y,
	vector_t* prev_paths );
bool_t path_exists_in( int x,int y,vector_t* prev_paths );
void draw_enemy( const enemy_t* en );
vector_t* get_enemy_vec();

#endif