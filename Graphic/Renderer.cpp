#include "Renderer.h"

Renderer* Renderer::pinstance_{nullptr};
std::mutex Renderer::mutex_;

Renderer* Renderer::GetInstance() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (pinstance_ == nullptr) {
        pinstance_ = new Renderer();
    }
    return pinstance_;
}

bool Renderer::isOpen() { return window.isOpen(); }

bool Renderer::pollEvent(sf::Event& event) { return window.pollEvent(event); }

void Renderer::close() { window.close(); }

void Renderer::clear(const sf::Color& color) { window.clear(color); }

void Renderer::display() {
    window.setView(view);
    window.display();
}

void Renderer::draw(
    const std::vector<std::pair<int, std::pair<float, float> > >& world) {
    // size of each cell
    const float cellWidth = window.getSize().x * 1.0 / resolutionX;
    const float cellHeight = window.getSize().y * 1.0 / resolutionY;

    for (const auto& u : world) {
        // Create a circle
        sf::CircleShape shape(std::min(cellWidth, cellHeight) / 2);
        shape.setPosition(u.second.first * cellWidth,
                          u.second.second * cellHeight);

        shape.setOrigin(shape.getRadius(), shape.getRadius());
        // Set color based on cell type
        switch (u.first) {
            case 0:
                shape.setFillColor(sf::Color::Red);
                break;
            case 1:
                shape.setFillColor(sf::Color::Green);
                break;
            case 2:
                shape.setFillColor(sf::Color::Blue);
                break;
            case 3:
                shape.setFillColor(sf::Color::Yellow);
                break;
            case 4:
                shape.setFillColor(sf::Color::Magenta);
                break;
            case 5:
                shape.setFillColor(sf::Color::Cyan);
                break;
            case 6:
                shape.setFillColor(sf::Color::White);
                break;
            default:
                shape.setFillColor(sf::Color::Black);
                break;
        }
        window.draw(shape);
    }
}
