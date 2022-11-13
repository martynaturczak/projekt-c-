#pragma once
#ifndef Included_NameModel_H 
#define Included_NameModel_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;

class TileMap : public sf::Drawable, public sf::Transformable
{
public: 
    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif