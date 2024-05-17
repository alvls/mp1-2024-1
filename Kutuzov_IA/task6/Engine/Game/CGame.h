#pragma once
#include "DataTypes.h"
#include <string>

class CWorld;
class CGameRender;

// Main game class, handles everything else
class CGame
{
protected:
	CWorld* GameWorld;
	CGameRender* GameRender;

	TCamera Camera;

	bool Running;

	std::string GameName;

public:
	CGame();
	virtual ~CGame();

	// Runs the game
	void RunGame();

	// Quits the game
	void QuitGame();

	// Returns the name of the game
	std::string GetGameName();
	
	// Returns GameWorld
	CWorld* GetWorld();

	// Returns GameRender
	CGameRender* GetRender();

	// Returns Camera
	TCamera& GetCamera();

};

