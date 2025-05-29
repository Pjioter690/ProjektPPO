#ifndef MAINMENU_HPP
#define MAINMENU_HPP
#pragma once
using namespace std;

#include <iostream>
#include <SFML/Graphics.hpp>

class MainMenu{
public:
    MainMenu(int windowWidth, int windowHeight, int scale);
    void changeMenu();
    void draw(sf::RenderWindow& window);
    void drawCharacterChooseScreen(sf::RenderWindow& window);
    void updateHover(const sf::RenderWindow& window);
    void chooseCharacter(const sf::RenderWindow& window);
    bool checkIfMainMenuOpen();
    bool checkIfCharacterChooseScreenOpen();

private:
    sf::Font font;
    sf::Text start;
    sf::Text gameName;
    sf::RectangleShape startButton;
    sf::CircleShape chooseKnight, chooseWizard, chooseRogue;
    template<typename T>
    void centerOrigin(T& drawable);
    template<typename T>
    void scaleObject(T& drawable);
    int WindowScale;
    bool isHovered = false;
    bool isOpen, isCharacterSelectionOpen;
};
#endif // MAINMENU_HPP
