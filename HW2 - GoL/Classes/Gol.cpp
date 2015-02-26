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
    for(int i = 1; i < _height - 1; i++)
    {
        for(int j=1; j < _width - 1; j++)
        {
            int neib=0;
            for(int k = -1; k < 2; k++)
            {
                for(int l = -1; l < 2; l++)
                {
                    if(!(k==0 && l==0))
                    {
                        neib+=_field[i+k][j+l];
                    }
                }
            }
            if(_field[i][j])
            {
                if(neib == 2 || neib == 3)
                {
                    fld[i][j] = 1;
                }
            }
            else
            {
                if(neib == 3)
                {
                    fld[i][j] = 1;
                }
            }
        }
    }
    _mutex.lock();
    for(int i = 0; i < _height; i++)
    {
        delete [] _field[i];
    }
    delete [] _field;

    _field = fld;
    checkResize();
    _mutex.unlock();
}

void Gol::run()
{
    while(!_stopped)
    {
        if(!_paused)
        {
            sleep(1);
            cycle();
        }
    }
}

void Gol::pause()
{
    cout<<"pausing"<<endl;
    _paused=!_paused;
}

void Gol::stop()
{
    cout<<"stopping"<<endl;
    _stopped=true;
}

void Gol::checkResize()
{
    bool rLeft = false, rRight = false, rTop = false, rBottom = false;
    for(int i = 0; i < _height; i++)
    {
        if(_field[i][1] == 1)
        {
            rLeft = true;
        }
        if(_field[i][_width - 2] == 1)
        {
            rRight = true;
        }
    }
    for(int i = 0; i < _width; i++)
    {
        if(_field[1][i] == 1)
        {
            rTop = true;
        }
        if(_field[_height - 2][i] == 1)
        {
            rBottom = true;
        }
    }
    int offsetX = 0;
    int offsetY = 0;
    int height = _height;
    int width = _width;
    if(rLeft)
    {
        offsetX=1;
        _drawingOffsetX+=1;
        width+=1;
    }
    if(rRight)
    {
        width+=1;
    }
    if(rTop)
    {
        offsetY=1;
        _drawingOffsetY+=1;
        height+=1;
    }
    if(rBottom)
    {
        height+=1;
    }
    resize(width, height, offsetY, offsetX);
}

void Gol::resize(int width, int height, int offsetX, int offsetY)
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
                fld[offsetY + i][offsetX + j] = _field[i][j];
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

void Gol::draw(sf::RenderWindow &window)
{
    GolDrawCell cell;
    cell.setSize(_cellSize);
    _mutex.lock();
    for(int i = 1; i < _height - 1 ; i++)
    {
        for(int j = 1; j < _width - 1 ; j++)
        {
            cell.setInnerCellsVisible(_field[i][j]);
            sf::Vector2f position(_cellSize * j - _drawingOffsetX * _cellSize, _cellSize * i + 40 - _drawingOffsetY * _cellSize);
            cell.setPosition(position);
            sf::FloatRect screenRect(-_cellSize, 40, 800 + _cellSize * 2 , 600 + _cellSize * 2);
            if(screenRect.contains(position))
            {
                window.draw(cell);
            }
        }
    }
    _mutex.unlock();
}

void Gol::processEvent(sf::Event event)
{
    if(event.type == sf::Event::MouseButtonPressed)
    {
        if(event.mouseButton.y>_cellSize)
        {
            int fieldX = event.mouseButton.x / _cellSize + _drawingOffsetX;
            int fieldY = (event.mouseButton.y - 40) / _cellSize + _drawingOffsetY;
            cout<<fieldX<<" "<<fieldY<<endl;
            if(_field[fieldY][fieldX])
            {
                _field[fieldY][fieldX] = 0;
            }
            else
            {
                _field[fieldY][fieldX] = 1;
            }
        }
    }
    else if(event.type == sf::Event::MouseWheelMoved)
    {
        if(event.mouseWheel.delta>0)
        {
            zoomIn();
        }
        else
        {
            zoomOut();
        }
    }
    else if(event.type == sf::Event::KeyPressed)
    {
        switch(event.key.code)
        {
            case sf::Keyboard::Up:     if(_drawingOffsetY>0) _drawingOffsetY-=1; break;
            case sf::Keyboard::Down:   _drawingOffsetY+=1; break;
            case sf::Keyboard::Left:   if(_drawingOffsetX>0) _drawingOffsetX-=1; break;
            case sf::Keyboard::Right:  _drawingOffsetX+=1; break;
        }
    }
}

void Gol::zoomIn()
{
    _cellSize+=1;
}

void Gol::zoomOut()
{
    if(_cellSize>5)
    {
        _cellSize-=1;
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
