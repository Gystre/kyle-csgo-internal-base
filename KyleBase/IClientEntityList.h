#pragma once

//forward declare b/c c++ gay
class C_BaseEntity;

class IClientEntityList
{
public:
	C_BaseEntity* getClientEntity(int index) {
		using original_fn = C_BaseEntity * (__thiscall*)(IClientEntityList*, int);
		return (*(original_fn**)this)[3](this, index);
	}

	//from handle
	C_BaseEntity* getClientEntity(void* handle) {
		using original_fn = C_BaseEntity * (__thiscall*)(IClientEntityList*, void*);
		return (*(original_fn**)this)[4](this, handle);
	}
};