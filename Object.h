#ifndef STG_OBJECT_H
#define STG_OBJECT_H

#include "headers.h"

class Object {
    Fl_Image *image;
public:
    int X, Y, W, H;

    Object(int X, int Y, int W, int H) : X(X), Y(Y), W(W), H(H) {}

    Object(int X, int Y, Fl_Image &i) : image(&i), X(X), Y(Y), W(i.w()), H(i.h()) {}

    virtual ~Object() {}

    virtual void draw() {
        image->draw(X, Y);
    }

    bool collides(Object &o) { //whether this collides with another object
        if (X + W < o.X) return false;
        if (o.X + o.W < X) return false;
        if (Y + H < o.Y) return false;
        if (o.Y + o.H < Y) return false;
        return true;
    }

    bool out_of_screen() {
        return X + W < 0 || X > 600 || Y + H < 0 || Y > 600;
    }
};

class Plane : public Object { //player
public:
    Plane(int X, int Y) : Object(X, Y, Images::player) {}
};

class Enemy : public Object {
public:
    int HP;
    int score;

    virtual void move(int px, int py)=0;

    Enemy(int X, int Y, Fl_Image &i, int HP, int score) : Object(X, Y, i), HP(HP), score(score) {}

    virtual ~Enemy() {}
};

class MovingEnemy : public Enemy {
    int SpeedX, SpeedY;
public:
    void move(int px, int py) {
        X += SpeedX;
        Y += SpeedY;
    }

    MovingEnemy() : Enemy(rand() % 600, 0, Images::enemy1, 3, 50), SpeedX(X < 300 ? rand() % 10 : -rand() % 10),
                    SpeedY(rand() % 5 + 2) {}
};

class RushingEnemy : public Enemy {
public:
    void move(int px, int py) {
        Y += 15;
        if (Y < py - 15)
            X += (px - X) * 15 / (py - Y);
    }

    RushingEnemy() : Enemy(rand() % 600, 0, Images::enemy2, 1, 80) {}
};

class BossEnemy : public Enemy {
    bool right;
public:
    void move(int px, int py) {
        if (right)
            X++;
        else
            X--;
        if (X < 0)
            right = true;
        if (X > 400)
            right = false;
    }

    BossEnemy() : Enemy(200, 100, Images::enemy3, 200, 20), right(true) {}
};

class Ammo : public Object {
public:
    Ammo(int X, int Y) : Object(X, Y, 10, 10) {}

    void draw() {
        fl_color(FL_WHITE);
        fl_pie(X, Y, 10, 10, 0, 360);
    }
};

enum fType {
    fLife, fWeapon, fAmmo
};

class Food : public Object {
    bool right;
public:
    Food(int X, int Y, Fl_Image &i) : Object(X, Y, i), right(rand() % 2) {}

    virtual ~Food() {}

    virtual fType get_type()=0;

    void move() {
        Y++;
        if (right)
            X++;
        else
            X--;
        if (X < 100)
            right = true;
        if (X > 500)
            right = false;
    }
};

class Food_Life : public Food {
public:
    Food_Life(int X, int Y) : Food(X, Y, Images::life) {}

    fType get_type() { return fLife; }
};

class Food_Weapon : public Food {
public:
    Food_Weapon(int X, int Y) : Food(X, Y, Images::weapon) {}

    fType get_type() { return fWeapon; }
};

class Food_Ammo : public Food {
public:
    Food_Ammo(int X, int Y) : Food(X, Y, Images::ammo) {}

    fType get_type() { return fAmmo; }
};


#endif //STG_OBJECT_H
