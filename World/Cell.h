#ifndef _Cell_h_
#define _Cell_h_

#include <algorithm>

class Cell {
   private:
    int type;
    float x;
    float y;

    float forceX;
    float forceY;

   public:
    Cell(int type, float x, float y) : type(type), x(x), y(y) {
        forceX = 0;
        forceY = 0;
    };

    ~Cell(){};

    void addForce(const float forceX, const float forceY);

    void multiplyForce(const float factor);

    // Move in delta time
    void move(const float &delaTime, const int &minX, const int &maxX,
              const int &minY, const int &maxY);

    float getX() const { return x; }
    float getY() const { return y; }

    void clearForce() {
        forceX = 0;
        forceY = 0;
    }

    void setForce(const float forceX, const float forceY) {
        this->forceX = forceX;
        this->forceY = forceY;
    }

    int getType() const { return type; }
};

#endif  // _Cell_h_