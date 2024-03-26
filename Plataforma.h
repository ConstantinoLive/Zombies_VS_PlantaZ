#pragma once
#include <SFML/Graphics.hpp>

#include "Colisionable.h"



class Plataforma : public Colisionable
{
public:
    Plataforma();
    virtual ~Plataforma();
    void update();
    void mobility();

    sf::Sprite& getDraw();
    sf::FloatRect getBounds() const override;


protected:

private:
    sf::Sprite _sprite_bloque;
    sf::Texture _texture_bloque;

};


