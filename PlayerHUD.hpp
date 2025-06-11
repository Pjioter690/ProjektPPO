#ifndef PLAYERHUD_HPP
#define PLAYERHUD_HPP
#pragma once
#include <SFML/Graphics.hpp>
#include "Alive.hpp"
#include <iostream>
using namespace std;


class PlayerHUD
{
public:
    PlayerHUD(int scale);
    void update(const sf::RenderWindow& window, Hero& player);
    void draw(sf::RenderWindow& window);
private:
    sf::RectangleShape hpBarBackground, expBarBackground, energyBarBackground;
    sf::RectangleShape hpBarForeground, expBarForeground, energyBarForeground;
    sf::Font font;
    sf::Text levelText;

    int WindowScale;

    template<typename T>
    void scaleObject(T& drawable);
};
#endif // PLAYERHUD_HPP




