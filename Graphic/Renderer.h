#ifndef _Renderer_h_
#define _Renderer_h_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <mutex>
// Singleton class for rendering

class Renderer {
   private:
    sf::RenderWindow window;
    static Renderer* pinstance_;
    static std::mutex mutex_;
    int resolutionX;
    int resolutionY;

   protected:
    Renderer() : window(sf::VideoMode(1855, 900), "My window") {
        resolutionX = 371;
        resolutionY = 180;
    }
    ~Renderer() {}

   public:
    Renderer(Renderer& other) = delete;

    void operator=(const Renderer&) = delete;

    static Renderer* GetInstance();

    bool isOpen();

    bool pollEvent(sf::Event& event);

    void close();

    void clear(const sf::Color& color = sf::Color::Black);

    void display();

    void setResolution(const int x, const int y) {
        resolutionX = x;
        resolutionY = y;
    }

    void draw(
        const std::vector<std::pair<int, std::pair<float, float> > >& world);

    int getX() { return resolutionX; }
    int getY() { return resolutionY; }
};

#endif  // _Renderer_h_