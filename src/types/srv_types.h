#pragma once

#include <stdlib.h>

typedef struct __string
{
	char* _str_data;
	size_t _str_len;
} srv_string;

srv_string* srv_copy_string(const srv_string* _str);

srv_string* srv_move_string(srv_string *_str);

srv_string* srv_raw_string(char* _data, size_t _len);
