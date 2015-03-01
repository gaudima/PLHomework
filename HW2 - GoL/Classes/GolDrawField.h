#ifndef GOLDRAWFIELD_H
#define GOLDRAWFIELD_H

#include <SFML/Graphics.hpp>
#include <cmath>

class GolDrawField : public sf::Drawable {
public:
    GolDrawField();
    void updateWithField(uint8_t** &golFieldArray, int width, int height);
    void setCellSize(float cellSize);
    void setPosition(sf::Vector2f position);
    void setOffset(int offsetX, int offsetY);

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
        target.draw(_fieldArray, states);
        target.draw(_circleArray, states);
    }
    sf::VertexArray _fieldArray;
    sf::VertexArray _circleArray;
    sf::Color _color;
    sf::Vector2f _position;
    float _cellSize;
    int _offsetX=0;
    int _offsetY=0;
};

#endif // GOLDRAWFIELD_H