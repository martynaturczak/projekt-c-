#pragma once
#include <SFML/Graphics.hpp>
#define menu_options 3

using namespace std;

class Menu
{
public:
    Menu(float width, float height);
    void draw(sf::RenderWindow& window);
    void MoveUp();
    void MoveDown( );
    int MenuPressed()
    {
        return menu_selected;
    }
private:
    sf::Font font;
    sf::Text menu[menu_options];
    sf::Text text2, text3, text4;
    int menu_selected;
};