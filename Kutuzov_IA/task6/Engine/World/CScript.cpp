#include "CScript.h"
#include "CObject.h"

using namespace std;

// CScript
CScript::CScript(CObject* InOwner, string Name) : CEntity(InOwner->GetWorld(), Name)
{
	if (InOwner)
		Owner = InOwner;

	Owner->AddScript(this, Name);
}

// Owner
CObject* CScript::GetOwner() { return Owner; }
