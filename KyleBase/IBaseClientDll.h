#pragma once

#include "ClientClass.h"

class IBaseClientDll
{
public:
	ClientClass* GetClientClasses() {
		using original_fn = ClientClass * (__thiscall*)(IBaseClientDll*);
		return (*(original_fn**)this)[8](this);
	}
};