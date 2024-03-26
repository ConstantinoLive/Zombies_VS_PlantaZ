#include "EnergyBar.h"
EnergyBar::EnergyBar()
{
    _energy_points = 5;     //Dado por el sprite, ya que es de 5 puntos posibles
    initTexture();
    _energy_bar_sprite.setPosition(0.f, 720.f);
}

EnergyBar::~EnergyBar()
{
    //dtor
}

void EnergyBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_energy_bar_sprite, states);
}

void EnergyBar::initTexture()
{
    _energy_bar_texture.loadFromFile("img/Energy_Bar.png");
    _energy_bar_sprite.setTexture(_energy_bar_texture);
    _current_frame = sf::IntRect(0, 0, 433, 175);
    _energy_bar_sprite.setTextureRect(_current_frame);
}

int EnergyBar::getEnergyPoints() const
{
    return _energy_points;
}

void EnergyBar::setEnergyPoints(int points)
{
    _energy_points = points;
}

void EnergyBar::update()
{
    switch (_energy_points)
    {
    case 5:
        _current_frame = sf::IntRect(0, 0, 433, 175);
        break;
    case 4:
        _current_frame = sf::IntRect(0, 175, 433, 175);
        break;
    case 3:
        _current_frame = sf::IntRect(0, 350, 433, 175);
        break;
    case 2:
        _current_frame = sf::IntRect(0, 525, 433, 175);
        break;
    case 1:
        _current_frame = sf::IntRect(0, 700, 433, 175);
        break;
    case 0:
        _current_frame = sf::IntRect(0, 875, 433, 175);
        break;
    default:
        _current_frame = sf::IntRect(0, 875, 433, 175);
        break;
    }
    _energy_bar_sprite.setTextureRect(_current_frame);
    _energy_bar_sprite.setScale(0.4, 0.4);
    _energy_bar_sprite.setPosition(700.f, 720.f);
}
