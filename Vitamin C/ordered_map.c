#include "ordered_map.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

ordered_map_t ordered_map_create()
{
	ordered_map_t temp;
	temp.start = malloc( sizeof( ordered_map_node_t ) );
	temp.start->left = NULL;
	temp.start->right = NULL;
	temp.start->pair.key = NULL;
	temp.start->pair.value = NULL;
	return( temp );
}

void ordered_map_destroy( ordered_map_t* map )
{
	ordered_map_free_node( map->start );
}

void ordered_map_insert( ordered_map_t* map,
	ordered_map_pair_t pair )
{
	ordered_map_node_t* latest = ordered_map_find_latest(
		map->start,&pair );

	if( ordered_map_element_exists( map,pair.key ) )
	{
		printf( "(!) Error, map element with key " );
		printf( "%s already exists!\n",pair.key );
		assert( FALSE );
	}

	if( latest->pair.key == NULL ) // Handle first element.
	{
		assert( latest->pair.value == NULL );

		latest->pair = pair;
	}
	else if( pair.key >= latest->pair.key )
	{
		assert( latest->right == NULL );

		latest->right = malloc( sizeof( ordered_map_node_t ) );
		latest->right->pair = pair;
		latest->right->left = NULL;
		latest->right->right = NULL;
	}
	else
	{
		assert( latest->left == NULL );
		assert( pair.key != latest->pair.key );

		latest->left = malloc( sizeof( ordered_map_node_t ) );
		latest->left->pair = pair;
		latest->left->left = NULL;
		latest->left->right = NULL;
	}
}

void* ordered_map_find( const ordered_map_t* map,
	const string_t name )
{
	ordered_map_node_t* cur = map->start;

	ordered_map_node_t* found = ordered_map_get_match(
		cur,name );

	if( found != NULL )
	{
		return( found->pair.value );
	}
	else
	{
		return( NULL );
	}
}

bool_t ordered_map_element_exists( const ordered_map_t* map,
	const string_t name )
{
	return( ordered_map_find( map,name ) != NULL );
}

ordered_map_pair_t ordered_map_create_pair(
	const string_t key,void* value )
{
	ordered_map_pair_t pair;
	pair.key = key;
	pair.value = value;
	return( pair );
}

ordered_map_node_t* ordered_map_find_latest(
	ordered_map_node_t* start,
	const ordered_map_pair_t* pair )
{
	// ordered_map_node_t* cur = start;
	// if( cur->left == NULL && cur->right == NULL )
	// {
	// 	return( cur );
	// }
	// 
	// if( cur->right != NULL && pair.key > cur->pair.key )
	// {
	// 	cur = cur->right;
	// }
	// else
	// {
	// 	cur = cur->left;
	// }
	// 
	// if( cur->left == NULL )
	// {
	// 	return( cur );
	// }
	// return( ordered_map_find_latest( cur,pair ) );

	ordered_map_node_t* cur = start;

	if( cur->right != NULL && pair->key >= cur->pair.key )
	{
		cur = cur->right;
	}
	else if( cur->left != NULL && pair->key < cur->pair.key )
	{
		cur = cur->left;
	}
	else
	{
		return( cur );
	}

	return( ordered_map_find_latest( cur,pair ) );
}

ordered_map_node_t* ordered_map_get_match(
	ordered_map_node_t* start,const string_t name )
{
	if( start == NULL || // This line must come first.
		name == start->pair.key ) // End the cycle.
	{
		return( start );
	}
	else if( name > start->pair.key )
	{
		return( ordered_map_get_match( start->right,name ) );
	}
	else
	{
		return( ordered_map_get_match( start->left,name ) );
	}
}

void ordered_map_free_node( ordered_map_node_t* start )
{
	if( start != NULL )
	{
		ordered_map_node_t* next1 = start->left;
		ordered_map_node_t* next2 = start->right;

		free( start );

		if( next1 != NULL ) ordered_map_free_node( next1 );
		if( next2 != NULL ) ordered_map_free_node( next2 );
	}
}
