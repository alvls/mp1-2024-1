#pragma once
class Game;
class Gobject {
    friend class Game;
protected:

    Game* game;
    char symbol;
    int x;
    int y;
    
public:
    Gobject() { symbol = '0'; };
    Gobject(char symbol, Game* gamep, int x=0, int y=0): symbol(symbol), game(gamep), x(x),y(y) {
    }

    virtual ~Gobject() = 0 {};
};



class Wall : public Gobject {

public:
    Wall(Game* gamep, int x=0, int y=0) :Gobject('W', gamep, x,y) {
    }
    ~Wall() {};
};

class ActiveGobject :public Gobject {
public:
    ActiveGobject(char symbol, Game* gamep, int x = 0, int y = 0) :Gobject(symbol, gamep, x, y) {};
    virtual void update() = 0;
    virtual ~ActiveGobject() = 0 {};
};

class Snake : public ActiveGobject {
public:
    Snake(Game* gamep, int x = 0, int y = 0) :ActiveGobject('S', gamep, x, y) {
    }

    void crawl(int tx, int ty);

    void update() override;
    ~Snake() {};
};