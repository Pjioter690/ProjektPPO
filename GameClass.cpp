#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

#include "GameClass.hpp"

Game::Game(){
    scale = 60; //skala 120 to prawdopodobnie fullscreen
    windowSize.x = 16*scale;
    windowSize.y = 9*scale;
    mWindow.create(sf::VideoMode({960,540}), "Dungeon Adventures",sf::Style::Default);
} //trzeba dodac oddzielne wartosci window size

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
            //tutaj dodawac kolejne eventy
        }
}

void Game::update(sf::Time deltaTime) {
    // update wszystkich obiekt�w + logika gry
}

void Game::render() {
    mWindow.clear();
    while(mainMenu.checkIfOpen()){
        mainMenu.draw(mWindow);
    }
    // Rysowanie obiekt�w
    mWindow.display();
}
