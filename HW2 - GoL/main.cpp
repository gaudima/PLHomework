#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include "Gol.h"
#include "UiLayout.h"

using namespace std;

float getFPS(const sf::Time &time) {
    return (1000000.0f / time.asMicroseconds());
}

int main() {
    srand(time(NULL));
    Gol gol(10, 10, 30, 2);
    sf::Thread GolCycleTread([&]() {
        gol.run();
    });
    sf::RenderWindow window(sf::VideoMode(800, 600), "GameOfLife", sf::Style::Close);
    UiLayout layout(&gol);
    sf::Clock clock;
    GolCycleTread.launch();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                gol.stop();
                window.close();
            }
            layout.processEvent(event);
            gol.processEvent(event);
        }
        window.clear(sf::Color(25, 25, 25));
        gol.draw(window);
        layout.draw(window);
        window.display();
        window.setTitle("GameOfLife FPS:" + to_string(getFPS(clock.restart())));
    }
    return 0;
}

