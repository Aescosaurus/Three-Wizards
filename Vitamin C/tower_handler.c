#include "tower_handler.h"
#include "vector.h"
#include "tile_map.h"
#include "mouse.h"
#include <assert.h>
#include "random.h"

vector_t tower_vec;
vector_t bullet_vec;
tower_t preview_tower;
bool_t tower_menu_open = FALSE;
vec2_t menu_draw_pos;

void tower_handler_init()
{
	tower_vec = vector_create( 2,sizeof( tower_t ) );
	bullet_vec = vector_create( 2,sizeof( bullet_t ) );
	
	// preview_tower = create_snowball_tower();
	preview_tower = create_tower( basic_leaf_tower,
		0.0f,0.0f );
}

void tower_handler_destroy()
{
	vector_delete( &tower_vec );
}

void tower_handler_update( vector_t* enemies,
	float dt )
{
	if( tower_menu_open )
	{
		// Select tower to place here.
	}
	else
	{
		// Tower placement stuff.
		preview_tower.pos = world_pos_2_tile_pos(
			mouse_get_pos() );

		if( mouse_left_is_pressed() )
		{
			attempt_place_tower( preview_tower );
		}

		// Update everything.
		for( int i = 0; i < vector_count( &tower_vec ); ++i )
		{
			tower_t* cur_tower = vector_at( &tower_vec,i );

			update_tower( cur_tower,enemies,dt );
		}

		for( int i = 0; i < vector_count( &bullet_vec ); ++i )
		{
			bullet_t* cur_bullet = vector_at( &bullet_vec,i );

			update_bullet( cur_bullet,dt );

			for( int i = 0; i < vector_count( enemies ); ++i )
			{
				enemy_t* cur_enemy = vector_at( enemies,i );

				if( rect_overlaps( &cur_bullet->hitbox,
					&cur_enemy->hitbox ) )
				{
					cur_enemy->hp -= cur_bullet->damage;
					cur_bullet->alive = FALSE;
				}
			}

			if( !cur_bullet->alive )
			{
				vector_remove_element( &bullet_vec,i );
			}
		}
	}
	
	// Handle open/closing tower select menu.
	if( mouse_right_is_pressed() )
	{
		if( !tower_menu_open )
		{
			tower_menu_open = TRUE;
			menu_draw_pos = mouse_get_pos();
		}
	}
	else
	{
		tower_menu_open = FALSE;
	}
}

void tower_handler_draw()
{
	if( tower_menu_open )
	{
		const int n_menu_options = 5;
		const int menu_width = TILE_SIZE * n_menu_options;
		const int menu_height = TILE_SIZE * n_menu_options;
		const int menu_start_x = ( int )menu_draw_pos.x -
			menu_width / 2;
		const int menu_start_y = ( int )menu_draw_pos.y -
			menu_height / 2;

		draw_rect( menu_start_x,menu_start_y,
			menu_width,menu_height,
			color_red() );
		
		for( int y = 0; y < n_menu_options; ++y )
		{
			for( int x = 0; x < n_menu_options; ++x )
			{
				// We will draw sprites here in the future.
				draw_rect( menu_start_x + TILE_SIZE * x,
					menu_start_y + TILE_SIZE * y,
					TILE_SIZE,TILE_SIZE,
					rand_color() );
			}
		}
	}
	else
	{
		for( int i = 0; i < vector_count( &tower_vec ); ++i )
		{
			const tower_t* t = vector_at( &tower_vec,i );

			draw_tower( t );
		}

		for( int i = 0; i < vector_count( &bullet_vec ); ++i )
		{
			const bullet_t* b = vector_at( &bullet_vec,i );

			draw_bullet( b );
		}

		draw_tower( &preview_tower );
		draw_tower_radius( &preview_tower );
	}
}

bool_t attempt_place_tower( tower_t t )
{
	bool_t result = FALSE;
	const int tower_x = ( int )t.pos.x / TILE_SIZE;
	const int tower_y = ( int )t.pos.y / TILE_SIZE;

	if( get_tile( tower_x,tower_y ) == tile_empty )
	{
		tower_t* temp = malloc( sizeof( tower_t ) );
		*temp = t;
		vector_add_element( &tower_vec,temp );

		// This spot now contains a tower.
		set_tile( tower_x,tower_y,tile_tower );
		result = TRUE;
	}
	else
	{
		result = FALSE;
	}

	return( result );
}

tower_t create_tower( tower_type type,float x,float y )
{
	tower_t tow;

	tow.pos = create_vec2( x,y );
	tow.type = type;

	switch( type )
	{
	case basic_leaf_tower:
		tow.range = 4;
		tow.magic = magic_leaf;
		tow.draw_col = color_green();
		tow.damage = create_range( 1,3 );
		tow.refire = create_timer( 0.8f );
		break;
	case snowball_tower:
		tow.range = 8;
		tow.magic = magic_water;
		tow.draw_col = color_blue();
		tow.damage = create_range( 4,6 );
		tow.refire = create_timer( 1.5f );
		break;
	case flame_spinner_tower:
		tow.range = 2;
		tow.magic = magic_fire;
		tow.draw_col = color_red();
		tow.damage = create_range( 1,2 );
		tow.refire = create_timer( 0.4f );
		break;
	}

	return( tow );
}

void update_tower( tower_t* t,const vector_t* enemies,
	float dt )
{
	timer_update( &t->refire,dt );

	if( timer_is_done( &t->refire ) )
	{
		const enemy_t* closest = find_closest_enemy(
			t->pos,enemies );

		if( closest != NULL && vec2_get_length(vec2_sub(
			rect_get_center( &closest->hitbox ),
			t->pos ) ) < t->range * TILE_SIZE )
		{
			vec2_t bullet_vel;
			timer_reset( &t->refire );

			switch( t->type )
			{
			case basic_leaf_tower:
				bullet_vel = vec2_sub( rect_get_center(
					&closest->hitbox ),t->pos );

				if( bullet_vel.x != 0.0f ||
					bullet_vel.y != 0.0f )
				{
					bullet_vel = vec2_div( bullet_vel,
						vec2_get_length( bullet_vel ) );
				}
				break;
			case snowball_tower:
				bullet_vel = vec2_sub( rect_get_center(
					&closest->hitbox ),t->pos );

				if( bullet_vel.x != 0.0f ||
					bullet_vel.y != 0.0f )
				{
					bullet_vel = vec2_div( bullet_vel,
						vec2_get_length( bullet_vel ) );
				}
				break;
			case flame_spinner_tower:
				bullet_vel = vec2_sub( rect_get_center(
					&closest->hitbox ),t->pos );

				if( bullet_vel.x != 0.0f ||
					bullet_vel.y != 0.0f )
				{
					bullet_vel = vec2_div( bullet_vel,
						vec2_get_length( bullet_vel ) );
				}
				break;
			default:
				assert( FALSE );
				break;
			}
			create_bullet( t->type,vec2_add( t->pos,
				create_vec2( TILE_SIZE / 2,
					TILE_SIZE / 2 ) ),t->draw_col,
				bullet_vel,( int )random_range(
				( float )( t->damage.min ),
				( float )( t->damage.max ) ) );
		}
	}
}

void create_bullet( tower_type type,vec2_t pos,
	color_t col,vec2_t vel,int damage )
{
	bullet_t* temp = malloc( sizeof( bullet_t ) );

	temp->hitbox = create_rect( pos.x,pos.y,
		BULLET_SIZE,BULLET_SIZE );
	temp->vel = vel;
	temp->type = type;
	temp->col = col;
	temp->speed = 255.1f; // From 45.1.
	temp->lifetimer = create_timer( 0.9f );
	temp->alive = TRUE;
	temp->damage = damage;

	vector_add_element( &bullet_vec,temp );
}

void update_bullet( bullet_t* b,float dt )
{
	b->hitbox.x += b->vel.x * b->speed * dt;
	b->hitbox.y += b->vel.y * b->speed * dt;

	timer_update( &b->lifetimer,dt );
	if( timer_is_done( &b->lifetimer ) ||
		!rect_contains_rect( &b->hitbox,
		get_screen_rect() ) )
	{
		b->alive = FALSE;
	}
}

void draw_bullet( const bullet_t* b )
{
	draw_rect( ( int )b->hitbox.x - BULLET_SIZE / 2,
		( int )b->hitbox.y - BULLET_SIZE / 2,
		BULLET_SIZE,BULLET_SIZE,b->col );
}

void draw_tower( const tower_t* t )
{
	draw_rect( ( int )t->pos.x,( int )t->pos.y,
		TILE_SIZE,TILE_SIZE,t->draw_col );
}

void draw_tower_radius( const tower_t* t )
{
	const int grid_x = ( int )t->pos.x / TILE_SIZE;
	const int grid_y = ( int )t->pos.y / TILE_SIZE;
	const int rad = ( int )( t->range );
	const int rad_sq = ( int )( t->range * t->range );
	const color_t draw_col = tile_exists( grid_x,grid_y ) &&
		( get_tile( grid_x,grid_y ) == tile_empty )
		? color_green() : color_red();

	for( int y = grid_y - rad; y < grid_y + rad; ++y )
	{
		for( int x = grid_x - rad; x < grid_x + rad; ++x )
		{
			// const vec2_t cur_pos = world_pos_2_tile_pos(
			// 	create_vec2( ( float )x,( float )y ) );
			const int x_diff = x - grid_x;
			const int y_diff = y - grid_y;

			if( x_diff * x_diff + y_diff * y_diff <
				rad_sq && tile_exists( x,y ) )
			{
				draw_rect_alpha( x * TILE_SIZE,
					y * TILE_SIZE,
					TILE_SIZE,TILE_SIZE,
					draw_col,0.2f );
			}
		}
	}
}

vec2_t world_pos_2_tile_pos( vec2_t world_pos )
{
	int x_pos = ( int )world_pos.x;
	int y_pos = ( int )world_pos.y;

	while( x_pos % TILE_SIZE != 0 ) --x_pos;
	while( y_pos % TILE_SIZE != 0 ) --y_pos;

	return( create_vec2( ( float )x_pos,( float )y_pos ) );
}

bool_t tower_menu_is_open()
{
	return( tower_menu_open );
}

const enemy_t* find_closest_enemy( vec2_t pos,
	const vector_t* enemies )
{
	const enemy_t* closest = NULL;
	float dist = 9999.0f;

	for( int i = 0; i < vector_count( enemies ); ++i )
	{
		const enemy_t* cur_enemy = vector_cat( enemies,i );
		const float dist_to_enemy = vec2_get_length(
			vec2_sub( rect_get_center(
			&cur_enemy->hitbox ),pos ) );

		if( dist_to_enemy < dist )
		{
			closest = cur_enemy;
			dist = dist_to_enemy;
		}
	}

	return( closest );
}
