#include "codex.h"
#include "ordered_map.h"

ordered_map_t map;

void codex_init()
{
	map = ordered_map_create();
}

void codex_destroy()
{
	ordered_map_destroy( &map );
}

const surface_t* surface_codex_fetch( const string_t file_path )
{
	if( !ordered_map_element_exists( &map,file_path ) )
	{
		surface_t* temp = malloc( sizeof( surface_t ) );
		*temp = surface_create( file_path );
		ordered_map_insert( &map,ordered_map_create_pair(
			file_path,temp ) );
	}

	return( ordered_map_find( &map,file_path ) );
}
