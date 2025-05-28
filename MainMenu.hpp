#ifndef MAINMENU_HPP
#define MAINMENU_HPP
using namespace std;
#include <iostream>
#include <SFML/Graphics.hpp>

class MainMenu{
public:
    MainMenu();
    void changeMenu();
    void draw(sf::RenderWindow& window);
    bool checkIfOpen();
private:
    sf::Font font;
    sf::Text start;
    sf::RectangleShape startButton;
    bool isOpen;
};
#endif // MAINMENU_HPP
