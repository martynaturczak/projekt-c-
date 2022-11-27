#include "menu.h"

Menu::Menu(float width, float height)
{
    font.loadFromFile("ARIAL.TTF");

    menu[0].setString("START GAME");
    menu[0].setFillColor(sf::Color::White);
    menu[0].setFont(font);
    menu[0].setPosition(200, 130);
    menu[0].setCharacterSize(13);

    menu[1].setString("RANKING");
    menu[1].setFillColor(sf::Color::White);
    menu[1].setFont(font);
    menu[1].setPosition(200, 150);
    menu[1].setCharacterSize(13);

    menu[2].setString("EXIT");
    menu[2].setFillColor(sf::Color::White);
    menu[2].setFont(font);
    menu[2].setPosition(200, 170);
    menu[2].setCharacterSize(13);
    menu_selected = 0;

    text2.setString("ON");
    text2.setFillColor(sf::Color::Yellow);
    text2.setFont(font);  
    text2.setPosition(35,120);    
    text2.setCharacterSize(19);
    text2.setStyle(sf::Text::Italic);

    text3.setString("THE OTHER");
    text3.setFillColor(sf::Color::Yellow);    
    text3.setFont(font);  
    text3.setPosition(35,142);  
    text3.setCharacterSize(25);
    text3.setStyle(sf::Text::Italic);
    
    text4.setString("SIDE");
    text4.setFillColor(sf::Color::Yellow);      
    text4.setFont(font);  
    text4.setPosition(137,169);
    text4.setCharacterSize(19);
    text4.setStyle(sf::Text::Italic);
}
void Menu::draw(sf::RenderWindow& window)
{
    for (int i = 0; i < menu_options; i++)
        window.draw(menu[i]);
    window.draw(text2);
    window.draw(text3);
    window.draw(text4);
}
void Menu::MoveUp()
{
    if (menu_selected - 1 >= -1)
    {
        menu[menu_selected].setFillColor(sf::Color::White);
        menu_selected--;
        if (menu_selected == -1)
           menu_selected = 2;
        menu[menu_selected].setFillColor(sf::Color::Yellow);
    }
}
void Menu::MoveDown()
{
    if (menu_selected + 1 <= menu_options)
    {
        menu[menu_selected].setFillColor(sf::Color::White);
        menu_selected++;
        if (menu_selected == 3)
            menu_selected = 0;
        menu[menu_selected].setFillColor(sf::Color::Yellow);
    }
}