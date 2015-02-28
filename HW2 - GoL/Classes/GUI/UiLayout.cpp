#include "UiLayout.h"

UiLayout::UiLayout(Gol *gol) {
    _gol = gol;
    _tbxWidth.setPosition(sf::Vector2f(5, 30));
    _tbxHeight.setPosition(sf::Vector2f(65, 30));
    _tbxPopulation.setPosition(sf::Vector2f(240, 30));
    _tbxSteps.setPosition(sf::Vector2f(350, 30));

    _ibtZoomIn.setImage("Resources/icons/zoom-in.png");
    _ibtZoomIn.setPosition(sf::Vector2f(485, 5));
    _ibtZoomIn.onClick([&](){
        _gol->zoomIn();
    });

    _ibtZoomOut.setImage("Resources/icons/zoom-out.png");
    _ibtZoomOut.setPosition(sf::Vector2f(460, 5));
    _ibtZoomOut.onClick([&](){
        _gol->zoomOut();
    });

    _ibtFaster.setImage("Resources/icons/faster.png");
    _ibtFaster.setPosition(sf::Vector2f(485, 30));
    _ibtFaster.onClick([&](){
        _gol->faster();
    });

    _ibtSlower.setImage("Resources/icons/slower.png");
    _ibtSlower.setPosition(sf::Vector2f(460, 30));
    _ibtSlower.onClick([&](){
        _gol->slower();
    });

    _tbtGenPopulation.setText("Gen");
    _tbtGenPopulation.setPosition(sf::Vector2f(285, 30));
    _tbtGenPopulation.setSize(sf::Vector2f(40, 20));
    _tbtGenPopulation.onClick([&](){
        string popul = _tbxPopulation.getText();
        if(popul.size()!=0)
        {
            _gol->clear();
            _gol->fill(stoi(popul));
        }
    });

    _tbtRunNCycles.setText("Run");
    _tbtRunNCycles.setPosition(sf::Vector2f(395, 30));
    _tbtRunNCycles.setSize(sf::Vector2f(40, 20));
    _tbtRunNCycles.onClick([&](){
        string nOfCycles = _tbxSteps.getText();
        if(nOfCycles.size()!=0) {
            _gol->runNumOfSteps(stoi(nOfCycles));
        }
    });

    _tbtCreateField.setText("Create field");
    _tbtCreateField.setPosition(sf::Vector2f(110, 30));
    _tbtCreateField.onClick([&](){
        string width  = _tbxWidth.getText(),
               height = _tbxHeight.getText();
        if(width.size()!=0 && height.size()!=0) {
            _gol->create(stoi(width), stoi(height));
        }
    });

    _tbtPlayPause.setImage("Resources/icons/play.png");
    _tbtPlayPause.setPosition(sf::Vector2f(510, 5));
    _tbtPlayPause.setSize(sf::Vector2f(45,45));
    _tbtPlayPause.onClick([&](){
        _gol->pause();
        if(_gol->getPaused()) {
            _tbtPlayPause.setImage("Resources/icons/play.png");
        } else {
            _tbtPlayPause.setImage("Resources/icons/pause.png");
        }
    });

    _font.loadFromFile("Resources/Ubuntu.ttf");


    _txtFieldSize.setFont(_font);
    _txtFieldSize.setCharacterSize(16);
    _txtFieldSize.setString("Field size:");
    _txtFieldSize.setPosition(sf::Vector2f(5,5));

    _txtPopulation.setFont(_font);
    _txtPopulation.setCharacterSize(16);
    _txtPopulation.setString("Population:");
    _txtPopulation.setPosition(sf::Vector2f(240,5));

    _txtX.setFont(_font);
    _txtX.setCharacterSize(16);
    _txtX.setString("x");
    _txtX.setPosition(sf::Vector2f(50, 30));

    _txtSteps.setFont(_font);
    _txtSteps.setCharacterSize(16);
    _txtSteps.setString("# of steps:");
    _txtSteps.setPosition(sf::Vector2f(350, 5));

    _txtStats.setFont(_font);
    _txtStats.setCharacterSize(16);
    _txtStats.setPosition(sf::Vector2f(580, 5));
}

void UiLayout::processEvent(sf::Event &event)
{
    _tbxWidth.processEvent(event);
    _tbxHeight.processEvent(event);
    _tbxSteps.processEvent(event);
    _ibtZoomIn.processEvent(event);
    _ibtZoomOut.processEvent(event);
    _ibtFaster.processEvent(event);
    _ibtSlower.processEvent(event);
    _tbtRunNCycles.processEvent(event);
    _tbtCreateField.processEvent(event);
    _tbtPlayPause.processEvent(event);
    _tbxPopulation.processEvent(event);
    _tbtGenPopulation.processEvent(event);
}
void UiLayout::draw(sf::RenderWindow &window) {

    window.draw(_tbxWidth);
    window.draw(_tbxHeight);
    window.draw(_tbxPopulation);
    window.draw(_tbxSteps);
    window.draw(_ibtZoomIn);
    window.draw(_ibtZoomOut);
    window.draw(_ibtFaster);
    window.draw(_ibtSlower);
    window.draw(_tbtRunNCycles);
    window.draw(_tbtCreateField);
    window.draw(_tbtPlayPause);
    window.draw(_tbtGenPopulation);

    window.draw(_txtFieldSize);
    window.draw(_txtX);
    window.draw(_txtPopulation);
    window.draw(_txtSteps);

    _txtStats.setString("born:          " + to_string(_gol->getBorn()) + "\nborn/died: " + to_string(_gol->getBornDied()));
    window.draw(_txtStats);
}
