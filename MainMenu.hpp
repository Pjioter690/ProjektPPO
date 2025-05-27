#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include <SFML/Graphics.hpp>

class MainMenu{
public:
    MainMenu();
    void changeMenu();
    void draw(sf::RenderWindow& window);
    bool checkIfOpen();
private:
    //sf::Text start;
    sf::RectangleShape startButton;
    bool isOpen;
    sf::Font font;
};
#endif // MAINMENU_HPP
