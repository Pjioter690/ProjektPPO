#include "MainMenu.hpp"

MainMenu::MainMenu(int windowWidth, int windowHeight, int scale) : start(font, "Start Game", 30), gameName(font, "Dungeon Adventures", 60)
{
    isOpen = true;
    isCharacterSelectionOpen = false;
    WindowScale = scale/60;
    if (!font.openFromFile("ProjektPPO\\fonts\\font1.ttf"))
    {
        cerr << "Nie udalo sie wczytac czcionki!\n";
    }
    //projektowanie Main menu
    start.setFillColor(sf::Color::White);
    centerOrigin(start);
    scaleObject(start);
    start.setPosition({static_cast<float>(windowWidth) / 2.f, static_cast<float>(windowHeight) / 2.f});

    gameName.setFillColor(sf::Color::White);
    centerOrigin(gameName);
    scaleObject(gameName);
    gameName.setPosition({static_cast<float>(windowWidth) / 2.f, static_cast<float>(windowHeight) / 6.f});

    startButton.setSize(sf::Vector2f(160.f, 50.f));
    centerOrigin(startButton);
    scaleObject(startButton);
    startButton.setPosition({static_cast<float>(windowWidth) / 2.f, static_cast<float>(windowHeight) / 2.f});
    //Projektowanie Character Selection
    chooseKnight.setFillColor(sf::Color::Red);
    chooseKnight.setRadius(30.f);
    centerOrigin(chooseKnight);
    scaleObject(chooseKnight);
    chooseKnight.setPosition({static_cast<float>(windowWidth) / 2.f, static_cast<float>(windowHeight) / 2.f});

    chooseWizard.setFillColor(sf::Color::Blue);
    chooseWizard.setRadius(30.f);
    centerOrigin(chooseWizard);
    scaleObject(chooseWizard);
    chooseWizard.setPosition({static_cast<float>(windowWidth) / 4.f, static_cast<float>(windowHeight) / 2.f});

    chooseRogue.setFillColor(sf::Color::Green);
    chooseRogue.setRadius(30.f);
    centerOrigin(chooseRogue);
    scaleObject(chooseRogue);
    chooseRogue.setPosition({static_cast<float>(windowWidth)*3.f/4.f, static_cast<float>(windowHeight) / 2.f});
}
void MainMenu::changeMenu(){
    isOpen = !isOpen;
    isCharacterSelectionOpen = !isCharacterSelectionOpen;
}
void MainMenu::draw(sf::RenderWindow& window){
    window.draw(startButton);
    window.draw(start);
    window.draw(gameName);
}
void MainMenu::drawCharacterChooseScreen(sf::RenderWindow& window){
    window.draw(chooseKnight);
    window.draw(chooseWizard);
    window.draw(chooseRogue);
}
bool MainMenu::checkIfMainMenuOpen(){
    return isOpen;
}
bool MainMenu::checkIfCharacterChooseScreenOpen(){
    return isCharacterSelectionOpen;
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
    if(isOpen)
        if(isHovered)
            if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                changeMenu();
            }
}
void MainMenu::chooseCharacter(const sf::RenderWindow& window)
{
    auto mouse = sf::Vector2f(sf::Mouse::getPosition(window));
    isHovered = chooseKnight.getGlobalBounds().contains(mouse);

    chooseKnight.setFillColor(isHovered ? sf::Color::White : sf::Color::Red );
    if(isCharacterSelectionOpen)
        if(isHovered)
            if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                cout<<"Wybrano Rycerza!"<<endl;
            }
}

