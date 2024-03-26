#pragma once
#include <SFML/Graphics.hpp>


class Lifebar : public sf::Drawable
{
public:
    Lifebar();
    virtual ~Lifebar();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;   //reescribimos el metodo DRAW por haberlo heredado de DRAWABLE

    void initTexture();
    int getLifePoints();
    void setLifePoints(int points);
    void update();
    void validation();

private:
    int _life_points;     //Segun spritesheet son 5 puntos
    sf::Texture _life_bar_texture;
    sf::Sprite _life_bar_sprite;
    sf::IntRect _current_frame;

};


