#pragma once
#include <SFML/Graphics.hpp>
#define gameover_options 2

using namespace std;

class GameOver
{
public:
    GameOver(float width, float height);
    void draw(sf::RenderWindow& window);
    void MoveUp();
    void MoveDown( );
    int GameOverPressed()
    {
        return gameover_selected;
    }
private:
    sf::Font font;
    sf::Text game_over[gameover_options];
    sf::Text text2, text3, text4;
    int gameover_selected;
};