#ifndef GAME_HPP
#define GAME_HPP
#pragma once
#include <SFML/Graphics.hpp>

#include"MainMenu.hpp"

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    int scale;
    int windowWidth, windowHeight;

    sf::RenderWindow mWindow;
    sf::Time mTimePerFrame;


    MainMenu mainMenu;
};

#endif
