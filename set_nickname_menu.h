#pragma once
#include <SFML/Graphics.hpp>
#define nickname_options 2

using namespace std;

class Nickname
{
public:
    Nickname(float width, float height);
    void draw(sf::RenderWindow& window);
    void MoveUp();
    void MoveDown( );
    int NicknamePressed()
    {
        return nickname_selected;
    }
private:
    sf::Font font;
    sf::Text nick_name[nickname_options];
    sf::Text text;
    int nickname_selected;
};