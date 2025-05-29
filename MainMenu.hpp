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
    bool checkIfOpen();
private:
    sf::Font font;
    sf::Text start;
    sf::RectangleShape startButton;
    bool isOpen;
    template<typename T>
    void centerOrigin(T& drawable);
    template<typename T>
    void scaleObject(T& drawable);
    int WindowScale;

};
#endif // MAINMENU_HPP
