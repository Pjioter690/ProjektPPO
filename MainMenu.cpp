#include "MainMenu.hpp"

MainMenu::MainMenu(){
    isOpen = true;
    if (!font.openFromFile("ProjektPPO\\fonts\\font1.ttf")) {

    }
    /*start.setFont(font);
    start.setString("Start Game");
    start.setCharacterSize(30);
    start.setFillColor(sf::Color::White);
    start.setPosition(100.f, 100.f);*/

    startButton.setSize(sf::Vector2f(200.f, 50.f));
    startButton.setFillColor(sf::Color::Blue);
    startButton.setPosition({90.f,90.f});
}
void MainMenu::changeMenu(){
    isOpen = !isOpen;
}
void MainMenu::draw(sf::RenderWindow& window){
    //window.draw(start);
    window.draw(startButton);
}
bool MainMenu::checkIfOpen(){
    return isOpen;
}
