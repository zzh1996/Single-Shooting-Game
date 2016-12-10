#ifndef STG_GAME_H
#define STG_GAME_H

#include "headers.h"

class Game {
public:
    bool game_over= false;
    bool pause= false;
    Plane self;
    bool Up = false, Down = false, Left = false, Right = false;
    bool Space = false, Enter= false, PAUSE= false;
    bool WP1= false,WP2= false,WP3= false;
    int AmmoCoolDownCount;
    const int planeSpeed = 10,AmmoSpeed=15,AmmoCoolDown = 3;
    int life;
    int score;
    int weapon;
    int ammo;
    int InvincibleCount;
    int LaserCount;
    int WaveCount;
    list<Ammo> self_ammos,enemy_ammos;
    list<Enemy*> enemies;
    list<Food*> foods;

    Game() : self(0,0) {reset();}

    ~Game() {}

    void update_state();
    void shoot();
    void decrease_life();
    void die();
    void reset();
    void gen_food(int X,int Y);
};

#endif //STG_GAME_H
