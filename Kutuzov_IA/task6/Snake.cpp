#include "Engine/ScarletEngine.h"
#include "CSnakeWorld.h"
#include <iostream>

using namespace std;

class CSnakeGame : public CGame
{
public:
	CSnakeGame()
	{
		GameName = "Snake";
		Camera.Resolution = TVector2D(1920, 1080);
		Camera.UnitsPerPixel = 1.f;

		TargetFPS = 60.f;

		GameWorld = new CSnakeWorld(this);
		GameRender = new CRenderOpenGL(this,
			{
				{"Square", TSpriteGL("Resources/ChibiZar.png",100, 100)},
				{"SnakeHead_F", TSpriteGL("Resources/SnakeHead_F.png",100, 100)},
				{"SnakeHead_B", TSpriteGL("Resources/SnakeHead_B.png",100, 100)},
				{"SnakeHead_R", TSpriteGL("Resources/SnakeHead_R.png",100, 100)},
				{"SnakeHead_L", TSpriteGL("Resources/SnakeHead_L.png",100, 100)},
				{"SnakeBody", TSpriteGL("Resources/SnakeBody.png",100, 100)},
				{"Wall", TSpriteGL("Resources/Wall.png",100, 100)},
				{ "Fruit", TSpriteGL("Resources/Fruit.png",50, 50)}
			});

		PlayerController = new CPlayerController(this);
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


