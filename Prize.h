#pragma once
#include<cstdlib>

#include"Colisionable.h"



class Prize : public Colisionable, public sf::Drawable
{
public:
    Prize(sf::Vector2f pos);
    virtual ~Prize();

    void draw(sf::RenderTarget& target, sf::RenderStates states)const override;  //reescribimos el metodo DRAW por haberlo heredado de DRAWABLE
    sf::FloatRect getBounds()const override;                                    //reescribimos el metodo getBounds por haberlo heredado de COLISIONABLE

    sf::IntRect getRandomPrize();

    void update();
    int getPoints()const;


protected:
    sf::Texture _prize_texture;
    sf::Sprite _prize_sprite;
    sf::IntRect _current_frame;

    int _width_texture;
    int _height_texture;
    int _ubicacion_sprite_prize[4] = { 0,32,64,96 };   //esto es el inicio de cada prize en el sprite, en ambos ejes
    int _points;
    sf::Vector2f _position;



    void initVariables();
    void initTexture();
};

