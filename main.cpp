#include <time.h>

#include <iostream>
#include <vector>

#include "Graphic/Renderer.h"
#include "World/World.h"

int main() {
    srand(time(nullptr));

    const int numberOfType = 7;
    //  force rules
    std::vector<std::vector<float> > rules(numberOfType,
                                           std::vector<float>(numberOfType, 0));
    // random from 5 to 19
    for (int i = 0; i < numberOfType; i++) {
        for (int j = 0; j < numberOfType; j++) {
            rules[i][j] = 1 + rand() % 4;
            if (i != j && rand() % 2 == 0) rules[i][j] *= -1;
        }
    }
    std::cout << "Rules: " << std::endl;
    for (int i = 0; i < numberOfType; i++) {
        for (int j = 0; j < numberOfType; j++) {
            std::cout << rules[i][j] << " ";
        }
        std::cout << std::endl;
    }

    int numberOfCells[numberOfType];
    for (int i = 0; i < numberOfType; i++) {
        numberOfCells[i] = 400;
    }

    // Create a world
    World world(371, 180, numberOfType, numberOfCells, 1, rules);

    // create the window
    Renderer* renderer = Renderer::GetInstance();

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
