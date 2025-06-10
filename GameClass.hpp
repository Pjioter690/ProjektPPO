#ifndef GAME_HPP
#define GAME_HPP
#pragma once
#include <SFML/Graphics.hpp>

#include"MainMenu.hpp"
#include"PlayerHUD.hpp"
#include"Map.hpp"

class Game {
public:
    Game();
    void run();

private:
    sf::View view;
    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    int scale;
    int windowWidth, windowHeight;

    sf::RenderWindow mWindow;
    sf::Time mTimePerFrame;


    MainMenu mainMenu;
    PlayerHUD playerHUD;
    Mapa map1;
    vector<unique_ptr<Enemy>> enemies;
    int posX=0;
    int posY=0;
    bool spawn=true;


};

#endif
