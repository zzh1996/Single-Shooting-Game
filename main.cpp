#include "headers.h"

int main() {
    srand(time(0)); //init random seed
    STGWindow window;
    window.show();
    return Fl::run();
}