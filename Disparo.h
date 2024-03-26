#pragma once
#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>

//#include "Audio.h"
#include "Colisionable.h"

enum TIPO
{
    FIRE,
    GREEN,
    ICE,
    SUPER_GREEN,
    BRAIN
};


class Disparo : public Colisionable, public sf::Drawable
{
public:
    Disparo(TIPO tipo, sf::Vector2f pos, bool direct);
    Disparo();
    virtual ~Disparo();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override; //reescribimos el metodo DRAW por haberlo heredado de DRAWABLE
    sf::FloatRect getBounds() const override;                                   //reescribimos el metodo getBounds por haberlo heredado de COLISIONABLE


    int getDamage()const;
    void escala(float esc);
    void movement(float x, float y);

    void updateMovement();
    void updateAnimation();
    bool checkWindowBounds(sf::RenderTarget& target);
    void update();
    int getTipoPlanta();
    int getTipoZombie();
    int _tipoDisparoPlanta;
    int _tipoDisparoZombie;
    TIPO getTipo();
    TIPO esTipo;
    //Audio Sound_8;


protected:
    sf::Texture _shoot_texture;
    sf::Sprite _shoot_sprite;
    sf::IntRect _current_frame;
    sf::IntRect _first_frame_of_sheet;      //me sirve para saber las coordenadas donde arranca el frame de cada tipo de disparo
    TIPO _type;
    int _width_texture;
    int _height_texture;
    int _end_of_frames_sheet;               //me sirve para saber hasta donde va cada sprite en los distintos tipos de disparos
    sf::Vector2f _speed;
    bool _direction;                        //parametro que recibe desde la planta para saber la direction del disparo, true if left
    sf::Vector2f _start_position;           //posicion que se va a spawnear el disparo
    int _damage_shoot;
    sf::Clock _animationTimer;
    void initVariables();
    void initTexture();
    void initAnimation();
};
