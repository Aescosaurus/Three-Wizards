#ifndef ORDERED_MAP_H
#define ORDERED_MAP_H

#include "utils.h"

// Yeah good luck with this lol.
//  Especially if you hope to make it generic.
//  Maybe try with like ints or something first.

struct ordered_map_node_s;

typedef struct
{
	string_t key;
	char* value; // Holds any type of data like vector.
} ordered_map_pair_t;

struct ordered_map_node_s
{
	struct ordered_map_node_s* left; // less
	struct ordered_map_node_s* right; // greater
	ordered_map_pair_t pair;
};
typedef struct ordered_map_node_s ordered_map_node_t;

typedef struct
{
	ordered_map_node_t* start;
} ordered_map_t;

ordered_map_t ordered_map_create();
void ordered_map_destroy( ordered_map_t* map );

void ordered_map_insert( ordered_map_t* map,
	ordered_map_pair_t pair );
// We don't need to remove nodes, right?  Great!
// void ordered_map_remove( const string_t name );

void* ordered_map_find( const ordered_map_t* map,
	const string_t name );
bool_t ordered_map_element_exists( const ordered_map_t* map,
	const string_t name );
ordered_map_pair_t ordered_map_create_pair(
	const string_t key,void* value );

// Internal function, don't use please.
ordered_map_node_t* ordered_map_find_latest(
	ordered_map_node_t* start,ordered_map_pair_t pair );
// Internal function, don't use please.
ordered_map_node_t* ordered_map_get_match(
	ordered_map_node_t* start,const string_t name );
// Internal function, don't use please.
void ordered_map_free_node( ordered_map_node_t* start );

#endif