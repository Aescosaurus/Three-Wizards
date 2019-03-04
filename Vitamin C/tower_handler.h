#ifndef TOWER_HANDLER_H
#define TOWER_HANDLER_H

#include "vec2.h"
#include "magic_types.h"
#include "colors.h"

typedef struct
{
	vec2_t pos;
	int range; // Range in number of tiles.
	magic_type magic;
	color_t draw_col;
} tower_t;

void tower_handler_init();
void tower_handler_destroy();
void tower_handler_update();
void tower_handler_draw();

tower_t create_snowball_tower();

void draw_tower( tower_t* t );

#endif