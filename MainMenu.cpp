#include "MainMenu.hpp"

MainMenu::MainMenu(int windowWidth, int windowHeight, int scale) : start(font, "Start Game", 30), gameName(font, "Dungeon Adventures", 60)
{
    isOpen = true;
    WindowScale = scale/60;
    if (!font.openFromFile("ProjektPPO\\fonts\\font1.ttf"))
    {
        cerr << "Nie udalo sie wczytac czcionki!\n";
    }
    start.setFillColor(sf::Color::White);
    centerOrigin(start);
    scaleObject(start);
    start.setPosition({static_cast<float>(windowWidth) / 2.f, static_cast<float>(windowHeight) / 2.f});

    gameName.setFillColor(sf::Color::White);
    centerOrigin(gameName);
    scaleObject(gameName);
    gameName.setPosition({static_cast<float>(windowWidth) / 2.f, static_cast<float>(windowHeight) / 6.f});

    startButton.setSize(sf::Vector2f(160.f, 50.f));
    //startButton.setFillColor(sf::Color::Blue);
    centerOrigin(startButton);
    scaleObject(startButton);
    startButton.setPosition({static_cast<float>(windowWidth) / 2.f, static_cast<float>(windowHeight) / 2.f});
}
void MainMenu::changeMenu(){
    isOpen = !isOpen;
}
void MainMenu::draw(sf::RenderWindow& window){
    window.draw(startButton);
    window.draw(start);
    window.draw(gameName);
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
template<typename T>
void MainMenu::scaleObject(T& drawable){
    drawable.scale({static_cast<float>(WindowScale),static_cast<float>(WindowScale)});
}
void MainMenu::updateHover(const sf::RenderWindow& window)
{
    auto mouse = sf::Vector2f(sf::Mouse::getPosition(window));
    isHovered = startButton.getGlobalBounds().contains(mouse);

    startButton.setFillColor(isHovered ? sf::Color::Red : sf::Color::Blue);
}

