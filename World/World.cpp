#include "World.h"

void World::init() {
    // Calculate the total size
    int total = std::accumulate(numberOfCells, numberOfCells + numberOfType, 0);

    // Reserve memory for the cells vector
    cells.reserve(total);

    // Create cells randomly
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> xDistribution(0, width - 1);
    std::uniform_int_distribution<> yDistribution(0, height - 1);

    for (int i = 0; i < numberOfType; i++) {
        for (int j = 0; j < numberOfCells[i]; j++) {
            cells.emplace_back(i, xDistribution(gen), yDistribution(gen));
        }
    }
}

void World::run(const float deltaTime) {
    // Calculate the force between cells

    for (int i = 0; i < cells.size(); i++) {
        float totalForceX = 0;
        float totalForceY = 0;
        for (int j = 0; j < cells.size(); j++) {
            float f = force(cells[i], cells[j]);
            auto direction = forceDirection(cells[i], cells[j]);

            totalForceX += f * direction.first;
            totalForceY += f * direction.second;
        }
        cells[i].setForce(totalForceX, totalForceY);
    }

    // Move cells
    for (int i = 0; i < cells.size(); i++) {
        cells[i].move(deltaTime, 0, width, 0, height);
    }
}

std::vector<std::pair<int, std::pair<float, float> > > World::display(
    const int windowWidth, const int windowHeight) {
    std::vector<std::pair<int, std::pair<float, float> > > result;
    result.reserve(cells.size());

    const float widthratio = windowWidth * 1.0 / width;
    const float heightratio = windowHeight * 1.0 / height;
    // Project cells to the window
    for (const auto& cell : cells) {
        float x = cell.getX() * widthratio;
        float y = cell.getY() * heightratio;

        if (x >= 0 && x < windowWidth && y >= 0 && y < windowHeight) {
            result.emplace_back(cell.getType(), std::make_pair(x, y));
        }
    }

    return std::move(result);
}

float World::distanceSquare(const Cell& cell1, const Cell& cell2) {
    const float dx = cell1.getX() - cell2.getX();
    const float dy = cell1.getY() - cell2.getY();
    return dx * dx + dy * dy;
}

float World::force(const Cell& cell1, const Cell& cell2) {
    const float distance = this->distanceSquare(cell1, cell2);
    if (distance > 0 && distance < 1600)
        return CoulombsConstant * rules[cell1.getType()][cell2.getType()] /
               std::sqrt(distance);
    return 0;
}

std::pair<float, float> World::forceDirection(const Cell& cell1,
                                              const Cell& cell2) {
    return std::make_pair(cell2.getX() - cell1.getX(),
                          cell2.getY() - cell1.getY());
}