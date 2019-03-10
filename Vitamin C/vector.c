#include "vector.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

vector_t vector_create( int start_size,int elem_size )
{
	assert( sizeof( char ) == 1 ); // Important for math!
	vector_t temp;

	temp.capacity = start_size;
	temp.cur_pos = 0;
	temp.elem_size = elem_size;
	temp.data = ( char* )malloc( elem_size * start_size );

	return( temp );
}

void vector_delete( vector_t* vec )
{
	free( vec->data );
	vec->data = NULL;
}

void vector_add_element( vector_t* vec,void* element )
{
	// Use char* for char(1 byte long) math.
	char* pos = vec->data;
	
	// Copy new element data into char array.
	pos += vec->cur_pos * vec->elem_size;
	memcpy( pos,element,vec->elem_size );
	free( element ); // Important!
	
	vec->cur_pos += 1;

	// Resize array if we need to.
	if( vec->cur_pos >= vec->capacity )
	{
		vector_resize( vec,vec->capacity * 2 );
	}
}

void vector_remove_element( vector_t* vec,int index )
{
	assert( vec->cur_pos > 0 );

	// No swapping is necessary.
	if( vec->cur_pos < 2 )
	{
		vector_pop_back( vec );
	}
	else // Swap and pop.
	{
		const char* last_element = vector_back( vec );
		char* element_to_remove = vector_at( vec,index );

		for( int i = 0; i < ( int )vec->elem_size; ++i )
		{
			element_to_remove[i] = last_element[i];
		}

		vector_pop_back( vec );
	}
}

void vector_pop_back( vector_t* vec )
{
	assert( vec->cur_pos > 0 );

	vec->cur_pos -= 1;
}

void vector_resize( vector_t* vec,int new_size )
{
	// Allocate new memory twice the size of original.
	const int orig_size = ( int )vec->capacity;
	char* temp = ( char* )malloc( vec->capacity *
		vec->elem_size * 2 );

	if( new_size > ( int )vec->capacity )
	{
		vec->capacity = new_size;
	}
	else vec->capacity *= 2;

	// Copy data into bigger vector.
	for( int i = 0;
		i < orig_size * ( int )vec->elem_size;
		++i )
	{
		temp[i] = vec->data[i];
	}

	free( vec->data ); // Important!

	// SHALLOW copy works here! :D
	vec->data = temp;
	temp = NULL;
}

void* vector_at( vector_t* vec,int index )
{
	assert( vec->cur_pos > 0 );
	assert( index < ( int )vec->capacity );

	return( &( vec->data[index * vec->elem_size] ) );
}

const void* vector_cat( const vector_t* vec,int index )
{
	assert( vec->cur_pos > 0 );
	assert( index < ( int )vec->capacity );

	return( &( vec->data[index * vec->elem_size] ) );
}

void* vector_front( vector_t* vec )
{
	assert( vec->cur_pos > 0 );

	return( &( vec->data[0] ) );
}

void* vector_back( vector_t* vec )
{
	assert( vec->cur_pos > 0 );

	return( &( vec->data[( vec->cur_pos - 1 ) *
		vec->elem_size] ) );
}

int vector_count( const vector_t* vec )
{
	return( ( int )vec->cur_pos );
}
