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

class Gol {
public:
    Gol(int width, int height, int populated, int cycles);

    void cycle();

    void clear();

    void debugOut();

    void create(int width, int height);

    void resize(int width, int height, int offsetX, int offsetY);

    void draw(sf::RenderWindow &window);

    void processEvent(sf::Event event);

    void putCell(int x, int y);

    void run();

    void runNumOfSteps(int num);

    void pause();

    bool getPaused();

    void stop();

    void zoomIn();

    void zoomOut();

    void faster();

    void slower();

    void fill(int population);

    long getBorn();

    double getBornDied();

private:
    void checkResize();

    sf::Mutex _mutex;
    sf::Clock _delayTimer;
    uint8_t **_field;
    int _refreshDelay = 500;
    int _height = 0;
    int _width = 0;
    int _drawingOffsetX = 0;
    int _drawingOffsetY = 0;
    bool _paused = true;
    bool _stopped = false;
    float _cellSize = 40;
    int _nOfSteps = -1;
    long _born = 0;
    long _died = 0;

};

#endif // GOL_H
