#include "TextBox.h"
#include <iostream>

TextBox::TextBox()
{
    init();
    setSize(sf::Vector2f(40,20));
    setText("");
    setPosition(sf::Vector2f(0,0));
}

TextBox::TextBox(string text)
{
    init();
    setSize(sf::Vector2f(40,20));
    setText(text);
    setPosition(sf::Vector2f(0,0));
}

void TextBox::init()
{
    _active = false;
    _font.loadFromFile("Resources/Ubuntu.ttf");
    _text.setFont(_font);
    _text.setOrigin(-2,-2);
    _outerBox.setFillColor(sf::Color(0,0,0,0));
    _outerBox.setOutlineColor(sf::Color(255,255,255));
    _outerBox.setOutlineThickness(1);
    _outerBox.setOrigin(-1,-1);
}

void TextBox::setSize(sf::Vector2f size)
{
    _text.setCharacterSize(size.y-4);
    _outerBox.setSize(sf::Vector2f(size.x-2,size.y-2));

}

void TextBox::setText(string text)
{
    _string = text;
    _text.setString(_string);
}

void TextBox::setPosition(sf::Vector2f position)
{
    _outerBox.setPosition(position);
    _text.setPosition(position);
}

void TextBox::setActive(bool active)
{
    _active = active;
    if(_active)
    {
        _outerBox.setOutlineColor(sf::Color(255,0,0));
    }
    else
    {
        _outerBox.setOutlineColor(sf::Color(255,255,255));
    }
}

string TextBox::getText()
{
    return _string;
}

void TextBox::processEvent(sf::Event event)
{
    if(event.type == sf::Event::MouseButtonPressed)
    {
        if(_outerBox.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
        {
            setActive(true);
        }
        else
        {
            setActive(false);
        }
    }
    if(_active)
    {
        if(event.type == sf::Event::KeyPressed)
        {
            if(event.key.code == sf::Keyboard::BackSpace)
            {
                if(_string.length()>0)
                {
                    _string.pop_back();
                }
                setText(_string);
            }
        }
        else if(event.type == sf::Event::TextEntered)
        {
            //dont know why backspace code = 8
            if(event.text.unicode < 128 && event.text.unicode != 8)
            {
                setText(_string+static_cast<char>(event.text.unicode));
                if(_text.getGlobalBounds().width>_outerBox.getSize().x)
                {
                    if(_string.length()>0)
                    {
                        _string.pop_back();
                    }
                    setText(_string);
                }
            }
        }
    }
}
