#include "MainMenu.hpp"

MainMenu::MainMenu(int windowWidth, int windowHeight, int scale) :
chooseCharacterBackground(Back1), menuBackground(MenuBackground),windowWidth(windowWidth),windowHeight(windowHeight)
{
    isOpen = true;
    isCharacterSelectionOpen = false;
    WindowScale = scale/60;
    if (!Back1.loadFromFile("ProjektPPO\\textures\\back1.png"))
    {
        cerr << "Nie udalo sie wczytac tekstury!\n";
    }
    if (!font.loadFromFile("ProjektPPO\\fonts\\font1.ttf"))
    {
        cerr << "Nie udalo sie wczytac czcionki!\n";
    }
    if (!MenuBackground.loadFromFile("ProjektPPO\\textures\\MainBackground.png"))
    {
        cerr << "Nie udalo sie wczytac tekstury!\n";
    }
    menuBackground.setPosition({0.0f,0.0f});
    menuBackground.setTextureRect({{0, 0}, {1920, 1080}});
    menuBackground.setScale({0.5f, 0.5f});

    chooseCharacterBackground.setPosition({0.0f,0.0f});
    chooseCharacterBackground.setTextureRect({{0, 0}, {1920, 1080}});
    chooseCharacterBackground.setScale({0.5f, 0.5f});
    // Main menu
    start.setFont(font);
    start.setString("Start Game");
    start.setCharacterSize(30);
    start.setFillColor(sf::Color::White);
    centerOrigin(start);
    scaleObject(start);
    start.setPosition({static_cast<float>(windowWidth) / 2.f, static_cast<float>(windowHeight) / 1.3f});

    gameName.setFont(font);
    gameName.setString("Dungeon Adventures");
    gameName.setCharacterSize(60);
    gameName.setFillColor(sf::Color::White);
    gameName.setOutlineThickness(3);
    gameName.setOutlineColor(sf::Color::Red);
    centerOrigin(gameName);
    scaleObject(gameName);
    gameName.setPosition({static_cast<float>(windowWidth) / 2.f, static_cast<float>(windowHeight) / 6.f});

    startButton.setSize(sf::Vector2f(160.f, 50.f));
    centerOrigin(startButton);
    scaleObject(startButton);
    startButton.setPosition({static_cast<float>(windowWidth) / 2.f, static_cast<float>(windowHeight) / 1.3f});
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

    gameOver.setFont(font);
    gameOver.setString("GAME OVER");
    gameOver.setCharacterSize(120);
    gameOver.setFillColor(sf::Color::White);
    gameOver.setOutlineThickness(3);
    gameOver.setOutlineColor(sf::Color::Red);
    centerOrigin(gameOver);
    scaleObject(gameOver);
    gameOver.setPosition({static_cast<float>(windowWidth) / 2.f, static_cast<float>(windowHeight) / 4.f});

    score.setFont(font);
    score.setCharacterSize(90);
    score.setFillColor(sf::Color::White);
    score.setOutlineThickness(3);
    score.setOutlineColor(sf::Color::Red);
    centerOrigin(score);
    scaleObject(score);
    score.setPosition({static_cast<float>(windowWidth) / 2.f, static_cast<float>(windowHeight) / 2.f});

}
void MainMenu::changeMenu(){
    isOpen = !isOpen;
    isCharacterSelectionOpen = !isCharacterSelectionOpen;
}
void MainMenu::draw(sf::RenderWindow& window){
    window.draw(menuBackground);
    window.draw(startButton);
    window.draw(start);
    window.draw(gameName);
}
void MainMenu::drawCharacterChooseScreen(sf::RenderWindow& window){
    window.draw(chooseCharacterBackground);
    window.draw(chooseKnight);
    window.draw(chooseWizard);
    window.draw(chooseRogue);
}
void MainMenu::drawGameOverScreen(sf::RenderWindow& window){
    window.draw(gameOver);
    window.draw(score);
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
    drawable.setOrigin({bounds.left + bounds.width / 2.f,
                       bounds.top + bounds.height / 2.f});
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
if (chooseKnight.getGlobalBounds().contains(mouse)) {
        chooseKnight.setFillColor(sf::Color::White);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            selectedHero = std::make_unique<Knight>();
            selectedWeapon = std::make_unique<Sword>();
            isCharacterSelectionOpen = false;
        }
    } else {
        chooseKnight.setFillColor(sf::Color::Red);
    }

    if (chooseWizard.getGlobalBounds().contains(mouse)) {
        chooseWizard.setFillColor(sf::Color::White);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            selectedHero = std::make_unique<Wizard>();
            selectedWeapon = std::make_unique<Wand>();
            isCharacterSelectionOpen = false;
        }
    } else {
        chooseWizard.setFillColor(sf::Color::Blue);
    }

    if (chooseRogue.getGlobalBounds().contains(mouse)) {
        chooseRogue.setFillColor(sf::Color::White);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            selectedHero = std::make_unique<Rogue>();
            selectedWeapon = std::make_unique<Knife>();
            isCharacterSelectionOpen = false;
        }
    } else {
        chooseRogue.setFillColor(sf::Color::Green);
    }
}
void MainMenu::setScore(float gameScore)
{
    int scoreInt = static_cast<int>(gameScore);
    score.setString("Score: " + to_string(scoreInt));
    centerOrigin(score);
    score.setPosition({static_cast<float>(windowWidth) / 2.f, static_cast<float>(windowHeight) / 2.f});
}

Alive* MainMenu::getSelectedHero() { return selectedHero.get(); }
Weapon* MainMenu::getSelectedWeapon() { return selectedWeapon.get(); }

