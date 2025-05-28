#include "MainMenu.hpp"

MainMenu::MainMenu(int windowWidth, int windowHeight) : start(font, "Start Game", 30)
{
    isOpen = true;
    if (!font.openFromFile("ProjektPPO\\fonts\\font1.ttf"))
    {
        cerr << "Nie udalo sie wczytac czcionki!\n";
    }
    float screenCentreY = windowHeight/2;

    start.setFillColor(sf::Color::White);
    sf::FloatRect bounds = start.getLocalBounds();
    float originX = bounds.position.x + bounds.size.x / 2.f;
    float originY = bounds.position.y + bounds.size.y / 2.f;
    start.setOrigin({originX, originY});
    start.setPosition({static_cast<float>(windowWidth) / 2.f, static_cast<float>(windowHeight) / 2.f});

    startButton.setSize(sf::Vector2f(200.f, 50.f));
    startButton.setFillColor(sf::Color::Blue);
    startButton.setPosition({90.f,90.f});
}
void MainMenu::changeMenu(){
    isOpen = !isOpen;
}
void MainMenu::draw(sf::RenderWindow& window){
    window.draw(startButton);
    window.draw(start);
}
bool MainMenu::checkIfOpen(){
    return isOpen;
}

