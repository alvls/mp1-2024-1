#include "CScript.h"
#include "CObject.h"

using namespace std;

// CScript
CScript::CScript(CObject* InOwner) : CEntity(InOwner->GetWorld())
{

}

// Executes the script
bool CScript::Execute()
{
	return Script();
}

// Owner
CObject* CScript::GetOwner() { return Owner; }
void CScript::SetOwner(CObject* InOwner)
{
	if (InOwner)
		Owner = InOwner;
}