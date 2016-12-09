#include "headers.h"

int STGWindow::handle(int event) {
    switch (event) {
        case FL_KEYDOWN:
            switch (Fl::event_key()) {
                case FL_Left:
                    game.Left = true;
                    break;
                case FL_Right:
                    game.Right = true;
                    break;
                case FL_Up:
                    game.Up = true;
                    break;
                case FL_Down:
                    game.Down = true;
                    break;
                default:
                    break;
            }
            break;
        case FL_KEYUP:
            switch (Fl::event_key()) {
                case FL_Left:
                    game.Left = false;
                    break;
                case FL_Right:
                    game.Right = false;
                    break;
                case FL_Up:
                    game.Up = false;
                    break;
                case FL_Down:
                    game.Down = false;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    return 1;
}

void STGWindow::draw() {
#ifndef __linux__
    fl_begin_offscreen(canvas.scr);
#endif
    canvas.draw_bg();
    canvas.draw_plane(game.planeX, game.planeY);
#ifndef __linux__
    fl_end_offscreen();
    fl_copy_offscreen(0, 0, 600, 600, canvas.scr, 0, 0);
#endif
}

STGWindow *STGWindow::instance;

void STGWindow::update() {
    instance->game.move_objects();
    instance->redraw();
}
