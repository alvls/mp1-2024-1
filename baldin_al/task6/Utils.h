#pragma once

#include "Common.h"

void gotoxy(int x, int y);

bool fileExists(const string& filename);

void UpdateSettings(int width_ = -1, int height_ = -1, int max_len = -1, float snakeSpeed_ = -1.0f,
    char snakeSymbol_ = '\0', char wallSymbol_ = '\0', char foodSymbol_ = '\0');


void changeDiff1();

void changeDiff2();

void changeDiff3();


void changeSize();

void changeSnakeSymbol();

void changeWallSymbol();

void changeFoodSymbol();

void changeWinSize();


void ResultsTable();


void writeGameResultToFile(const GameResult& result);

void SetSetting(string filename);

void ClearGameResults(string filename);