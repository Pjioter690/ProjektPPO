#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

#include "GameClass.hpp"

Game::Game(): scale(60),
    windowWidth(16*scale),//skala 120 to prawdopodobnie fullscreen
    windowHeight(9*scale),
    mainMenu(windowWidth, windowHeight, scale),
    playerHUD(scale){
    view.setSize(sf::Vector2f{320.0f, 180.0f});
    mWindow.create(sf::VideoMode({static_cast<unsigned int>(windowWidth),static_cast<unsigned int>(windowHeight)}), "Dungeon Adventures",sf::Style::Titlebar | sf::Style::Close);
    enemies.emplace_back(std::make_unique<Zombie>(posX, posY));
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
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            mWindow.close();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            if (mainMenu.checkIfMainMenuOpen()) {
                std::cout << "Zamykanie aplikacji: " << mainMenu.checkIfMainMenuOpen() << std::endl;
                // mWindow.close();
            } else if (mainMenu.checkIfCharacterChooseScreenOpen()) {
                mainMenu.changeMenu();
            }
        }

        // tutaj dodawac kolejne eventy
    }
}

void Game::update(sf::Time deltaTime) {
    mainMenu.updateHover(mWindow);

    if(mainMenu.checkIfCharacterChooseScreenOpen())
        mainMenu.chooseCharacter(mWindow);

    if (auto* hero = dynamic_cast<Hero*>(mainMenu.getSelectedHero())) {
        auto* weapon = dynamic_cast<Weapon*>(mainMenu.getSelectedWeapon());
        hero->control(deltaTime,map1,dynamic_cast<Weapon*>(mainMenu.getSelectedWeapon()));    // <--- sterowanie!
        hero->update();     // <--- aktualizacja animacji
        playerHUD.update(mWindow, *hero);
        for(auto& enemy : enemies)
        {
            enemy->update(deltaTime, *hero);
            enemy->animate(deltaTime);
        }
    }
    // update wszystkich obiekt�w + logika gry
}

void Game::render() {

    mWindow.clear();
    if(mainMenu.checkIfMainMenuOpen())
    {
        mainMenu.draw(mWindow);
    }
    else if(mainMenu.checkIfCharacterChooseScreenOpen())
    {
        mainMenu.drawCharacterChooseScreen(mWindow);
    }
    else if (auto* hero = mainMenu.getSelectedHero()) {
        auto* weapon = dynamic_cast<Weapon*>(mainMenu.getSelectedWeapon());
        view.setCenter(hero->getPosition());
        mWindow.setView(view);
        map1.draw(mWindow);
        hero->draw(mWindow);
        weapon->draw(mWindow);
        for (auto& enemy : enemies)
        {
            enemy->draw(mWindow);
        }
        playerHUD.draw(mWindow);
    }
    mWindow.display();
}
