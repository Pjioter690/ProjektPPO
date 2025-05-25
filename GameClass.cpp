#include <SFML/Graphics.hpp>
#include <iostream>
#pragma Once
using namespace std;

#include "GameClass.hpp"

Game::Game()
: mWindow(sf::VideoMode({800, 600}), "Dungeon Adventures"){
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
    // Rysowanie obiekt�w
    mWindow.display();
}
