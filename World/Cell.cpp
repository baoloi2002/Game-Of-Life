#include "Cell.h"

void Cell::addForce(const float forceX, const float forceY) {
    this->forceX += forceX;
    this->forceY += forceY;
}

void Cell::multiplyForce(const float factor) {
    forceX *= factor;
    forceY *= factor;
}

// Move in delta time
void Cell::move(const float &delaTime, const int &minX, const int &maxX,
                const int &minY, const int &maxY) {
    float dx = forceX * delaTime;
    float dy = forceY * delaTime;

    // Move X
    x += dx;
    if (x > maxX)
        x -= maxX;
    else if (x < minX)
        x += maxX;

    // Move Y
    y += dy;
    if (y > maxY)
        y -= maxY;
    else if (y < minY)
        y += maxY;
}