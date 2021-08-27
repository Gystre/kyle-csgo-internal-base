#include "pch.h"
#include "HacksContainer.h"
#include "BunnyHop.h"

void HacksContainer::Init()
{
	//push all hacks to global vector array
	hacks.push_back(std::make_shared<BunnyHop>());
}