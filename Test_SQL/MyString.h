#pragma once

int Mystrlen(const char* dest);
int Mystrcmp(const char* dest, const char* src);
char* Mystrcpy(char* dest,const char* src);
char* Mystrcat(char* dest, const char* src);

void* Mymemcpy(void* destin, void* source, unsigned n);
void* Mymemset(void* s, int ch, size_t n);
int Mymemcmp(const void* str1, const void* str2, size_t n);

