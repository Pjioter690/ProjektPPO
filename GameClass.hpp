#ifndef GAME_HPP
#define GAME_HPP
#pragma once
#include <SFML/Graphics.hpp>

#include"MainMenu.hpp"
#include"PlayerHUD.hpp"
#include"Map.hpp"
#include"Alive.hpp"
#include<fstream>

class Game {
public:
    Game();
    void run();

private:
    sf::View view;
    int lvl;
    int maxEnemies;
    const int maxCap;
    void processEvents();
    void update(sf::Time deltaTime);
    void spawnMobs();
    void render();
    void save(sf::Time deltaTime, Hero* hero);
    int scale;
    int windowWidth, windowHeight;

    sf::RenderWindow mWindow;
    sf::Time mTimePerFrame;
    sf::Clock deathAnimationClock;


    MainMenu mainMenu;
    PlayerHUD playerHUD;
    Mapa map1;
    vector<unique_ptr<Enemy>> enemies;
    int posX=1700;
    int posY=500;
    bool spawn=true;
    bool isPaused=false;
    bool playerDead=false;
    float score=0;
};

#endif
