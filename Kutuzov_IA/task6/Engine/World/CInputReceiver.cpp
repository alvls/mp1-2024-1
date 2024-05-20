#include "CInputReceiver.h"
#include "../Game/CGame.h"
#include "../Game/CPlayerController.h"


CInputReceiver::CInputReceiver(CGame* InGame, std::string InName): Game(InGame), Name(InName)
{
	DoesReceiveInput = true;
	if (Game)
		Game->GetPlayerController()->SubscribeToInput(this);
}

CInputReceiver::~CInputReceiver()
{
	if (Game)
		Game->GetPlayerController()->UnSubscribeToInput(this);
}

bool CInputReceiver::GetReceiveInput()
{
	return DoesReceiveInput;
}

void CInputReceiver::SetReceiveInput(bool InReceiveInput)
{
	DoesReceiveInput = InReceiveInput;
}

std::string CInputReceiver::GetName()
{
	return Name;
}

void CInputReceiver::ReceiveInputCall(int Input, char Action)
{
	ReceiveInput(Input, Action);
}


void CInputReceiver::ReceiveInput(int Input, char Action) {}