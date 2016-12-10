#ifndef STG_CANVAS_H
#define STG_CANVAS_H

#include "headers.h"

class Canvas {
public:
    Fl_Offscreen scr;

    Canvas() : scr(
#ifndef __linux__ //disable buffer on linux due to bugs
            fl_create_offscreen(600, 600) //buffer
#endif
    ) {}

    ~Canvas() {}
};

#endif //STG_CANVAS_H
