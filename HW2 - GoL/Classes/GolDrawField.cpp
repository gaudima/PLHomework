#include "GolDrawField.h"

GolDrawField::GolDrawField(): _color(69,69,69), _position(0, 0) {
    _fieldArray.setPrimitiveType(sf::Lines);
    _circleArray.setPrimitiveType(sf::Triangles);
}

void GolDrawField::updateWithField(uint8_t** &golFieldArray, int width, int height) {
    _fieldArray.clear();
    _circleArray.clear();

    sf::FloatRect screenRect(-_cellSize, 60 - _cellSize, 800 + _cellSize * 2, 540 + _cellSize * 2);
    sf::Vector2f offset(_offsetX * _cellSize, _offsetY * _cellSize);
    for (int i = 0; i <= height; i++) {
        for (int j = 0; j <= width; j++) {
            if(_cellSize>=8) {
                sf::Vector2f pos = _position - offset;
                if (screenRect.contains(pos + sf::Vector2f(j * _cellSize, i * _cellSize))) {
                    if (i < height) {
                        _fieldArray.append(sf::Vertex(pos + sf::Vector2f(j * _cellSize, i * _cellSize), _color));
                        _fieldArray.append(sf::Vertex(pos + sf::Vector2f(j * _cellSize, (i + 1) * _cellSize), _color));
                    }
                    if (j < width) {
                        _fieldArray.append(sf::Vertex(pos + sf::Vector2f(j * _cellSize, i * _cellSize), _color));
                        _fieldArray.append(sf::Vertex(pos + sf::Vector2f((j + 1) * _cellSize, i * _cellSize), _color));
                    }
                }
            }
            if(i < height && j < width) {
                if (golFieldArray[i][j] & 0x01) {
                    sf::Vector2f position = sf::Vector2f(j * _cellSize + _cellSize / 2, i * _cellSize + _cellSize / 2) - sf::Vector2f(_offsetX * _cellSize, _offsetY * _cellSize);
                    if (screenRect.contains(_position + position)) {
                        float angle = 0;
                        for (int k = 1; k <= 20; k++) {
                            _circleArray.append(sf::Vertex(_position + position, sf::Color(255, 255, 255)));
                            _circleArray.append(sf::Vertex(_position + position + sf::Vector2f(cos(angle) * (_cellSize - 4) / 2, sin(angle) * (_cellSize - 4) / 2), sf::Color(255, 255, 255)));
                            angle += 3.1415926535 * 2 / 20;
                            _circleArray.append(sf::Vertex(_position + position + sf::Vector2f(cos(angle) * (_cellSize - 4) / 2, sin(angle) * (_cellSize - 4) / 2), sf::Color(255, 255, 255)));
                        }
                    }
                }
            }
        }
    }
}

void GolDrawField::setCellSize(float cellSize) {
    _cellSize = cellSize;
}

void GolDrawField::setPosition(sf::Vector2f position) {
    _position = position;
}

void GolDrawField::setOffset(int offsetX, int offsetY) {
    _offsetX = offsetX;
    _offsetY = offsetY;
}