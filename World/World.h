#ifndef _World_h_
#define _World_h_

#include <omp.h>
#include <time.h>

#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

#include "Cell.h"

class World {
   private:
    const int width;
    const int height;
    const int numberOfType;
    const int* numberOfCells;
    const float CoulombsConstant;
    const std::vector<std::vector<float> > rules;

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
    float distance(const Cell& cell1, const Cell& cell2);

    float force(const Cell& cell1, const Cell& cell2);

    std::pair<float, float> forceDirection(const Cell& cell1,
                                           const Cell& cell2);

    void insertCell(const int number);

    int getNumberOfCells() const { return cells.size(); }

    void removeCell(const int number);
};

#endif  // _World_h_