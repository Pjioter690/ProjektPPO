#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

#include "GameClass.hpp"

Game::Game(): scale(60),
    windowWidth(16*scale),//skala 120 to fullscreen
    windowHeight(9*scale),
    mainMenu(windowWidth, windowHeight, scale),
    map1(scale),
    playerHUD(scale),
    lvl(0),
    maxEnemies(20),
    maxCap(50)

    {
        view.setSize(sf::Vector2f{320.0f, 180.0f});
        mWindow.create(sf::VideoMode({static_cast<unsigned int>(windowWidth),static_cast<unsigned int>(windowHeight)}), "Dungeon Adventures",sf::Style::Titlebar | sf::Style::Close);
        enemies.emplace_back(std::make_unique<Ogre>(posX, posY));
        std::srand(static_cast<unsigned>(std::time(nullptr)));
    }

void Game::run() {
    sf::Clock clock;
    while (mWindow.isOpen()) {
        sf::Time deltaTime = clock.restart(); //glowny zegar gry
        processEvents();                      //obsluga event�w
        update(deltaTime);          //update wszystkich obiekt�w
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
        if(!isPaused)
        {
            if(hero->getHp()>0)
            {
                hero->control(deltaTime,map1,dynamic_cast<Weapon*>(mainMenu.getSelectedWeapon()));    // <--- sterowanie!
                hero->regenerate();
                hero->animate(deltaTime);
                playerDead=false;
                deathAnimationClock.restart();
            }
            else
            {
                hero->animate(deltaTime);
                if(deathAnimationClock.getElapsedTime().asSeconds()>=1.41f){
                    playerDead=true;
                    isPaused=true;
                    save(deltaTime,hero);
                }
            }
        }

        weapon->attack(hero->getDmg(),enemies,hero->getenergy(),hero->getmaxenergy(),hero);
        playerHUD.update(mWindow, *hero);
        hero->lvlUp();

        if(hero->getLevel()>lvl)
        {
            lvl=hero->getLevel();
            spawnMobs();
            maxEnemies=min(maxEnemies+5, maxCap);
        }
        if(!isPaused)
        {
            for(auto& enemy : enemies)
            {
                enemy->update(deltaTime, *hero, enemies,map1);
                enemy->animate(deltaTime);
                if(!enemy->GetisAlive())
                {
                        hero->gainExp(enemy->expValue);
                }
            }
        }


        enemies.erase(remove_if(enemies.begin(), enemies.end(),
        [](const unique_ptr<Enemy>& enemy) { return !enemy->GetisAlive(); }),
        enemies.end());
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
        for (auto& enemy : enemies)
        {
            enemy->draw(mWindow);
        }
        if (playerDead==false) {
            hero->draw(mWindow);
            weapon->draw(mWindow);
        }
        playerHUD.draw(mWindow);
        if(playerDead==true){
            mainMenu.drawGameOverScreen(mWindow);
        }
    }
    mWindow.display();
}

void Game::spawnMobs() {
    auto* hero = dynamic_cast<Hero*>(mainMenu.getSelectedHero());
    if (!hero) return;

    int current = static_cast<int>(enemies.size());
    int toSpawn = maxEnemies - current;
    if (toSpawn <= 0) return;

    const int cols = 28;  // kafelków w poziomie
    const int rows = 11;  // kafelków w pionie

    for (int i = 0; i < toSpawn; ++i) {
        for (int attempt = 0; attempt < 10; ++attempt) {
            int tx = std::rand() % cols;
            int ty = std::rand() % rows;

            // środek kafelka 100x100
            sf::Vector2f pos{ tx*100.f + 50.f, ty*100.f + 50.f };
            float radius = 20.f;

            if (map1.isWall(pos, radius)) continue;

            float dx = pos.x - hero->getPosition().x;
            float dy = pos.y - hero->getPosition().y;
            if (std::sqrt(dx*dx + dy*dy) < 100.f) continue;

            if (std::rand() % 2 == 0)
                enemies.emplace_back(std::make_unique<Goblin>(pos.x, pos.y));
            else
                enemies.emplace_back(std::make_unique<Zombie>(pos.x, pos.y));
            break;
        }

    }
    cout<<enemies.size()<<endl;
}
 void Game::save(sf::Time deltaTime, Hero* hero)
 {
     ofstream outFile;
     outFile.open("ProjektPPO\\saves\\game_stats.txt", ios::app);

     if(!outFile.is_open()){
        cout<<"Nie mozna otworzyc pliku do zapisu"<<endl;
        return;
     }

     score+=deltaTime.asSeconds()*0.1f;
     score+=hero->getLevel()*5;
     int K;
     for(auto& enemy : enemies)
     {
         K=enemy->killedEnemies;
     }
     score+=K;

     outFile<<"---------------------"<<endl;
     outFile<<"Score: "<<score<<endl;

     outFile.close();
     mainMenu.setScore(score);
 }
