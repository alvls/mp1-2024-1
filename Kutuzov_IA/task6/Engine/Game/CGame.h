#pragma once
class CWorld;
class CGameRender;

// Main game class, handles everything else
class CGame
{
protected:
	CWorld* GameWorld;
	CGameRender* GameRender;

	bool Running;

public:
	CGame();
	virtual ~CGame();

	// Runs the game
	void RunGame();

	// Quits the game
	void QuitGame();
};

