#include <string.h>
#include "srv_types.h"

inline static srv_string* init_string_type(const srv_string* _str,
						  void*(action)(void* _s1, const void* _s2, size_t _ln));

srv_string* srv_copy_string(const srv_string *_str)
{
	return init_string_type(_str, &memcpy);
}

srv_string *srv_move_string(srv_string *_str)
{
	return init_string_type(_str, &memmove);
}

srv_string *srv_raw_string(char *_data, size_t _len)
{
	srv_string* _tmpData = malloc(sizeof (srv_string));
	_tmpData->_str_data = _data;
	_tmpData->_str_len = _len;
	return _tmpData;
}

inline static srv_string* init_string_type(const srv_string* _str,
						  void*(action)(void* _s1, const void* _s2, size_t _ln))
{
	if (_str == NULL)
	{
		return NULL;
	}

	const size_t string_size = sizeof (srv_string);

	srv_string* _tmpStr = malloc(string_size + _str->_str_len);
	void* _mem_begin_block = ((char*)_tmpStr) + string_size;
	_mem_begin_block = action(_mem_begin_block, _str->_str_data, _str->_str_len);
	if (_mem_begin_block == NULL)
	{
		free(_tmpStr);
		return NULL;
	}
	else
	{
		return  _tmpStr;
	}
}
