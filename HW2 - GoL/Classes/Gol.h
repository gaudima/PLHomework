#ifndef GOL_H
#define GOL_H

#include <cstdint>
#include <random>
#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "GolDrawField.h"
#include <unistd.h>

using namespace std;

class Gol {
public:
    //Constructor that creates field with given dimensions and given number of cells populated
    Gol(int width, int height, int populated);

    //One step i ntime
    void cycle();

    //Clears field
    void clear();

    //Outputs field to console
    void debugOut();

    //Creates field with given dimensions
    void create(int width, int height);

    //Resizes field from current size to given size and offsets initial field by given offset
    void resize(int width, int height, int offsetX, int offsetY);

    //Draws field on screen
    void draw(sf::RenderWindow &window);

    //Process events emmited by sfml
    void processEvent(sf::Event event);

    //Make cell at x y alive if dead and viceversa
    void putCell(int x, int y);

    //This method launched in thread and reuns cycle() with given delay
    void run();

    //Just sets number of steps that run() should run
    void runNumOfSteps(int num);

    //Puses run() method
    void pause();

    //Returns true if run() paused othervise false
    bool getPaused();

    //Stops run() thread from executing
    void stop();

    //Make cell dimensions bigger
    void zoomIn();

    //Make cell dimensions smaller
    void zoomOut();

    //Make delay between cycles smaller
    void faster();

    //Make delay between cycles bigger
    void slower();

    //Populate field with given number of cells
    void fill(int population);

    //Get number of cells was born on current cycle
    long getBorn();

    //Get ratio of born to died
    double getBornDied();

private:
    //Checks if field sould be rsized and rsizes it if needed
    void checkResize();

    sf::Mutex _mutex;
    sf::Clock _delayTimer;
    sf::Clock _mClock;
    GolDrawField _drawField;
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
