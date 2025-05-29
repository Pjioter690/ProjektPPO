#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

#include "GameClass.hpp"

Game::Game(): scale(60),
    windowWidth(16*scale),//skala 120 to prawdopodobnie fullscreen
    windowHeight(9*scale),
    mainMenu(windowWidth, windowHeight, scale){
    mWindow.create(sf::VideoMode({static_cast<unsigned int>(windowWidth),static_cast<unsigned int>(windowHeight)}), "Dungeon Adventures",sf::Style::Titlebar | sf::Style::Close);
}

void Game::run() {
    sf::Clock clock;
    while (mWindow.isOpen()) {
        sf::Time deltaTime = clock.restart(); //glowny zegar gry
        processEvents();                      //obsluga event�w
        update(deltaTime);                    //update wszystkich obiekt�w
        render();                             //render wszystkich obiekt�w: trzeba rozdzieli� na kilka render�w zale�nie od menu
    }
}

void Game::processEvents() {
    while (const std::optional event = mWindow.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                mWindow.close();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Escape))
                if(mainMenu.checkIfMainMenuOpen())
                    mWindow.close();
            //tutaj dodawac kolejne eventy
        }
}

void Game::update(sf::Time deltaTime) {
    mainMenu.updateHover(mWindow);
    // update wszystkich obiekt�w + logika gry
}

void Game::render() {
    if(mainMenu.checkIfMainMenuOpen())
    {
        mWindow.clear();
        mainMenu.draw(mWindow);
        mWindow.display();
    }
    else if(mainMenu.checkIfCharacterChooseScreenOpen())
    {
        mWindow.clear();
        mainMenu.drawCharacterChooseScreen(mWindow);
        mWindow.display();
    }
}
