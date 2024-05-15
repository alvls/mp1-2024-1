#pragma once
#include "CEntity.h"
class CObject;

class CScript : public CEntity
{
protected:
	CObject* Owner;


public:
	CScript(CObject* InOwner, std::string Name = "Script");

	// Owner
	CObject* GetOwner();
};

