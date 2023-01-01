#include "ranking.h"

Ranking::Ranking(float width, float height)
{
    font.loadFromFile("ARIAL.TTF");

    ranking[0].setString("BACK TO MAIN MENU");
    ranking[0].setFillColor(sf::Color::Yellow);
    ranking[0].setFont(font);
    ranking[0].setPosition(10, 20);
    ranking[0].setCharacterSize(13);

    ranking[1].setString("EXIT");
    ranking[1].setFillColor(sf::Color::White);
    ranking[1].setFont(font);
    ranking[1].setPosition(10, 40);
    ranking[1].setCharacterSize(13);

    ranking_selected = 0;

    text2.setString("RANKING");
    text2.setFillColor(sf::Color::Yellow);
    text2.setFont(font);  
    text2.setPosition(180,50);    
    text2.setCharacterSize(30);
    text2.setStyle(sf::Text::Italic);

    text3.setString("1.");
    text3.setFillColor(sf::Color::Yellow);    
    text3.setFont(font);  
    text3.setPosition(150,90);  
    text3.setCharacterSize(30);
    text3.setStyle(sf::Text::Italic);

    text4.setString("2. ");
    text4.setFillColor(sf::Color::Yellow);    
    text4.setFont(font);  
    text4.setPosition(150,130);  
    text4.setCharacterSize(30);
    text4.setStyle(sf::Text::Italic);

    text5.setString("3. ");
    text5.setFillColor(sf::Color::Yellow);    
    text5.setFont(font);  
    text5.setPosition(150,170);  
    text5.setCharacterSize(30);
    text5.setStyle(sf::Text::Italic);
    
}
void Ranking::draw(sf::RenderWindow& window)
{
    for (int i = 0; i < ranking_options; i++)
        window.draw(ranking[i]);
    window.draw(text2);
    window.draw(text3);
    window.draw(text4);
    window.draw(text5);
}
void Ranking::MoveUp()
{
    if (ranking_selected - 1 >= -1)
    {
        ranking[ranking_selected].setFillColor(sf::Color::White);
        ranking_selected--;
        if (ranking_selected == -1)
           ranking_selected = 1;
        ranking[ranking_selected].setFillColor(sf::Color::Yellow);
    }
}
void Ranking::MoveDown()
{
    if (ranking_selected + 1 <= ranking_options)
    {
        ranking[ranking_selected].setFillColor(sf::Color::White);
        ranking_selected++;
        if (ranking_selected == 2)
            ranking_selected = 0;
        ranking[ranking_selected].setFillColor(sf::Color::Yellow);
    }
}