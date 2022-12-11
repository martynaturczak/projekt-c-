#include "gameover.h"

GameOver::GameOver(float width, float height)
{
    font.loadFromFile("ARIAL.TTF");

    game_over[0].setString("RANKING");
    game_over[0].setFillColor(sf::Color::White);
    game_over[0].setFont(font);
    game_over[0].setPosition(220, 140);
    game_over[0].setCharacterSize(13);

    game_over[1].setString("EXIT");
    game_over[1].setFillColor(sf::Color::White);
    game_over[1].setFont(font);
    game_over[1].setPosition(220, 160);
    game_over[1].setCharacterSize(13);

    gameover_selected = 0;

    text2.setString("GAME");
    text2.setFillColor(sf::Color::Yellow);
    text2.setFont(font);  
    text2.setPosition(150,50);    
    text2.setCharacterSize(30);
    text2.setStyle(sf::Text::Italic);

    text3.setString("OVER");
    text3.setFillColor(sf::Color::Yellow);    
    text3.setFont(font);  
    text3.setPosition(250,50);  
    text3.setCharacterSize(30);
    text3.setStyle(sf::Text::Italic);

    text4.setString("SCORE: ");
    text4.setFillColor(sf::Color::Yellow);    
    text4.setFont(font);  
    text4.setPosition(180,100);  
    text4.setCharacterSize(25);
    text4.setStyle(sf::Text::Italic);
    
}
void GameOver::draw(sf::RenderWindow& window)
{
    for (int i = 0; i < gameover_options; i++)
        window.draw(game_over[i]);
    window.draw(text2);
    window.draw(text3);
    window.draw(text4);
}
void GameOver::MoveUp()
{
    if (gameover_selected - 1 >= -1)
    {
        game_over[gameover_selected].setFillColor(sf::Color::White);
        gameover_selected--;
        if (gameover_selected == -1)
           gameover_selected = 1;
        game_over[gameover_selected].setFillColor(sf::Color::Yellow);
    }
}
void GameOver::MoveDown()
{
    if (gameover_selected + 1 <= gameover_options)
    {
        game_over[gameover_selected].setFillColor(sf::Color::White);
        gameover_selected++;
        if (gameover_selected == 2)
            gameover_selected = 0;
        game_over[gameover_selected].setFillColor(sf::Color::Yellow);
    }
}