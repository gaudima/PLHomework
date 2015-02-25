#ifndef GOL_H
#define GOL_H

#include <cstdint>
#include <random>
#include <iostream>
#include <ctime>


using namespace std;

class Gol
{
public:
    Gol(int width, int height, int populated, int cycles);
    void cycle();
    void clear();
    void debugOut();
    void resize(int width, int height);
private:


    void checkResize();
    void create(int width, int height);
    void fill(int population);

    uint8_t **_field;
    int _height=0;
    int _width=0;
    int _offsetX=0;
    int _offsetY=0;

};

#endif // GOL_H
