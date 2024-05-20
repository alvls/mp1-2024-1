#include "CPlayerController.h"
#include "../World/CInputReceiver.h"

CPlayerController::CPlayerController(CGame* InGame): Game(InGame) 
{
	IsReceivingInput = true;
}

CPlayerController::~CPlayerController() {}

bool CPlayerController::GetIsReceivingInput()
{
	return IsReceivingInput;
}

void CPlayerController::SetIsReceivingInput(bool InIsReceivingInput)
{
	IsReceivingInput = InIsReceivingInput;
}

void CPlayerController::SendInput(int Input, char Action)
{
	if (IsReceivingInput)
		for (auto Sub : InputSubscribers)
			if (Sub.second->GetReceiveInput())
				Sub.second->ReceiveInputCall(Input, Action);
}

void CPlayerController::SubscribeToInput(CInputReceiver* InputReceiver)
{
	InputSubscribers[InputReceiver->GetName()] = InputReceiver;
}

void CPlayerController::UnSubscribeToInput(CInputReceiver* InputReceiver)
{
	if (InputSubscribers.count(InputReceiver->GetName()) > 0)
		InputSubscribers.erase(InputReceiver->GetName());
}

CGame* CPlayerController::GetGame() { return Game; }
