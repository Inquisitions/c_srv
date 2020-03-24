#pragma once

#include <stdlib.h>
#include <inttypes.h>
#include "srv_types.h"

typedef struct __url
{
	srv_string* scheme;
	srv_string* host;
	srv_string* path;
	srv_string* search;
	uint16_t port;
} srv_url;

srv_url* srv_copy_url(const srv_url* url);

srv_url* srv_move_url(srv_url* url);

srv_url* srv_raw_url(srv_string* _schm, srv_string* _hst, uint32_t _prt,
						  srv_string* _pth, srv_string* _src);
