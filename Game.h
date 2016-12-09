#ifndef STG_GAME_H
#define STG_GAME_H

#include "headers.h"

class Game{
public:
    int planeX,planeY;
    bool Up=false,Down=false,Left=false,Right=false;
    int planeSpeed=5;
    Game():planeX(300),planeY(500){}
    ~Game(){}
    void move_objects();
};

#endif //STG_GAME_H
