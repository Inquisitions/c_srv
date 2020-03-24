#include <netdb.h>
#include <netinet/in.h>

#include "http_server.h"

typedef struct __http_server_data
{
	int socket;
	struct sockaddr_in* addr;
} __srv_http_server_data;

inline static srv_http_server* init_http_server_type(const srv_url* _url,
													 srv_url*(*action)(const srv_url* _val));

srv_http_server *srv_init_copy_tcp_server(const srv_url *url)
{
	return init_http_server_type(url, &srv_copy_url);
}

srv_http_server *srv_init_move_tcp_server(srv_url *url)
{
	return init_http_server_type(url, &srv_move_url);
}

srv_http_server *srv_init_raw_tcp_server(srv_url *url)
{
	srv_http_server* _tcp_server = malloc(sizeof (srv_http_server));
	_tcp_server->url = url;
	return  _tcp_server;
}

inline static srv_http_server* init_http_server_type(const srv_url* _url,
												srv_url*(*action)(const srv_url *))
{
	if (_url == NULL)
	{
		return NULL;
	}

	size_t type_sz = sizeof (srv_http_server);

	srv_http_server* _tcp_server = malloc(type_sz + sizeof (__srv_http_server_data));
	_tcp_server->url = action(_url);
	__srv_http_server_data* data = (((void*)_tcp_server) + type_sz);
	data->socket = socket(AF_INET, SOCK_STREAM, 0);

	data->addr = malloc(sizeof (struct sockaddr));
	data->addr->sin_family = AF_INET;
	data->addr->sin_addr.s_addr = INADDR_ANY;
	data->addr->sin_port = htons(_url->port);

	return  _tcp_server;
}


int8_t srv_try_to_connect(const srv_http_server *_srv)
{
	const __srv_http_server_data* data = (__srv_http_server_data*)_srv->data;
	int state = bind(data->socket, (struct sockaddr *)data->addr, sizeof (struct sockaddr));
	if (state < 0)
	{
		return 1;
	}
	else
	{
		listen(data->socket, _srv->max_connection);
		return 0;
	}
}

srv_http_handler *srv_wait_request(const srv_http_server *_srv)
{
	const __srv_http_server_data* _srv_data = (__srv_http_server_data*)_srv->data;

	__srv_http_server_data* _tmpData =  malloc(sizeof (__srv_http_server_data));

	__socklen_t srv_data_len = sizeof (struct sockaddr_in);
	_tmpData->socket = accept(_srv_data->socket,
							  (struct sockaddr *) _tmpData->addr,
							  &srv_data_len);

	if (_tmpData->socket < 0)
	{
		free(_tmpData);
		return NULL;
	}
	else
	{
		return  (srv_http_handler*)_tmpData;
	}
}
