#include "Prize.h"
Prize::Prize(sf::Vector2f pos)
{
    _position = pos;
    initVariables();
    initTexture();
}

Prize::~Prize()
{
    //dtor
}



void Prize::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_prize_sprite, states);
}

sf::FloatRect Prize::getBounds() const
{
    return _prize_sprite.getGlobalBounds();
}


void Prize::update()
{
    _current_frame = getRandomPrize();
    _prize_sprite.setTextureRect(_current_frame);
}


int Prize::getPoints() const
{
    return _points;
}

sf::IntRect Prize::getRandomPrize()
{
    return sf::IntRect(_ubicacion_sprite_prize[rand() % 4], _ubicacion_sprite_prize[rand() % 4], _width_texture, _height_texture);
}


void Prize::initVariables()
{
    _points = 5;
    _width_texture = 32;
    _height_texture = 32;
    _current_frame = getRandomPrize();
}

void Prize::initTexture()
{
    _prize_texture.loadFromFile("img/Prize.png");
    _prize_sprite.setTexture(_prize_texture);
    _prize_sprite.setTextureRect(_current_frame);       //me quedo con un prize random
    _prize_sprite.setScale(1.85, 1.85);
    _prize_sprite.setPosition(_position);
}
