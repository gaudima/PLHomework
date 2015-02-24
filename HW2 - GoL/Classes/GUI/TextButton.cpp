#include "TextButton.h"

TextButton::TextButton()
{
    init();
    setSize(20);
    setText("");
    setPosition(sf::Vector2f(0,0));
}

TextButton::TextButton(string text)
{
    init();
    setSize(20);
    setText(text);
    setPosition(sf::Vector2f(0,0));
}

void TextButton::setText(string text)
{
    _string = text;
    _text.setString(_string);
    setSize(_height);
}

void TextButton::setPosition(sf::Vector2f position)
{
    _outerBox.setPosition(position);
    _text.setPosition(position);
}

void TextButton::setSize(float height)
{
    _height = height;
    _text.setCharacterSize(_height-4);
    _outerBox.setSize(sf::Vector2f(_text.getGlobalBounds().width+2,_height-2));
}

void TextButton::onClick(function<void()> callback)
{
    _callback=callback;
}

void TextButton::processEvent(sf::Event event)
{
    if(event.type == sf::Event::MouseButtonPressed)
    {
        if(_outerBox.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
        {
            _outerBox.setOutlineColor(sf::Color(255,0,0));
            _text.setColor(sf::Color(255,0,0));
            _callback();
        }
    }
    else if(event.type == sf::Event::MouseButtonReleased)
    {
        _outerBox.setOutlineColor(sf::Color(255,255,255));
        _text.setColor(sf::Color(255,255,255));
    }
}

void TextButton::init()
{
    _font.loadFromFile("Resources/Ubuntu.ttf");
    _text.setFont(_font);
    _text.setOrigin(-2,-2);
    _outerBox.setFillColor(sf::Color(0,0,0,0));
    _outerBox.setOutlineColor(sf::Color(255,255,255));
    _outerBox.setOutlineThickness(1);
    _outerBox.setOrigin(-1,-1);
    _callback = [](){ cout<<"button pressed"<<endl;};
}
