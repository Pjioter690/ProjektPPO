#include "PlayerHUD.hpp"
#include <cmath>

PlayerHUD::PlayerHUD(int scale): levelText(font, "1", 30.0f)
{
    WindowScale = scale/60;
    if (!font.openFromFile("ProjektPPO\\fonts\\font1.ttf"))
    {
        cerr << "Nie udalo sie wczytac czcionki!\n";
    }
    //----Pasek zycia----
    hpBarBackground.setFillColor(sf::Color(90, 90, 100));
    hpBarBackground.setOutlineColor(sf::Color(50, 50, 50));
    scaleObject(hpBarBackground);
    hpBarBackground.setSize(sf::Vector2f(300.0f, 25.0f));
    hpBarBackground.setOutlineThickness(3.0f);
    hpBarBackground.setPosition({10.0f, 10.0f});

    hpBarForeground.setFillColor(sf::Color::Red);
    scaleObject(hpBarForeground);
    hpBarForeground.setPosition({10.0f, 10.0f});
    //----Pasek EXP----
    expBarBackground.setFillColor(sf::Color(90, 90, 100));
    expBarBackground.setOutlineColor(sf::Color(50, 50, 50));
    scaleObject(expBarBackground);
    expBarBackground.setSize(sf::Vector2f(250.0f, 10.0f));
    expBarBackground.setOutlineThickness(3.0f);
    expBarBackground.setPosition({10.0f, 45.0f});

    expBarForeground.setFillColor(sf::Color::Green);
    scaleObject(expBarForeground);
    expBarForeground.setPosition({10.0f, 45.0f});

    /*levelText.setFillColor(sf::Color::White);
    levelText.setOutlineColor(sf::Color::Black);
    scaleObject(levelText);
    levelText.setOutlineThickness(3);
    levelText.setPosition({10.0f, 100.0f});*/

    //----Pasek Many----
    manaBarBackground.setFillColor(sf::Color(90, 90, 100));
    manaBarBackground.setOutlineColor(sf::Color(50, 50, 50));
    scaleObject(manaBarBackground);
    manaBarBackground.setSize(sf::Vector2f(250.0f, 10.0f));
    manaBarBackground.setOutlineThickness(3.0f);
    manaBarBackground.setPosition({10.0f, 65.0f});

    manaBarForeground.setFillColor(sf::Color(50, 50, 255));
    scaleObject(manaBarForeground);
    manaBarForeground.setPosition({10.0f, 65.0f});
}

void PlayerHUD::update(const sf::RenderWindow& window, Hero& player)
{
    hpBarForeground.setSize(sf::Vector2f(300.0f*(player.getHp()/player.getmaxHp()), 25.0f));
    expBarForeground.setSize(sf::Vector2f(250.0f*(player.getExp()/player.getmaxExp()), 10.0f));
    manaBarForeground.setSize(sf::Vector2f(250.0f*(player.getMana()/player.getmaxMana()), 10.0f));
  // levelText.setString("Poziom: " + std::to_string(player->getLevel()));*/
}

void PlayerHUD::draw(sf::RenderWindow& window)
{
    window.setView(window.getDefaultView());
    window.draw(hpBarBackground);
    window.draw(hpBarForeground);

    window.draw(expBarBackground);
    window.draw(expBarForeground);

    window.draw(manaBarBackground);
    window.draw(manaBarForeground);

    window.draw(levelText);
}

template<typename T>
void PlayerHUD::scaleObject(T& drawable){
    drawable.scale({static_cast<float>(WindowScale),static_cast<float>(WindowScale)});
}
