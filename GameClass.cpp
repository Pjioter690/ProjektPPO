#include <SFML/Graphics.hpp>
#include <iostream>
#pragma Once
using namespace std;

#include "GameClass.hpp"

Game::Game()
: mWindow(sf::VideoMode({800, 600}), "Dungeon Adventures"){
} //trzeba dodaæ oddzieln¹ wartoœæ window size

void Game::run() {
    sf::Clock clock;
    while (mWindow.isOpen()) {
        sf::Time deltaTime = clock.restart(); //g³ówny zegar gry
        processEvents();                      //obs³uga eventów
        update(deltaTime);                    //update wszystkich obiektów
        render();                             //render wszystkich obiektów: trzeba rozdzieliæ na kilka renderów zale¿nie od menu
    }
}

void Game::processEvents() {
    while (const std::optional event = mWindow.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                mWindow.close();
            //tutaj dodawaæ kolejne eventy
        }
}

void Game::update(sf::Time deltaTime) {
    // update wszystkich obiektów + logika gry
}

void Game::render() {
    mWindow.clear();
    // Rysowanie obiektów
    mWindow.display();
}
