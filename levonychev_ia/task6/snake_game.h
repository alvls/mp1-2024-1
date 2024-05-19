#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>
#include <time.h>
#include <ciso646> 
#include <conio.h>
#include <stdio.h>
#include <string>
#include "objects.h"




class SnakeGame
{
	int WIDTH = 28;
	int HEIGHT = 17;
	int MAX_LEN = (WIDTH - 3) * (HEIGHT - 2);
	double SPEED = 0.5;
	void setcur(int x, int y);

public:
	void gameplay();

};
