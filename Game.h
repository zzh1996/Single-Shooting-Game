#ifndef STG_GAME_H
#define STG_GAME_H

#include "headers.h"

class Game {
public:
    Plane self;
    bool Up = false, Down = false, Left = false, Right = false;
    bool Space = false;
    int AmmoCoolDown = 3,AmmoCoolDownCount=0;
    int planeSpeed = 10,AmmoSpeed=15;
    int life=5;
    int score=0;
    list<Ammo> self_ammos,enemy_ammos;
    list<Enemy*> enemies;

    Game() : self(300,500) {}

    ~Game() {}

    void update_state();
    void shoot();
    void decrease_life();
    void gameover();
};

#endif //STG_GAME_H
