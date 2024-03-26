#pragma once
#include <SFML/Graphics.hpp>

class EnergyBar : public sf::Drawable
{
public:
    EnergyBar();
    virtual ~EnergyBar();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;   //reescribimos el metodo DRAW por haberlo heredado de DRAWABLE
    void initTexture();
    int getEnergyPoints()const;
    void setEnergyPoints(int points);
    void update();

private:
    int _energy_points;     //Segun spritesheet son 5 puntos
    sf::Texture _energy_bar_texture;
    sf::Sprite _energy_bar_sprite;
    sf::IntRect _current_frame;
};

