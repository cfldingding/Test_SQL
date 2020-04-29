#include "MyString.h"
#include<assert.h>
int Mystrlen(const char* dest)
{
	assert(nullptr != dest);
	int num = 0;
	while (*dest++)
		num++;
	return num;
}


int Mystrcmp(const char* dest, const char* src)
{
	while (*dest == *src)
	{
		assert((nullptr != dest)&& (nullptr != src));
		if ('\0' == *dest)
			return 0;
		dest++;
		src++;
	}
	return *dest - *src;
}

char* Mystrcpy(char* dest, const char* src)
{
	assert(nullptr != src);
	char* v_dest = dest;
	const char* v_src = src;
	while ((*v_dest++ = *v_src++) != '\0');
	return dest;
}

char* Mystrcat(char* dest, const char* src)
{
	assert(nullptr != src && nullptr != dest);
	char* v_dest = dest;
	while (*v_dest)
		v_dest++;
	while ((*v_dest++ = *src++) != '\0');
	return dest;
}

void* Mymemcpy(void* destin, void* source, unsigned n)
{
	//static_assert((nullptr != destin) && (nullptr != source));
	assert((nullptr != destin) && (nullptr != source));
	char* v_destin = (char*)destin;
	char* v_source = (char*)source;
	while(n--)
	{
		*v_destin++ = *v_source++;
	}
	return destin;
}

void* Mymemset(void* s, int ch, size_t n)
{
	assert(nullptr  != s);
	char* v_temp = (char*)s;
	while (n--)
	{
		*v_temp = ch;
		v_temp++;
	}
		
	return s;
}

int MyMemcmp(const void* str1, const void* str2, size_t n)
{
	assert((nullptr != str1) && (nullptr != str2));
	char* v_str1 = (char*)str1;
	char* v_str2 = (char*)str2;
	for (size_t i = 0;i < n;++i)
	{
		if (*v_str1 != *v_str2)
		{
			return *v_str1 - *v_str2;
		}
		v_str1++;
		v_str2++;
	}
	return 0;
}