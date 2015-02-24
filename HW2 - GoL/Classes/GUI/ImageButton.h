#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include <functional>
#include <iostream>

using namespace std;

class ImageButton : public sf::Drawable
{
public:
    ImageButton();
    ImageButton(string path);
    void setImage(string path);
    void setSize(sf::Vector2f size);
    void setPosition(sf::Vector2f position);
    void processEvent(sf::Event event);
    void onClick(function<void()> callback);

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        target.draw(_outerBox, states);
        target.draw(_sprite, states);
    }

    void init();
    sf::Sprite _sprite;
    sf::Texture _texture;
    sf::RectangleShape _outerBox;
    function<void()> _callback;

};

#endif // IMAGEBUTTON_H
