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
    //sf::FloatRect getWallBounds(sf::RectangleShape tile);
    void draw(sf::RenderWindow& window);
    bool isWall(sf::Vector2f position, float radius);
private:
    sf::RectangleShape tile;
    std::vector<sf::RectangleShape> tiles;
    sf::RectangleShape wall;
    std::vector<sf::RectangleShape> walls;
};


#endif // MAP_HPP
