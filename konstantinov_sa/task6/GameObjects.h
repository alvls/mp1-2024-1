#pragma once
//#include <iostream>


class Game;

class Gobject {
    friend class Game;
    static Game* gamep;
    
public:
    static char defaultsymbol;
    char symbol;// = defaultsymbol;
    Gobject() {
        symbol = defaultsymbol;
        //std::cout << "Gobject symbol rewrite \n";
    }
    virtual void interact(Gobject ob); //будут разные перегрузки для разных классов-наследников
};



class Wall : public Gobject {
    static char defaultsymbol; //это статическое поле дочернего класса со своим значением
public:
    Wall() :Gobject(){

        symbol = defaultsymbol; //повторяется так как в конструкторе Gobject будет присвоено значение статического поля класса Gobject, а не Wall
        //std::cout << "WALL symbol rewrite \n";
    }
};
