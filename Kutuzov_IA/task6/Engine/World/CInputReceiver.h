#pragma once
#include <map>
#include <string>
#include "../Game/KeyCodes.h"

class CWorld;
class CGame;

// Iherit this class to add input receiving functionality to your classes
class CInputReceiver
{
	CGame* Game;
	bool DoesReceiveInput;
	std::string Name;

protected:

	// Override this to get input in other classes
	virtual void ReceiveInput(int Input, char Action);

public:
	CInputReceiver(CGame* InGame, std::string InName = "Input Receiver");
	~CInputReceiver();

	// Receive Input interface
	bool GetReceiveInput();
	void SetReceiveInput(bool InReceiveInput);

	// Name
	std::string GetName();

	// Actual Receiving Input
	void ReceiveInputCall(int Input, char Action);
};
