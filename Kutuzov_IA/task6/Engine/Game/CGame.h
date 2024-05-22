#pragma once
#include "DataTypes.h"
#include <string>

class CWorld;
class CGameRender;
class CPlayerController;

// Main game class, handles everything else
class CGame
{
protected:
	CWorld* GameWorld;
	CGameRender* GameRender;
	CPlayerController* PlayerController;

	TCamera Camera;
	float TargetFPS;
	float DeltaTimeLimit; // Limits the delta time, useful for stability

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

	// Returns PlayerController
	CPlayerController* GetPlayerController();

	// Returns Camera
	TCamera& GetCamera();

};

