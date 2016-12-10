#include "headers.h"

int main() {
    srand(time(0));
    STGWindow window;
    window.show();
    return Fl::run();
}