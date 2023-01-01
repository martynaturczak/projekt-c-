#pragma once
#include <SFML/Graphics.hpp>
#define ranking_options 2

using namespace std;

class Ranking
{
public:
    Ranking(float width, float height);
    void draw(sf::RenderWindow& window);
    void MoveUp();
    void MoveDown( );
    int RankingPressed()
    {
        return ranking_selected;
    }
private:
    sf::Font font;
    sf::Text ranking[ranking_options];
    sf::Text text2, text3, text4, text5;
    int ranking_selected;
};