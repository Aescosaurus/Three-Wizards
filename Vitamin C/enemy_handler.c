#include "enemy_handler.h"
#include "tile_map.h"

vector_t enemy_vec;
vector_t path_vec;

void enemy_handler_init()
{
	int last_x = 0;
	int last_y = 0;
	vec2_t to_add = create_vec2( -1,-1 );
	bool_t keep_adding = TRUE;

	enemy_vec = vector_create( 2,sizeof( enemy_t ) );
	path_vec = vector_create( 2,sizeof( rect_t ) );

	for( int y = 0; y < N_Y_TILES; ++y )
	{
		for( int x = 0; x < N_X_TILES; ++x )
		{
			if( get_tile( x,y ) == tile_path_start )
			{
				rect_t* start_rect = malloc( sizeof( rect_t ) );
				*start_rect = create_rect(
					( float )x * TILE_SIZE,
					( float )y * TILE_SIZE,
					TILE_SIZE,TILE_SIZE );
				vector_add_element( &path_vec,start_rect );

				last_x = x;
				last_y = y;
			}
		}
	}
	
	do
	{
		to_add = get_next_path_pos( last_x,last_y,
			&path_vec );

		if( to_add.x == -1 || to_add.y == -1 )
		{
			keep_adding = FALSE;
		}
		else
		{
			rect_t* add_rect = malloc( sizeof( rect_t ) );

			last_x = ( int )to_add.x;
			last_y = ( int )to_add.y;

			*add_rect = create_rect( to_add.x * TILE_SIZE,
				to_add.y * TILE_SIZE,TILE_SIZE,TILE_SIZE );
			vector_add_element( &path_vec,add_rect );
		}
	} while( keep_adding );

	// Test enemy.
	{
		enemy_t* en = malloc( sizeof( enemy_t ) );
		const rect_t* start_square = vector_at( &path_vec,0 );
		const rect_t* next_square = vector_at( &path_vec,1 );

		// TODO: Turn all these into vec2_create.
		en->hitbox.x = start_square->x;
		en->hitbox.y = start_square->y;
		en->hitbox.width = 15;
		en->hitbox.height = 15;

		en->cur_tile_index = 1;

		en->target.x = next_square->x;
		en->target.y = next_square->y;

		en->vel.x = en->target.x - en->hitbox.x;
		en->vel.y = en->target.y - en->hitbox.y;

		en->vel = vec2_div( &en->vel,
			vec2_get_length( &en->vel ) );

		en->vel = vec2_mul( &en->vel,ENEMY_MOVE_SPEED );

		vector_add_element( &enemy_vec,en );
	}
}

void enemy_handler_destroy()
{
	vector_delete( &enemy_vec );
	vector_delete( &path_vec );
}

void enemy_handler_update()
{
	for( int i = 0; i < vector_count( &enemy_vec ); ++i )
	{
		enemy_t* cur_enemy = vector_at( &enemy_vec,i );

		cur_enemy->hitbox.x += cur_enemy->vel.x;
		cur_enemy->hitbox.y += cur_enemy->vel.y;

		if( rect_overlaps_point( &cur_enemy->hitbox,
			&cur_enemy->target ) )
		{
			const rect_t* next_square = vector_at( &path_vec,
				cur_enemy->cur_tile_index );

			cur_enemy->target.x = next_square->x;
			cur_enemy->target.y = next_square->y;

			cur_enemy->vel.x = cur_enemy->target.x -
				cur_enemy->hitbox.x;
			cur_enemy->vel.y = cur_enemy->target.y -
				cur_enemy->hitbox.y;

			cur_enemy->vel = vec2_div( &cur_enemy->vel,
				vec2_get_length( &cur_enemy->vel ) );

			cur_enemy->vel = vec2_mul( &cur_enemy->vel,
				ENEMY_MOVE_SPEED );

			cur_enemy->cur_tile_index += 1;
		}
	}
}

void enemy_handler_draw()
{
	for( int i = 0; i < vector_count( &path_vec ); ++i )
	{
		const rect_t* temp_rect = vector_at( &path_vec,i );
		
		draw_rect( temp_rect->x,temp_rect->y,
			temp_rect->width,temp_rect->height,
			make_rgb(
				i * ( 255 / vector_count( &path_vec ) ),
				i * ( 255 / vector_count( &path_vec ) ),
				i * ( 255 / vector_count( &path_vec ) )
			) );
	}

	for( int i = 0; i < vector_count( &enemy_vec ); ++i )
	{
		const enemy_t* cur_enemy = vector_at( &enemy_vec,i );

		draw_rect( ( int )cur_enemy->hitbox.x,
			( int )cur_enemy->hitbox.y,
			( int )cur_enemy->hitbox.width,
			( int )cur_enemy->hitbox.height,
			color_green() );
	}
}

vec2_t get_next_path_pos( int cur_x,int cur_y,
	vector_t* prev_paths )
{
	// int start_x = cur_x - 1;
	// int start_y = cur_y - 1;
	// int end_x = cur_x + 2;
	// int end_y = cur_y + 2;
	vec2_t next_pos = create_vec2( -1,-1 );

	// if( start_x < 0 ) start_x = 0;
	// if( start_y < 0 ) start_y = 0;
	// if( end_x > N_X_TILES ) end_x = N_X_TILES;
	// if( end_y > N_Y_TILES ) end_y = N_Y_TILES;

	if( tile_exists( cur_x,cur_y - 1 ) &&
		get_tile( cur_x,cur_y - 1 ) == tile_path &&
		!path_exists_in( cur_x,cur_y - 1,prev_paths ) )
	{
		next_pos.x = ( float )cur_x;
		next_pos.y = ( float )cur_y - 1;
	}
	// else if( tile_exists( cur_x,cur_y ) &&
	// 	get_tile( cur_x,cur_y ) == tile_path &&
	// 	!path_exists_in( cur_x,cur_y,prev_paths ) )
	// {
	// 	next_pos.x = cur_x;
	// 	next_pos.y = cur_y;
	// }
	else if( tile_exists( cur_x,cur_y + 1 ) &&
		get_tile( cur_x,cur_y + 1 ) == tile_path &&
		!path_exists_in( cur_x,cur_y + 1,prev_paths ) )
	{
		next_pos.x = ( float )cur_x;
		next_pos.y = ( float )cur_y + 1;
	}
	else if( tile_exists( cur_x - 1,cur_y ) &&
		get_tile( cur_x - 1,cur_y ) == tile_path &&
		!path_exists_in( cur_x - 1,cur_y,prev_paths ) )
	{
		next_pos.x = ( float )cur_x - 1;
		next_pos.y = ( float )cur_y;
	}
	else if( tile_exists( cur_x + 1,cur_y ) &&
		get_tile( cur_x + 1,cur_y ) == tile_path &&
		!path_exists_in( cur_x + 1,cur_y,prev_paths ) )
	{
		next_pos.x = ( float )cur_x + 1;
		next_pos.y = ( float )cur_y;
	}

	// for( int y = start_y; y < end_y; ++y )
	// {
	// 	for( int x = start_x; x < end_x; ++x )
	// 	{
	// 		if( get_tile( x,y ) == tile_path &&
	// 			!path_exists_in( x,y,prev_paths ) )
	// 		{
	// 			next_pos.x = x;
	// 			next_pos.y = y;
	// 		}
	// 		else if( get_tile( x,y ) == tile_path_end )
	// 		{
	// 			next_pos.x = -1;
	// 			next_pos.y = -1;
	// 		}
	// 	}
	// }
	
	return( next_pos );
}

bool_t path_exists_in( int x,int y,vector_t* prev_paths )
{
	bool_t exists = FALSE;

	for( int i = 0; i < vector_count( prev_paths ); ++i )
	{
		const rect_t* path = vector_at( prev_paths,i );

		if( x * TILE_SIZE == path->x &&
			y * TILE_SIZE == path->y )
		{
			exists = TRUE;
		}
	}

	return( exists );
}
