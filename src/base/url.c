#include "url.h"

inline static srv_url* init_url_type(const srv_url* url,
							  srv_string*(*action)(const srv_string* _val));

srv_url *srv_copy_url(const srv_url *url)
{
	return  init_url_type(url, &srv_copy_string);
}

srv_url *srv_move_url(srv_url *url)
{
	return  init_url_type(url, &srv_copy_string);
}

srv_url *srv_raw_url(srv_string *_schm,
						  srv_string *_hst,
						  uint32_t _prt,
						  srv_string *_pth,
						  srv_string *_src)
{
	struct __url* _tmpUrl = malloc(sizeof (srv_url));

	_tmpUrl->scheme = _schm;
	_tmpUrl->host = _hst;
	_tmpUrl->port = _prt;
	_tmpUrl->path = _pth;
	_tmpUrl->search = _src;

	return _tmpUrl;
}


inline static srv_url* init_url_type(const srv_url* url,
							  srv_string*(*action)(const srv_string* _val))
{
	if (url == NULL)
	{
		return NULL;
	}

	struct __url* _tmpUrl = malloc(sizeof (srv_url));

	_tmpUrl->scheme = action(url->scheme);
	_tmpUrl->host = action(url->host);
	_tmpUrl->path = action(url->path);
	_tmpUrl->search = action(url->search);
	_tmpUrl->port = url->port;

	return _tmpUrl;
}
