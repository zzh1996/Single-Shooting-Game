#ifndef STG_CANVAS_H
#define STG_CANVAS_H

#include "headers.h"

class Canvas{
public:
    Fl_Offscreen scr;
    Canvas():scr(fl_create_offscreen(600,600)){}
    ~Canvas(){}
    void draw_bg(){
        fl_begin_offscreen(scr);
        Images::bg.draw(0, 0);
        fl_end_offscreen();
    }
    void draw_plane(int x,int y){
        fl_begin_offscreen(scr);
        Images::plane.draw(x, y);
        fl_end_offscreen();
    }
};

#endif //STG_CANVAS_H
