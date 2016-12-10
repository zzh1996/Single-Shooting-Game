#ifndef STG_CANVAS_H
#define STG_CANVAS_H

#include "headers.h"

class Canvas {
public:
    Fl_Offscreen scr;

    Canvas() : scr(
#ifndef __linux__
            fl_create_offscreen(600, 600)
#endif
    ) {}

    ~Canvas() {}

    void draw_bg() {
        Images::bg.draw(0, 0);
    }

    void draw_plane(int x, int y) {
        Images::player.draw(x, y);
    }
};

#endif //STG_CANVAS_H
