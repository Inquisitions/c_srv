#pragma once

#include "url.h"

typedef void* srv_http_server_data;
typedef void* srv_http_handler;

typedef struct __http_server
{
	srv_url* url;
	srv_http_server_data* data;
	uint8_t max_connection;
} srv_http_server;

srv_http_server* srv_init_copy_tcp_server(const srv_url* url);
srv_http_server* srv_init_move_tcp_server(srv_url* url);
srv_http_server* srv_init_raw_tcp_server(srv_url* url);

int8_t srv_try_to_connect(const srv_http_server *_srv);
srv_http_handler* srv_wait_request(const srv_http_server *_srv);

int8_t srv_get_from_handler() __attribute_warn_unused_result__;
