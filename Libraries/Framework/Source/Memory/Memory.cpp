#include "FrameworkPCH.h"
#include "Utility/CPPList.h"

#undef new

CPPListHead g_Allocations;

struct MemoryObject : public CPPListNode
{
	const char* filename;
	unsigned int line;
	size_t size;
};

void PrintLeaks()
{
	for (CPPListNode* node = g_Allocations.GetHead(); node != 0; node = node->GetNext())
	{
		MemoryObject* memobj = (MemoryObject*)node;
		OutputMessage("%s(%d): size:%d\n", memobj->filename, memobj->line, memobj->size);
	}
}

void* operator new(size_t size, const char* filename, unsigned int line)
{
	void* ptr = malloc(sizeof(MemoryObject) + size);
	memset(ptr, 0, sizeof(MemoryObject) + size);
	MemoryObject* memobj = (MemoryObject*)ptr;

	memobj->filename = filename;
	memobj->line = line;
	memobj->size = size;

	g_Allocations.AddTail(memobj);

	return (char*)memobj + sizeof(MemoryObject);
}

void* operator new(size_t size)
{
	return operator new(size, "No filename", 0);
}

void operator delete(void* ptr)
{
	operator delete(ptr, "", 0);
}

void operator delete(void* ptr, const char* filename, unsigned int line)
{
	void* origptr = (char*)ptr - sizeof(MemoryObject);
	MemoryObject* memobj = (MemoryObject*)origptr;
	memobj->Remove();

	free(origptr);
}