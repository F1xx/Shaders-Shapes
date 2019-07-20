#pragma once

void PrintLeaks();

void* operator new(size_t size, const char* filename, unsigned int line);
void operator delete(void* ptr, const char* filename, unsigned int line);

void* operator new(size_t size);
void operator delete(void* ptr);

#define new new(__FILE__, __LINE__)