#pragma once
//#include <iostream>



class Game;

enum class Otype {
    None, Air, Wall, Snake, Food
};

class Gobject {
    friend class Game;
protected:
    Otype type;
    Game* game;
    char symbol;
    int x; //может и не понадобятся
    int y;
    
public:
    static char defaultsymbol;
    Gobject() { type = Otype::None; symbol = '0'; };
    Gobject(Otype type, char symbol, Game* gamep, int x=0, int y=0):type(type), symbol(symbol), game(gamep), x(x),y(y) {
    }
    //virtual void interact(Gobject ob); //будут разные перегрузки для разных классов-наследников
    virtual void update(){}

    virtual ~Gobject() {};
};



class Wall : public Gobject {

public:
    Wall(Game* gamep, int x=0, int y=0) :Gobject(Otype::Wall, 'W', gamep, x,y) {
    }
};

class Air : public Gobject {
public:
    Air(Game* gamep, int x = 0, int y = 0) :Gobject(Otype::Air, '.', gamep, x, y) {
    }
};

class Snake : public Gobject {
public:
    Snake(Game* gamep, int x = 0, int y = 0) :Gobject(Otype::Snake, 'S', gamep, x, y) {
    }

    void update() override;
};