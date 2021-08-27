#pragma once

#include "RecvProps.h"
#include "Singleton.h"
#include <unordered_map>

struct NetvarData
{
	bool DataMapVar;
	RecvProp* PropPtr;
	size_t Offset;
};

class NetvarManager : public Singleton<NetvarManager>
{
private:
	std::unordered_map<unsigned int, std::unordered_map<unsigned int, NetvarData>> netvarsMap;

	void dumpTableRecursively(char* name, RecvTable* table, size_t offset = 0);
	void dumpTableRecursivelyToFile(char* name, RecvTable* table, std::ofstream& file, size_t offset = 0);
public:
	void init();
	unsigned short getOffset(const char* table, const char* prop);
	RecvProp* getProperty(const char* table, const char* prop);
};

#define OffsetFn(type, var, offset) \
	type& var() { \
		return *(type*)(uintptr_t(this) + offset); \
	} \

#define NetvarFn(type, var, table, prop) \
	type& var() { \
		static auto _offset = NetvarManager::Get().getOffset(table, prop); \
		return *(type*)(uintptr_t(this) + _offset); \
	} \

#define NetvarPtrFn(type, var, table, prop) \
	type* var() { \
		static auto _offset = NetvarManager::Get().getOffset(table, prop); \
		return (type*)(uintptr_t(this) + _offset); \
	} \

#define NetvarOffsetFn(type, var, table, prop, offset) \
	type& var() { \
		static auto _offset = NetvarManager::Get().getOffset(table, prop); \
		return *(type*)(uintptr_t(this) + _offset + offset); \
	} \