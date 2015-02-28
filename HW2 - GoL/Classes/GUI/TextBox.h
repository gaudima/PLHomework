#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

class TextBox : public sf::Drawable {
public:
    TextBox();

    TextBox(string text);

    void setText(string text);

    void setSize(sf::Vector2f size);

    void setPosition(sf::Vector2f position);

    void setActive(bool active);

    void processEvent(sf::Event &event);

    string getText();

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
        target.draw(_outerBox, states);
        target.draw(_text, states);
    }

    void init();

    sf::RectangleShape _outerBox;
    sf::Text _text;
    sf::Font _font;
    string _string;
    bool _active;
};

#endif // TEXTBOX_H
