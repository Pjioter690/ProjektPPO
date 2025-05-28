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
    centerOrigin(start);
    start.setPosition({static_cast<float>(windowWidth) / 2.f, static_cast<float>(windowHeight) / 2.f});

    startButton.setSize(sf::Vector2f(200.f, 50.f));
    startButton.setFillColor(sf::Color::Blue);
    centerOrigin(startButton);
    startButton.setPosition({static_cast<float>(windowWidth) / 2.f, static_cast<float>(windowHeight) / 2.f});
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
template<typename T>
void MainMenu::centerOrigin(T& drawable){
    sf::FloatRect bounds = drawable.getLocalBounds();
    drawable.setOrigin({bounds.position.x + bounds.size.x / 2.f,
                       bounds.position.y + bounds.size.y / 2.f});
}

