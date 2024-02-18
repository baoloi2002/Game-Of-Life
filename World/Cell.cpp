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
    const float dx = forceX * delaTime;
    const float dy = forceY * delaTime;

    // Move X
    x += dx;
    // Move Y
    y += dy;

    x = std::max(minX * 1.0f, std::min(maxX * 1.0f, x));
    y = std::max(minY * 1.0f, std::min(maxY * 1.0f, y));
}