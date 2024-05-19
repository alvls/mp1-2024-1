#pragma once
#include "windows.h"
#include "Game.h"
#include <memory>

//class Game;

class Gobject {
    friend class Game;
protected:

    Game* game;
    char symbol;
    int color;
    int x;
    int y;
    
public:
    Gobject() { symbol = '0'; };
    Gobject(char symbol, Game* gamep, int x=0, int y=0, int color = 0): symbol(symbol),color(color), game(gamep), x(x),y(y) {
    }
    

    virtual ~Gobject() = 0 {};
};



class Wall : public Gobject {

public:
    Wall(Game* gamep, int x=0, int y=0) :Gobject('#', gamep, x,y, 0) {
        
        if ((x + y) % 2)
            color = FOREGROUND_INTENSITY;
        else
            color = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
    }
    ~Wall() {};
};

class Food : public Gobject {

public:
    Food(Game* gamep, int x = 0, int y = 0) :Gobject('@', gamep, x, y, FOREGROUND_RED|FOREGROUND_INTENSITY) {
        game->foodcount++;
    }
    ~Food() {
        game->foodcount--;
    }
};

class ActiveGobject :public Gobject {
public:
    ActiveGobject(char symbol, Game* gamep, int x = 0, int y = 0, int color = 0) :Gobject(symbol, gamep, x, y, color) {};
    virtual void update() = 0 {};
    virtual ~ActiveGobject() = 0 {};
};



class Segment : public ActiveGobject {
protected:
    
    int tx;
    int ty;
    int id;
    
public:
    bool willgrow;
    shared_ptr<Segment> next;

    Segment(Game* gamep, int x = 0, int y = 0) :ActiveGobject('=', gamep, x, y, FOREGROUND_GREEN) {
        willgrow = 0;
    }
    void init(int id_, shared_ptr<Segment> next_ = nullptr) {
        if (id % 2)
            color = color | FOREGROUND_INTENSITY;
        next = next_;
    }
    void transmit(int nx, int ny);
    void update() override;

};

class Snake : public ActiveGobject {
    int dx;
    int dy;
    int growstate;
    shared_ptr<Segment> next;
    shared_ptr<Segment> tail;
public:
    Snake(Game* gamep, int x = 0, int y = 0) :ActiveGobject('S', gamep, x, y, FOREGROUND_GREEN|FOREGROUND_RED | FOREGROUND_INTENSITY) {
        growstate = 0;
    }

    void crawl(int tx, int ty);

    void update() override;
    ~Snake() {};
};