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
            const float f = force(cells[i], cells[j]);
            const auto direction = forceDirection(cells[i], cells[j]);

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
        const float x = cell.getX() * widthratio;
        const float y = cell.getY() * heightratio;
        result.emplace_back(cell.getType(), std::make_pair(x, y));
        // if (x >= 0 && x <= windowWidth && y >= 0 && y <= windowHeight) {

        // }
    }

    return std::move(result);
}

float World::distanceSquare(const Cell& cell1, const Cell& cell2) {
    const float dx = cell1.getX() - cell2.getX();
    const float dy = cell1.getY() - cell2.getY();
    return dx * dx + dy * dy;
}

float World::distance(const Cell& cell1, const Cell& cell2) {
    return std::sqrt(this->distanceSquare(cell1, cell2));
}

float World::force(const Cell& cell1, const Cell& cell2) {
    const float alpha = 10;
    // If distance < 5 then force increase from 0 to 1 when distance decrease
    // If distance > 5 and <= 10 then force decrease from 0 to rule when
    // distance increase If distance > 10 and <=15 then force decrease from rule
    // to 0 when distance increase If distance > 15 then force = 0
    const float distance = this->distance(cell1, cell2);

    const float rule = rules[cell1.getType()][cell2.getType()];
    float result = 0;
    if (distance < 0) {
        result = -1;
    } else if (distance < alpha) {
        result = -1 * (1 - distance / alpha);
    } else if (distance <= alpha * 2) {
        result = rule * (distance - alpha) / alpha;
    } else if (distance <= alpha * 3) {
        result = rule * (alpha * 3 - distance) / alpha;
    }
    return result * CoulombsConstant;
}

std::pair<float, float> World::forceDirection(const Cell& cell1,
                                              const Cell& cell2) {
    const float dx = cell2.getX() - cell1.getX();
    const float dy = cell2.getY() - cell1.getY();
    // Normalize the direction
    const float distance = std::sqrt(dx * dx + dy * dy);
    if (distance == 0) {
        return std::make_pair(0, 0);
    }
    return std::make_pair(dx / distance, dy / distance);
}

void World::insertCell(const int number) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> xDistribution(0, width - 1);
    std::uniform_int_distribution<> yDistribution(0, height - 1);

    for (int i = 0; i < number; i++) {
        cells.emplace_back(rand() % numberOfType, xDistribution(gen),
                           yDistribution(gen));
    }
}

void World::removeCell(const int number) {
    if (number >= cells.size()) {
        cells.clear();
    } else {
        cells.erase(cells.begin(), cells.begin() + number);
    }
}