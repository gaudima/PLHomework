#include "GolDrawCell.h"

GolDrawCell::GolDrawCell() {
    init();
    setSize(_size);
}

GolDrawCell::GolDrawCell(sf::Vector2f position) {
    init();
    setSize(_size);
    setPosition(position);
}

void GolDrawCell::setSize(float wh) {
    _size = wh;
    _outerCell.setSize(sf::Vector2f(_size - 2, _size - 2));
    _innerCell.setRadius((_size - 2) / 2 - 1);
}

float GolDrawCell::getSize() {
    return _size;
}

void GolDrawCell::setPosition(sf::Vector2f position) {
    _outerCell.setPosition(position);
    _innerCell.setPosition(position);
}

void GolDrawCell::setInnerCellsVisible(bool visible) {
    _innerCellVisible = visible;
}

void GolDrawCell::init() {
    _innerCellVisible = false;
    _size = 20;

    _outerCell.setFillColor(sf::Color(0, 0, 0, 0));
    _outerCell.setOutlineColor(sf::Color(255, 255, 255));
    _outerCell.setOutlineThickness(1);
    _outerCell.setOrigin(-1, -1);

    _innerCell.setFillColor(sf::Color(255, 255, 255));
    _innerCell.setOrigin(sf::Vector2f(-2, -2));
}
