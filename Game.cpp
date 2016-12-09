#include "headers.h"

void Game::move_objects() {
    if (Up)
        planeY -= planeSpeed;
    if (Down)
        planeY += planeSpeed;
    if (Left)
        planeX -= planeSpeed;
    if (Right)
        planeX += planeSpeed;
}