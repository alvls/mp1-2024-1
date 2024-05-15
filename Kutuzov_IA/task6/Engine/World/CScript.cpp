#include "CScript.h"
#include "CObject.h"

using namespace std;

// CScript
CScript::CScript(CObject* InOwner, string Name) : CEntity(InOwner->GetWorld(), Name)
{
	if (InOwner)
		Owner = InOwner;

	else
		throw (exception("Invalid Owner pointer!"));
}

// Owner
CObject* CScript::GetOwner() { return Owner; }
