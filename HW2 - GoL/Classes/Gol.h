#ifndef GOL_H
#define GOL_H

#include <cstdint>

class Gol
{
public:
    Gol(long height, long width, long populated, long cycles);
    void cycle();
private:
    uint8_t **_field;
    long _height;
    long _width;

};

#endif // GOL_H
