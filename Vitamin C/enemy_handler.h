#ifndef ENEMY_HANDLER_H
#define ENEMY_HANDLER_H

#include "vector.h"
#include "utils.h"
#include "vec2.h"
#include "rect.h"

#define ENEMY_MOVE_SPEED 80.1f

typedef struct
{
	rect_t hitbox;
	vec2_t target;
	vec2_t vel;
	int cur_tile_index;
} enemy_t;

void enemy_handler_init();
void enemy_handler_destroy();
void enemy_handler_update( float dt );
void enemy_handler_draw();

vec2_t get_next_path_pos( int cur_x,int cur_y,
	vector_t* prev_paths );
bool_t path_exists_in( int x,int y,vector_t* prev_paths );


#endif