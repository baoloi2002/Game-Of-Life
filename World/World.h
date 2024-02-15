#ifndef _World_h_
#define _World_h_

#include <omp.h>
#include <time.h>

#include <cmath>
#include <cstdlib>
#include <random>
#include <vector>

#include "Cell.h"

class World {
   private:
    const int width;
    const int height;
    const int numberOfType;
    const int* numberOfCells;
    const float CoulombsConstant;
    std::vector<std::vector<float> > rules;

    // List of cells
    std::vector<Cell> cells;

   public:
    World(const int width, const int height, const int numberOfType,
          const int numberOfCells[], const float CoulombsConstant,
          const std::vector<std::vector<float> > rules)
        : width(width),
          height(height),
          numberOfType(numberOfType),
          numberOfCells(numberOfCells),
          CoulombsConstant(CoulombsConstant),
          rules(rules) {
        init();
    };

    ~World() { delete[] numberOfCells; };

    void init();

    void run(const float deltaTime);
    std::vector<std::pair<int, std::pair<float, float> > > display(
        const int windowWidth, const int windowHeight);

    float distanceSquare(const Cell& cell1, const Cell& cell2);
    float force(const Cell& cell1, const Cell& cell2);
    std::pair<float, float> forceDirection(const Cell& cell1,
                                           const Cell& cell2);
};

#endif  // _World_h_