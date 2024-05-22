#pragma once
#include "CObject.h"

class CWorldScriptHandler : public CObject
{
	// An empty shell for holding world scripts
public:
	CWorldScriptHandler(CWorld* World, std::string Name = "World Script Handler");
};

