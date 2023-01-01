#include "set_nickname_menu.h"

Nickname::Nickname(float width, float height)
{
    font.loadFromFile("ARIAL.TTF");

    nick_name[0].setString("PLAY");
    nick_name[0].setFillColor(sf::Color::White);
    nick_name[0].setFont(font);
    nick_name[0].setPosition(200, 130);
    nick_name[0].setCharacterSize(13);

    nick_name[1].setString("BACK TO MAIN MENU");
    nick_name[1].setFillColor(sf::Color::White);
    nick_name[1].setFont(font);
    nick_name[1].setPosition(200, 150);
    nick_name[1].setCharacterSize(13);

    nickname_selected = 0;

    text.setString("SET NICKNAME");
    text.setFillColor(sf::Color::Yellow);
    text.setFont(font);  
    text.setPosition(140,50);    
    text.setCharacterSize(30);
    text.setStyle(sf::Text::Italic);
}
void Nickname::draw(sf::RenderWindow& window)
{
    for (int i = 0; i < nickname_options; i++)
        window.draw(nick_name[i]);
    window.draw(text);
}
void Nickname::MoveUp()
{
    if (nickname_selected - 1 >= -1)
    {
        nick_name[nickname_selected].setFillColor(sf::Color::White);
        nickname_selected--;
        if (nickname_selected == -1)
           nickname_selected = 1;
        nick_name[nickname_selected].setFillColor(sf::Color::Yellow);
    }
}
void Nickname::MoveDown()
{
    if (nickname_selected + 1 <= nickname_options)
    {
        nick_name[nickname_selected].setFillColor(sf::Color::White);
        nickname_selected++;
        if (nickname_selected == 2)
            nickname_selected = 0;
        nick_name[nickname_selected].setFillColor(sf::Color::Yellow);
    }
}