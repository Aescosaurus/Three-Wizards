#ifndef VECTOR_H
#define VECTOR_H

#include "utils.h"

// Generic dynamically allocated array.
typedef struct
{
	// Total number of elements vector is capable of
	//  holding before resizing.
	uint capacity;
	// Current number of elements(not chars) in the array.
	uint cur_pos;
	// Size of a single element.
	uint elem_size;
	// Generic data interpreted as chars, not a string!
	char* data;
} vector_t;

// Create and return a new vector.
vector_t vector_create( int start_size,int elem_size );
// Free memory from a vector.
void vector_delete( vector_t* vec );
// Takes control of element so you don't have to delete it.
void vector_add_element( vector_t* vec,void* element );
// Returns a reference to element of vec at index.
void* vector_at( vector_t* vec,int index );
// Returns number of elements in a vector.
int vector_count( const vector_t* vec );

#endif