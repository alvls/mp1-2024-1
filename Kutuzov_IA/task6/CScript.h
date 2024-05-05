#pragma once
#include "CEntity.h"
class CObject;

class CScript : public CEntity
{
protected:
	CObject* Owner;

protected:
	virtual bool Script() = 0; // To be overriden by child classes

public:
	CScript(CObject* InOwner);

	// Executes the script
	bool Execute();

	// Owner
	CObject* GetOwner();
	void SetOwner(CObject* InOwner);
};

