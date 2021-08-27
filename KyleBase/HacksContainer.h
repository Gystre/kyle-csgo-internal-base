#pragma once

#include "Hack.h"

class HacksContainer : public Singleton<HacksContainer>
{
public:
	std::vector<std::shared_ptr<Hack>> hacks;
	void Init();
};