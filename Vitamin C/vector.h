#ifndef VECTOR_H
#define VECTOR_H

#include "utils.h"

// Generic dynamically allocated array.
typedef struct
{
	uint capacity;
	uint cur_pos;
	uint elem_size;
	char* data;
} vector_t;

vector_t vector_create( int start_size,int elem_size );
void vector_delete( vector_t* vec );
// Takes control of element so you don't have to delete it.
void vector_add_element( vector_t* vec,void* element );
// Returns a reference to element of vec at index.
void* vector_at( vector_t* vec,int index );
// Returns number of elements in a vector.
uint vector_count( vector_t* vec );

#endif