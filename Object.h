#ifndef STG_OBJECT_H
#define STG_OBJECT_H

#include "headers.h"

class Object {
    Fl_Image *image;
public:
    int X,Y,W,H;
    Object(int X,int Y,int W,int H):X(X),Y(Y),W(W),H(H){}
    Object(int X,int Y,Fl_Image &i):image(&i),X(X),Y(Y),W(i.w()),H(i.h()){}
    virtual ~Object(){}
    virtual void draw(){
        image->draw(X,Y);
    }
    bool collides(Object &o) {
        if (X+W < o.X) return false;
        if (o.X+o.W < X) return false;
        if (Y+H < o.Y) return false;
        if (o.Y+o.H < Y) return false;
        return true;
    }
    bool out_of_screen(){
        return X+W<0||X>600||Y+H<0||Y>600;
    }
    bool across_screen(){
        return X<0||X+W>600||Y<0||Y+H>600;
    }
};

class Plane:public Object{
public:
    Plane(int X,int Y):Object(X,Y,Images::plane){}
};

class Enemy:public Object{
public:
    int HP;
    int score;
    virtual void move()=0;
    Enemy(int X,int Y,Fl_Image &i,int HP,int score):Object(X,Y,i),HP(HP),score(score){}
    virtual ~Enemy(){}
};

class MovingEnemy:public Enemy{
    int SpeedX,SpeedY;
public:
    void move(){
        X+=SpeedX;
        Y+=SpeedY;
    }
    MovingEnemy():Enemy(rand()%600,0,Images::plane1,3,100),SpeedX(rand()%20-10),SpeedY(rand()%5+2){}
};

class Ammo:public Object{
public:
    Ammo(int X,int Y):Object(X,Y,10,10){}
    void draw(){
        fl_color(FL_WHITE);
        fl_pie(X,Y,10,10,0,360);
    }
};


#endif //STG_OBJECT_H
