#ifndef GOLDRAWCELL_H
#define GOLDRAWCELL_H

#include <SFML/Graphics.hpp>

class GolDrawCell : public sf::Drawable {
public:
    GolDrawCell();

    GolDrawCell(sf::Vector2f position);

    void setPosition(sf::Vector2f position);

    void setInnerCellsVisible(bool visible);

    void setSize(float wh);

    float getSize();

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
        target.draw(_outerCell, states);
        if (_innerCellVisible) {
            target.draw(_innerCell, states);
        }
    }

    void init();

    sf::RectangleShape _outerCell;
    sf::CircleShape _innerCell;
    bool _innerCellVisible;
    float _size;
};

#endif // GOLDRAWCELL_H
