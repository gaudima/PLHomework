#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include "Gol.h"
#include "GolDrawCell.h"
#include "TextBox.h"
#include "TextButton.h"
#include "ImageButton.h"
#include "unistd.h"

using namespace std;

float getFPS(const sf::Time& time) {
     return (1000000.0f / time.asMicroseconds());
}

int main()
{
    srand(time(NULL));
    Gol gol(10,10,30,2);
    sf::Thread GolCycleTread([&](){gol.run();});
    sf::RenderWindow window(sf::VideoMode(800,600), "GameOfLife", sf::Style::Close);
    TextBox tBox;
    TextButton tButton("Button");
    ImageButton iButton("Resources/icons/pause.png");
    iButton.onClick([&](){gol.pause();});
    iButton.setPosition(sf::Vector2f(150,0));
    tButton.setPosition(sf::Vector2f(50,0));
    sf::Clock Clock;
    GolCycleTread.launch();
    while (window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                gol.stop();
                window.close();
            }
            tBox.processEvent(event);
            tButton.processEvent(event);
            iButton.processEvent(event);
            gol.processEvent(event);
        }
        window.clear(sf::Color(25,25,25));
        gol.draw(window);
        window.draw(tButton);
        window.draw(tBox);
        window.draw(iButton);
        window.display();
        window.setTitle("GameOfLife FPS:" + to_string(getFPS(Clock.restart())));
    }
    return 0;
}

