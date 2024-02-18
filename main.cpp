#include <time.h>

#include <iostream>
#include <vector>

#include "Graphic/Renderer.h"
#include "World/World.h"

const int X = 1865 / 5;
const int Y = 900 / 5;
const float CoulombsConstant = 1;
const float baseForce = 1;
const float deltaForce = -0.28;
const int numberOfType = 7;

std::vector<std::vector<float> > rules(numberOfType,
                                       std::vector<float>(numberOfType, 0));
int numberOfCells[numberOfType];

int main() {
    srand(time(nullptr));

    for (int i = 0; i < numberOfType; i++) {
        for (int j = 0; j < numberOfType; j++) {
            // rules[i][(i + j) % numberOfType] = baseForce + deltaForce * j;
            rules[i][(i + j) % numberOfType] = rand() % 100 / 100.0;
            if (rand() % 2 == 0) rules[i][(i + j) % numberOfType] *= -1;
        }
        // rules[i][i] = 1;
    }

    for (int i = 0; i < numberOfType; i++) {
        numberOfCells[i] = 500;
    }

    // Create a world
    World world(X, Y, numberOfType, numberOfCells, CoulombsConstant, rules);

    // create the window
    Renderer* renderer = Renderer::GetInstance();
    renderer->setResolution(X, Y);

    // start time
    clock_t start = clock();

    float FPS = 0;

    // run the program as long as the window is open
    while (renderer->isOpen()) {
        // check all the window's events that were triggered since the last
        // iteration of the loop
        sf::Event event;
        while (renderer->pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) renderer->close();

            // mouse scroll event update view
            if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                    if (event.mouseWheelScroll.delta > 0) {
                        renderer->setViewZoom(0.9);
                    } else {
                        renderer->setViewZoom(1.1);
                    }
                }
            }
        }
        // Calculate delta time
        const float deltaTime = (float)(clock() - start) / CLOCKS_PER_SEC;
        start = clock();

        FPS = FPS * 0.7 + 0.3 / deltaTime;
        std::cout << "FPS: " << FPS << std::endl;

        // Run the world
        world.run(deltaTime);

        // clear the window with black color
        renderer->clear();

        // Draw the world
        renderer->draw(world.display(renderer->getX(), renderer->getY()));

        // end the current frame
        renderer->display();
    }

    return 0;
}
