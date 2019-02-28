#include "game.h"
#include "tile_map.h"
#include "vector.h"

// ---------------User Variables Go Here---------------- //
vector_t test_vec;
// ----------------------------------------------------- //

void initialize_game()
{
	create_map( "Maps/Map1.txt" );
	test_vec = vector_create( 2,sizeof( double ) );

	double* temp_val = ( double* )malloc( sizeof( double ) );
	*temp_val = 2.17;
	vector_add_element( &test_vec,temp_val );

	double* temp2 = ( double* )malloc( sizeof( double ) );
	*temp2 = 1.16;
	vector_add_element( &test_vec,temp2 );

	double* temp3 = ( double* )malloc( sizeof( double ) );
	*temp3 = 3.14;
	vector_add_element( &test_vec,temp3 );

	double* temp4 = ( double* )malloc( sizeof( double ) );
	*temp4 = 4.2;
	vector_add_element( &test_vec,temp4 );

	double* temp5 = ( double* )malloc( sizeof( double ) );
	*temp5 = 9.9;
	vector_add_element( &test_vec,temp5 );

	printf( "count: %d\n",( int )vector_count( &test_vec ) );
	for( int i = 0; i < ( int )vector_count( &test_vec ); ++i )
	{
		printf( "%lf",*( ( double* )vector_at( &test_vec,i ) ) );
		printf( "\n" );
	}

	vector_delete( &test_vec );
}

void update_model()
{
}

void compose_frame()
{
	draw_map();
}

void destruct_game()
{
	destroy_map();
}
