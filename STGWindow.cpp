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
                case ' ':
                    game.Space=true;
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
                case ' ':
                    game.Space=false;
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
    Fl_Window::draw();
    canvas.draw_bg();
    for(Ammo &a:game.self_ammos) {
        a.draw();
    }
    for(auto p:game.enemies) {
        p->draw();
    }
    game.self.draw();
    for(int i=0;i<game.life;i++) {
        fl_color(FL_RED);
        fl_pie(10 + 15 * i, 580, 10, 10, 0, 360);
    }
    char s[15];
    sprintf(s,"%06d",game.score);
    fl_font(FL_COURIER_BOLD,20);
    fl_color(FL_WHITE);
    fl_draw(s,10,30);
#ifndef __linux__
    fl_end_offscreen();
    fl_copy_offscreen(0, 0, 600, 600, canvas.scr, 0, 0);
#endif
}

STGWindow *STGWindow::instance;

void STGWindow::update() {
    instance->game.update_state();
    instance->redraw();
}
