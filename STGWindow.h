#ifndef STG_STGWINDOW_H
#define STG_STGWINDOW_H

#include "headers.h"

class STGWindow : public Fl_Window {
    static STGWindow *instance;
    Timer timer;
    Canvas canvas;
    Game game;

    int handle(int event);

    void draw();

    static void update();

public:
    STGWindow() : Fl_Window(600, 600, "Single Shooting Game"), timer(0.02, update) {
        instance = this;
    }

    ~STGWindow() {}
};

#endif //STG_STGWINDOW_H
