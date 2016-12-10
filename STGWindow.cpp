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
                    break;
                case FL_Enter:
                    game.Enter=true;
                    break;
                case 'p':
                    game.PAUSE=true;
                    break;
                case 'z':
                    game.WP1=true;
                    break;
                case 'x':
                    game.WP2=true;
                    break;
                case 'c':
                    game.WP3=true;
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
                case ' ':
                    game.Space=false;
                    break;
                case FL_Enter:
                    game.Enter=false;
                    break;
                case 'p':
                    game.PAUSE=false;
                    break;
                case 'z':
                    game.WP1=false;
                    break;
                case 'x':
                    game.WP2=false;
                    break;
                case 'c':
                    game.WP3=false;
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
    Fl_Window::draw();
    canvas.draw_bg();
    for(Ammo &a:game.self_ammos) {
        a.draw();
    }
    for(auto p:game.enemies) {
        p->draw();
    }
    for(auto p:game.foods) {
        p->draw();
    }
    if(game.InvincibleCount){
        fl_color(FL_YELLOW);
        fl_circle(game.self.X+game.self.W/2,game.self.Y+game.self.H/2+5,50);
    }
    if(game.LaserCount){
        fl_rectf(game.self.X,0,game.self.W,game.self.Y+game.self.H,FL_WHITE);
    }
    if(game.WaveCount){
        fl_rectf(0,game.WaveCount-5,600,10,FL_WHITE);
    }
    game.self.draw();
    for(int i=0;i<game.life;i++) {
        fl_color(FL_RED);
        fl_pie(10 + 15 * i, 580, 10, 10, 0, 360);
    }
    for(int i=0;i<game.weapon;i++) {
        fl_color(FL_GREEN);
        fl_pie(580-15*i, 580, 10, 10, 0, 360);
    }
    char s[15];
    sprintf(s,"%06d",game.score);
    fl_font(FL_COURIER_BOLD,20);
    fl_color(FL_WHITE);
    fl_draw(s,10,30);
    if(game.game_over){
        fl_font(FL_TIMES_BOLD,100);
        fl_color(FL_DARK_YELLOW);
        fl_draw("Game Over",50,300);
        fl_font(FL_TIMES,30);
        fl_color(FL_WHITE);
        fl_draw("Press Enter to restart",175,400);
    }
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
