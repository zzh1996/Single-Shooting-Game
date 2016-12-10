#include "headers.h"

void Game::update_state() {
    if (game_over || win) {
        if (Enter) { //game over, press enter to continue
            reset();
            game_over = false;
            win = false;
        }
        return;
    }
    if (PAUSE) {
        pause = !pause;
        PAUSE = false;
    }
    if (pause)
        return; //do not update state

    //player move
    if (Up)
        if (self.Y > 0)
            self.Y -= planeSpeed;
    if (Down)
        if (self.Y + self.H < 600)
            self.Y += planeSpeed;
    if (Left)
        if (self.X > 0)
            self.X -= planeSpeed;
    if (Right)
        if (self.X + self.W < 600)
            self.X += planeSpeed;

    //player shoot
    if (!Space) {
        if (AmmoCoolDownCount == 0) {
            shoot();
            AmmoCoolDownCount = AmmoCoolDown;
        } else
            AmmoCoolDownCount--;
    }

    //use weapons
    if (weapon) {
        if (WP1 && !InvincibleCount) {
            weapon--;
            WP1 = false;
            InvincibleCount = 200;
        }
        if (WP2 && !LaserCount) {
            weapon--;
            WP2 = false;
            LaserCount = 100;
        }
        if (WP3 && !WaveCount) {
            weapon--;
            WP3 = false;
            WaveCount = 600;
        }
    }

    //update weapon timer
    if (InvincibleCount > 0)
        InvincibleCount--;
    if (LaserCount > 0)
        LaserCount--;
    if (WaveCount > 0)
        WaveCount -= 5;

    //update ammo
    for (auto i = self_ammos.begin(); i != self_ammos.end();) {
        i->Y -= AmmoSpeed;
        if (i->out_of_screen()) {
            i = self_ammos.erase(i);
        } else
            i++;
    }

    //update enemies
    for (auto i = enemies.begin(); i != enemies.end();) {
        Enemy *e = *i;
        bool del = false;

        e->move(self.X - self.W / 2, self.Y - self.H / 2); //enemies move

        if (e->collides(self)) { //player collides with enemy
            decrease_life();
            e->HP -= 10;
            score += e->score;
        }

        if (LaserCount && e->X < self.X + self.W && e->X + e->W > self.X) { //laser collides with enemy
            e->HP--;
            score += e->score;
        }

        if (WaveCount && e->Y <= WaveCount + 5 && e->Y + e->H >= WaveCount - 5) { //wave collides with enemy
            e->HP--;
            score += e->score;
        }

        for (auto a = self_ammos.begin(); a != self_ammos.end();) { //ammo collides with enemy
            if (e->collides(*a)) {
                a = self_ammos.erase(a);
                e->HP--;
                score += e->score;
            }
            a++;
        }

        if ((*i)->out_of_screen()) { //enemy goes out of screen
            del = true;
        }

        if (e->HP <= 0) { //enemy dies
            del = true;
            gen_food(e->X + e->W / 2, e->Y + e->H / 2);
        }

        if (del) { //delete enemy
            delete *i;
            i = enemies.erase(i);
        } else
            i++;
    }

    for (auto i = foods.begin(); i != foods.end();) { //update foods
        Food *f = *i;

        f->move();

        if (f->out_of_screen()) { //food goes out of screen
            delete f;
            i = foods.erase(i);
        } else if (f->collides(self)) { //food collides with player
            switch (f->get_type()) {
                case fLife:
                    if (life < 10)
                        life++; //add life
                    break;
                case fWeapon:
                    if (weapon < 10)
                        weapon++; //add weapon
                    break;
                case fAmmo:
                    if (ammo < 3)
                        ammo++; //add ammo
                    break;
                default:
                    break;
            }
            delete f; //delete food
            i = foods.erase(i);
            score += 50;
        } else
            i++;
    }

    stagecount--; //stage timer
    switch (stage) {
        case 0: //initial state
            stage = 1;
            stagecount = 500;
            break;
        case 1: //enemy1
            if (stagecount <= 0) {
                stage = 2;
                stagecount = 500;
            }
            if (rand() % 100 < 5)
                enemies.push_back(new MovingEnemy());
            break;
        case 2: //enemy2
            if (stagecount <= 0) {
                stage = 3;
                enemies.push_back(new BossEnemy());
            }
            if (rand() % 100 < 5)
                enemies.push_back(new RushingEnemy());
            break;
        case 3: //boss
            if (enemies.empty()) {
                win = true;
            }
            break;
        default:
            break;
    }
}

void Game::shoot() {
    switch (ammo) {
        case 1:
            self_ammos.push_back(Ammo(self.X + self.W / 2 - 5, self.Y));
            break;
        case 2:
            self_ammos.push_back(Ammo(self.X - 5, self.Y + self.H));
            self_ammos.push_back(Ammo(self.X + self.W - 5, self.Y + self.H));
            break;
        case 3:
            self_ammos.push_back(Ammo(self.X + self.W / 2 - 5, self.Y));
            self_ammos.push_back(Ammo(self.X - 5, self.Y + self.H));
            self_ammos.push_back(Ammo(self.X + self.W - 5, self.Y + self.H));
            break;
        default:
            break;
    }
}

void Game::decrease_life() {
    if (!InvincibleCount) {
        life--;
        ammo = 1;
    }
    if (life == 0) {
        die();
    }
}

void Game::die() {
    game_over = true;
}

void Game::reset() {
    self.X = 300 - self.W / 2;
    self.Y = 500;
    AmmoCoolDownCount = 0;
    life = 3;
    score = 0;
    weapon = 3;
    ammo = 1;
    InvincibleCount = 0;
    LaserCount = 0;
    WaveCount = 0;
    stage = 0;
    stagecount = 0;
    self_ammos.clear();
    while (!enemies.empty()) { //clear enemies
        delete enemies.front();
        enemies.pop_front();
    }
    while (!foods.empty()) { //clear foods
        delete foods.front();
        foods.pop_front();
    }
}

void Game::gen_food(int X, int Y) { //generate food at dead enemies
    X -= 15;
    Y -= 15;
    switch (rand() % 20) {
        case 0:
            foods.push_back(new Food_Life(X, Y));
            break;
        case 1:
            foods.push_back(new Food_Weapon(X, Y));
            break;
        case 2:
            foods.push_back(new Food_Ammo(X, Y));
            break;
        default:
            break;
    }
}