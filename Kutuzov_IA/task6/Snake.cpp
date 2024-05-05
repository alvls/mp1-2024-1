#include "ScarletEngine.h"

using namespace std;

class CSnakeGame : public CGame
{
public:
	CSnakeGame()
	{
		GameWorld = new CWorld(this);
		GameRender = new CRenderOpenGL(this);
	}

	~CSnakeGame() {}
};




int main()
{
	CSnakeGame* SnakeGame = new CSnakeGame();

	SnakeGame->RunGame();

	delete SnakeGame;

	return 0;
}