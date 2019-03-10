#ifndef CODEX_H
#define CODEX_H

#include "utils.h"
#include "surface.h"

void codex_init();
void codex_destroy();

surface_t* surf_codex_fetch( const string_t file_path );
// TODO: sound codex fetch

#endif