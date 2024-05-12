#pragma once

#include "Common.h"

class Settings {
public:
    int width = 20;
    int height = 10;
    float snakeSpeed = 0.5;
    int MaxLenSnake = (width - 2) * (height - 2);
    char snakeSymbol = 'O';
    char wallSymbol = '#';
    char foodSymbol = '*';

    Settings() {
        ifstream in(settings_file);
        if (in.is_open()) {
            in >> width >> height >> MaxLenSnake >> snakeSpeed >>
                snakeSymbol >> wallSymbol >> foodSymbol;
            in.close();
        }
        else throw "Не удалось открыть файл для считывания настроек игры";
    }
};