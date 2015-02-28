#ifndef UILAYOUT_H
#define UILAYOUT_H

#include <SFML/Graphics.hpp>
#include "ImageButton.h"
#include "TextBox.h"
#include "TextButton.h"
#include "Gol.h"

class UiLayout {

public:
    UiLayout(Gol *gol);

    void processEvent(sf::Event &event);

    void draw(sf::RenderWindow &window);

private:

    TextBox _tbxWidth;
    TextBox _tbxHeight;
    TextBox _tbxPopulation;
    TextBox _tbxSteps;
    ImageButton _ibtZoomIn;
    ImageButton _ibtZoomOut;
    ImageButton _ibtFaster;
    ImageButton _ibtSlower;
    TextButton _tbtRunNCycles;
    TextButton _tbtCreateField;
    TextButton _tbtGenPopulation;
    ImageButton _tbtPlayPause;

    sf::Text _txtFieldSize;
    sf::Text _txtPopulation;
    sf::Text _txtSteps;
    sf::Text _txtX;

    sf::Text _txtStats;

    sf::Font _font;

    Gol *_gol;

};


#endif // UILAYOUT_H
