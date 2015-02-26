#ifndef GOL_H
#define GOL_H

#include <cstdint>
#include <random>
#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "GolDrawCell.h"
#include <unistd.h>

using namespace std;

class Gol
{
public:
    Gol(int width, int height, int populated, int cycles);
    void cycle();
    void clear();
    void debugOut();
    void resize(int width, int height, int offsetX, int offsetY);
    void draw(sf::RenderWindow &window);
    void processEvent(sf::Event event);
    void run();
    void pause();
    void stop();
    void zoomIn();
    void zoomOut();

private:
    void checkResize();
    void create(int width, int height);
    void fill(int population);

    sf::Mutex _mutex;
    uint8_t **_field;
    int _height=0;
    int _width=0;
    int _drawingOffsetX=0;
    int _drawingOffsetY=0;
    bool _paused=false;
    bool _stopped=false;
    float _cellSize=40;

};

#endif // GOL_H
