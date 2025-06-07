#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

class Mapa{
public:
    Mapa();
    sf::FloatRect getWallBounds();
    void draw(sf::RenderWindow& window);
private:
    sf::RectangleShape tile;
    std::vector<sf::RectangleShape> tiles;
    sf::RectangleShape Wall;
    std::vector<sf::RectangleShape> Walls;
};


#endif // MAP_HPP
