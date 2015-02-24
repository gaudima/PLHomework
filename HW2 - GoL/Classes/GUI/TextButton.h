#ifndef TEXTBUTTON_H
#define TEXTBUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include <functional>
#include <iostream>

using namespace std;

class TextButton : public sf::Drawable
{
public:
    TextButton();
    TextButton(string text);
    void setText(string text);
    void setSize(float height);
    void setPosition(sf::Vector2f position);
    void processEvent(sf::Event event);
    void onClick(function<void()> callback);
private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        target.draw(_outerBox, states);
        target.draw(_text, states);
    }

    void init();
    sf::Text _text;
    sf::RectangleShape _outerBox;
    sf::Font _font;
    string _string;
    float _height;
    function<void()> _callback;
};

#endif // TEXTBUTTON_H
