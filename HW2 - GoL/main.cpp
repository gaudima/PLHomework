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

using namespace std;

float getFPS(const sf::Time& time) {
     return (1000000.0f / time.asMicroseconds());
}

int main()
{
    srand(time(NULL));
    Gol gol(10,10,30,2);
    gol.debugOut();
    for(int i = 0; i < 10; i++)
    {
        gol.cycle();
        cout<<endl;
        gol.debugOut();
    }
    sf::RenderWindow window(sf::VideoMode(800,600), "GameOfLife", sf::Style::Close);
    bool paused = false;
    GolDrawCell cell;
    TextBox tBox;
    TextButton tButton("Button");
    ImageButton iButton("Resources/icons/pause.png");
    iButton.onClick([&](){paused=!paused;});
    iButton.setPosition(sf::Vector2f(150,0));
    tButton.setPosition(sf::Vector2f(50,0));
    sf::Clock Clock;
    while (window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
            tBox.processEvent(event);
            tButton.processEvent(event);
            iButton.processEvent(event);
        }
        if(!paused)
        {
            window.clear(sf::Color(25,25,25));

            for(int i=0; i<30; i++)
            {
                for(int j=0; j<30; j++)
                {
                    cell.setSize(40);
                    cell.setInnerCellsVisible(rand()%2);
                    float size = cell.getSize();
                    cell.setPosition(sf::Vector2f(size*i,size*j+40));
                    window.draw(cell);
                }
            }
            window.draw(tButton);
            window.draw(tBox);
            window.draw(iButton);
            window.display();
            window.setTitle("GameOfLife FPS:" + to_string(getFPS(Clock.restart())));
        }
    }
    return 0;
}

