#include "Plataforma.h"
Plataforma::Plataforma()
{
    _texture_bloque.loadFromFile("img/Plataforma_ind1.png");
    _sprite_bloque.setTexture(_texture_bloque);

}

Plataforma::~Plataforma()
{
    //dtor
}

void Plataforma::update()
{

}

sf::Sprite& Plataforma::getDraw()
{
    return _sprite_bloque;
}

void Plataforma::mobility()
{

}

sf::FloatRect Plataforma::getBounds()const
{
    return _sprite_bloque.getGlobalBounds();
}
