#include "ImageButton.h"

ImageButton::ImageButton()
{
    init();
    setSize(sf::Vector2f(20,20));
    setPosition(sf::Vector2f(0,0));
}

ImageButton::ImageButton(string path)
{
    init();
    setImage(path);
    setSize(sf::Vector2f(20,20));
    setPosition(sf::Vector2f(0,0));
}

void ImageButton::setImage(string path)
{
    _texture.loadFromFile(path);
    _sprite.setTexture(_texture);
    //_outerBox.setSize(sf::Vector2f(_sprite.getGlobalBounds().width+2, _sprite.getGlobalBounds().height+2));
}

void ImageButton::setPosition(sf::Vector2f position)
{
    _outerBox.setPosition(position);
    _sprite.setPosition(position);
}

void ImageButton::setSize(sf::Vector2f size)
{
    _sprite.setScale(sf::Vector2f((size.x-2)/_texture.getSize().x, (size.y-2)/_texture.getSize().y));
    _outerBox.setSize(sf::Vector2f(size.x-2,size.y-2));
}

void ImageButton::onClick(function<void()> callback)
{
    _callback=callback;
}

void ImageButton::processEvent(sf::Event event)
{
    if(event.type == sf::Event::MouseButtonPressed)
    {
        if(_outerBox.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
        {
            _outerBox.setOutlineColor(sf::Color(255,0,0));
            _sprite.setColor(sf::Color(255,0,0));
            _callback();
        }
    }
    else if(event.type == sf::Event::MouseButtonReleased)
    {
        _outerBox.setOutlineColor(sf::Color(255,255,255));
        _sprite.setColor(sf::Color(255,255,255));
    }
}

void ImageButton::init()
{
    _sprite.setOrigin(-2,-2);
    _texture.setSmooth(true);
    _outerBox.setFillColor(sf::Color(0,0,0,0));
    _outerBox.setOutlineColor(sf::Color(255,255,255));
    _outerBox.setOutlineThickness(1);
    _outerBox.setOrigin(-1,-1);
    _callback = [](){ cout<<"button pressed"<<endl;};
}
