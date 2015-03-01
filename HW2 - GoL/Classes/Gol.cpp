#include "Gol.h"

Gol::Gol(int width, int height, int populated) {
    create(width, height);
    _drawField.setCellSize(_cellSize);
    _drawField.setPosition(sf::Vector2f(0, 61));
    fill(populated);
}

void Gol::cycle() {
    _born = 0;
    _died = 0;
    _mutex.lock();
    checkResize();
    _mutex.unlock();

    uint8_t **new_field = new uint8_t *[_height];
    for (int i = 0; i < _height; i++) {
        new_field[i] = new uint8_t[_width]();
    }

    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            if (_field[i][j]) {
                int neighbours = _field[i][j] >> 4;
                if (_field[i][j] & 0x01) {
                    if (neighbours == 3 || neighbours == 2) {
                        new_field[i][j] = new_field[i][j] | 0x01;
                    } else {
                        _died += 1;
                    }
                } else {
                    if (neighbours == 3) {
                        _born += 1;
                        new_field[i][j] = new_field[i][j] | 0x01;
                    }
                }
                if (new_field[i][j] & 0x01) {
                    for (int k = -1; k < 2; k++) {
                        for (int l = -1; l < 2; l++) {
                            if (i + k >= 0 && i + k < _height &&
                                    j + l >= 0 && j + l < _width &&
                                    !(k == 0 && l == 0)) {
                                new_field[i + k][j + l] += 0x10;
                            }
                        }
                    }
                }
            }
        }
    }

    _mutex.lock();
    for (int i = 0; i < _height; i++) {
        delete[] _field[i];
    }
    delete[] _field;
    _field = new_field;
    _mutex.unlock();
}

void Gol::run() {
    while (!_stopped) {
        if (_paused && _nOfSteps == -1) {
            _delayTimer.restart();
        }

        if (_delayTimer.getElapsedTime().asMilliseconds() >= _refreshDelay) {
            _mClock.restart();
            cycle();
            cout<<"Cycle Time: "<<_mClock.restart().asMicroseconds()<<endl;
            if (_nOfSteps > -1) {
                _nOfSteps -= 1;
            }
            _delayTimer.restart();
        }
    }
}

void Gol::pause() {
    cout << "pausing" << endl;
    _paused = !_paused;
}

bool Gol::getPaused() {
    return _paused;
}

void Gol::stop() {
    cout << "stopping" << endl;
    _stopped = true;
}

void Gol::checkResize() {

    //flags are set to true if field should be resized in on of directions
    bool rTop = false,
            rBottom = false,
            rLeft = false,
            rRight = false;

    int new_width = _width,
            new_height = _height,
            offsetX = 0,
            offsetY = 0;

    for (int i = 0; i < _height; i++) {
        if (_field[i][0] & 0x01) {
            rLeft = true;
        }
        if (_field[i][_width - 1] & 0x01) {
            rRight = true;
        }
    }

    for (int i = 0; i < _width; i++) {
        if (_field[0][i] & 0x01) {
            rTop = true;
        }
        if (_field[_height - 1][i] & 0x01) {
            rBottom = true;
        }
    }

    if (rTop) {
        offsetY = 1;
        new_height += 1;
        _drawingOffsetY += 1;
    }
    if (rBottom) {
        new_height += 1;
    }
    if (rLeft) {
        offsetX = 1;
        new_width += 1;
        _drawingOffsetX += 1;
    }
    if (rRight) {
        new_width += 1;
    }
    resize(new_width, new_height, offsetX, offsetY);
    _drawField.setOffset(_drawingOffsetX, _drawingOffsetY);
}

void Gol::resize(int width, int height, int offsetX, int offsetY) {

    uint8_t **new_field = new uint8_t *[height];
    for (int i = 0; i < height; i++) {
        new_field[i] = new uint8_t[width]();
    }

    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            new_field[offsetY + i][offsetX + j] = _field[i][j];
        }
    }

    for (int i = 0; i < _height; i++) {
        delete[] _field[i];
    }
    delete[] _field;

    _field = new_field;
    _width = width;
    _height = height;
}

void Gol::create(int width, int height) {
    _drawingOffsetX=0;
    _drawingOffsetY=0;
    _field = new uint8_t *[height];
    for (int i = 0; i < height; i++) {
        _field[i] = new uint8_t[width]();
    }
    _width = width;
    _height = height;
    cout << "finished create" << endl;
}

void Gol::fill(int population) {
    srand(time(NULL));
    if (population > _height * _width) {
        return;
    }

    int x = rand() % _width;
    int y = rand() % _height;

    while (population != 0) {
        while (_field[y][x] != 0) {
            x = rand() % _width;
            y = rand() % _height;
        }
        _field[y][x] = 0x01;
        population -= 1;
    }

    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            if (_field[i][j] & 1) {
                for (int k = -1; k < 2; k++) {
                    for (int l = -1; l < 2; l++) {
                        if (i + k >= 0 && i + k < _height &&
                                j + l >= 0 && j + l < _width &&
                                !(k == 0 && l == 0)) {
                            _field[i + k][j + l] += 0x10;
                        }
                    }
                }
            }
        }
    }
}

void Gol::debugOut() {
    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            cout << (int) _field[i][j] << " ";
        }
        cout << endl;
    }
}

void Gol::runNumOfSteps(int num) {
    _nOfSteps = num - 1;
}

void Gol::draw(sf::RenderWindow &window) {
//    GolDrawCell cell;
//    sf::FloatRect screenRect(-_cellSize, 60, 800 + _cellSize * 2, 600 + _cellSize * 2);
//    cell.setSize(_cellSize);
    _mutex.lock();
//    //_rTexture.clear(sf::Color(25, 25, 25));
//    for (int i = 0; i < _height; i++) {
//        for (int j = 0; j < _width; j++) {
//            sf::Vector2f position(_cellSize * j - _drawingOffsetX * _cellSize, _cellSize * i + 60 - _drawingOffsetY * _cellSize);
//            if (screenRect.contains(position)) {
//                cell.setInnerCellsVisible(_field[i][j] & 0x01);
//                cell.setPosition(position);
//                window.draw(cell);
//            }
//        }
//    }
    //_rTexture.display();
    //sf::Sprite spr(_rTexture.getTexture());
    //window.draw(spr);

    _drawField.updateWithField(_field, _width, _height);

    window.draw(_drawField);
    _mutex.unlock();
}

void Gol::putCell(int x, int y) {
    if (_field[y][x] & 0x01) {
        _field[y][x] -= 0x01;
        for (int k = -1; k < 2; k++) {
            for (int l = -1; l < 2; l++) {
                if (y + k >= 0 && y + k < _height &&
                        x + l >= 0 && x + l < _width &&
                        !(k == 0 && l == 0)) {
                    _field[y + k][x + l] -= 0x10;
                }
            }
        }
    } else {
        _field[y][x] += 0x01;
        for (int k = -1; k < 2; k++) {
            for (int l = -1; l < 2; l++) {
                if (y + k >= 0 && y + k < _height &&
                        x + l >= 0 && x + l < _width &&
                        !(k == 0 && l == 0)) {
                    _field[y + k][x + l] += 0x10;
                }
            }
        }
    }
}

void Gol::processEvent(sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.y > 60) {
            int fieldX = event.mouseButton.x / _cellSize + _drawingOffsetX;
            int fieldY = (event.mouseButton.y - 60) / _cellSize + _drawingOffsetY;
            if (fieldX >= 0 && fieldX <= _width && fieldY >= 0 && fieldY <= _height) {
                cout << fieldX << " " << fieldY << endl;
                putCell(fieldX, fieldY);
            }
        }
    }
    else if (event.type == sf::Event::MouseWheelMoved) {
        if (event.mouseWheel.delta > 0) {
            zoomIn();
        }
        else {
            zoomOut();
        }
    }
    else if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Up:
                _drawingOffsetY -= 1;
                break;
            case sf::Keyboard::Down:
                _drawingOffsetY += 1;
                break;
            case sf::Keyboard::Left:
                _drawingOffsetX -= 1;
                break;
            case sf::Keyboard::Right:
                _drawingOffsetX += 1;
                break;
        }
        _drawField.setOffset(_drawingOffsetX, _drawingOffsetY);
    }
}

void Gol::zoomIn() {
    _cellSize += 1;
    _drawField.setCellSize(_cellSize);
}

void Gol::zoomOut() {
    if (_cellSize > 5) {
        _cellSize -= 1;
    }
    _drawField.setCellSize(_cellSize);
}

void Gol::clear() {
    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            _field[i][j] = 0;
        }
    }
}

void Gol::faster() {
    if (_refreshDelay > 40) {
        _refreshDelay -= 20;
    }
}

void Gol::slower() {
    _refreshDelay += 20;
}

long Gol::getBorn() {
    return _born;
}

double Gol::getBornDied() {
    if (_died != 0) {
        return (double) _born / (double) _died;
    } else {
        return (double) (_born) / 1;
    }
}
