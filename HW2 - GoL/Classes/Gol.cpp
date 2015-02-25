#include "Gol.h"

Gol::Gol(int width, int height, int populated, int cycles)
{
    create(width, height);
    fill(populated);
}

void Gol::cycle()
{
    uint8_t **fld = new uint8_t*[_height];
    for(int i = 0; i < _height; i++)
    {
        fld[i] = new uint8_t[_width]();
    }
    for(int i = 1; i < _height-1; i++)
    {
        for(int j=1; j < _width-1; j++)
        {
            int neib=0;
            for(int k = -1; k < 2; k++)
            {
                for(int l = -1; l < 2; l++)
                {
                    if(k!=l && l!=0)
                    {
                        neib+=_field[i+k][j+l];
                    }
                }
            }
            cout<<neib<<endl;
            if(_field[i][j] == 0)
            {
                if(neib == 3)
                {
                    fld[i][j] = 1;
                }
            }
            else
            {
                if(neib==2 || neib==3)
                {
                    fld[i][j]==1;
                }
                else
                {
                    fld[i][j]==0;
                }
            }
        }
    }

    for(int i = 0; i < _height; i++)
    {
        delete [] _field[i];
    }
    delete [] _field;

    _field = fld;
    checkResize();
}

void Gol::checkResize()
{
    bool rLeft = false, rRight=false, rTop=false, rBottom=false;
    for(int i = 0; i<_height; i++)
    {
        if(_field[i][1]==1)
        {
            rLeft=true;
        }
        if(_field[i][_width-2]==1)
        {
            rRight=true;
        }
    }
    for(int i = 0; i<_width; i++)
    {
        if(_field[1][i]==1)
        {
            rTop=true;
        }
        if(_field[_height-2][i]==1)
        {
            rBottom=true;
        }
    }

    int height = _height;
    int width = _width;
    if(rLeft)
    {
        _offsetX=2;
        width+=1;
    }
    if(rRight)
    {
        width+=1;
    }
    if(rTop)
    {
        _offsetY=2;
        height+=1;
    }
    if(rBottom)
    {
        height+=1;
    }
    resize(width, height);
}

void Gol::resize(int width, int height)
{
    uint8_t **fld = new uint8_t*[height];
    for(int i = 0; i < height; i++)
    {
        fld[i] = new uint8_t[width]();
    }

    for(int i = 0; i < _height; i++)
    {
        for(int j = 0; j < _width; j++)
        {
                fld[_offsetY + i][_offsetX + j] = _field[i][j];
        }
    }

    for(int i = 0; i < _height; i++)
    {
        delete [] _field[i];
    }
    delete [] _field;

    _field = fld;
    _width = width;
    _height = height;
}

void Gol::create(int width, int height)
{
    _field = new uint8_t*[height];
    for(int i = 0; i < height; i++)
    {
        _field[i] = new uint8_t[width]();
    }
    _width = width;
    _height = height;
    cout<<"finished create"<<endl;
}

void Gol::fill(int population)
{
    srand(time(NULL));
    if(population>_height*_width)
    {
        return;
    }


    int x = rand() % (_width - 2) + 1;
    int y = rand() % (_height - 2) + 1;

    while(population!=0)
    {
        while(_field[y][x] != 0)
        {
            x = rand() % (_width - 2) +1;
            y = rand() % (_height - 2) +1;
        }
        _field[y][x] = 1;
        population-=1;
    }
}

void Gol::debugOut()
{
    for(int i = 0; i < _height; i++)
    {
        for(int j=0; j < _width; j++)
        {
            cout<<(int)_field[i][j]<<" ";
        }
        cout<<endl;
    }
}

void Gol::clear()
{
    for(int i = 0; i < _height; i++)
    {
        for(int j=0; j < _width; j++)
        {
            _field[i][j] = 0;
        }
    }
}
