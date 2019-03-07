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
// Removes element at index from vec, NOT preserving order.
void vector_remove_element( vector_t* vec,int index );
// Remove last element from the vector.
void vector_pop_back( vector_t* vec );

// Returns a reference to element of vec at index.
void* vector_at( vector_t* vec,int index );
// Returns a const reference to element of vec at index.
const void* vector_cat( const vector_t* vec,int index );
// Returns first element of vec.
void* vector_front( vector_t* vec );
// Returns last element of vec.
void* vector_back( vector_t* vec );
// Returns number of elements in a vector.
int vector_count( const vector_t* vec );

#endif