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
		// Allocate new memory twice the size of original.
		const int orig_size = ( int )vec->capacity;
		char* temp = ( char* )malloc( vec->capacity *
			vec->elem_size * 2 );

		vec->capacity *= 2;

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
}

void* vector_at( vector_t* vec,int index )
{
	assert( index < ( int )vec->capacity );

	return( &( vec->data[index * vec->elem_size] ) );
}

uint vector_count( const vector_t* vec )
{
	return( vec->cur_pos );
}
