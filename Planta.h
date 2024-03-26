#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>

#include "Colisionable.h"
#include "Disparo.h"
#include "Plataforma.h"
#include "Gestor_disparos.h"


#define _CRT_SECURE_NO_WARNINGS
#define LEFT    true
#define RIGHT   false

class Planta : public Colisionable, public sf::Drawable
{
public:
    Planta(TIPO tipo, sf::Vector2i pos, bool look, Gestor_disparos& gestor);
    virtual ~Planta();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;   //reescribimos el metodo DRAW por haberlo heredado de DRAWABLE
    sf::FloatRect getBounds() const override;                                     //reescribimos el metodo getBounds por haberlo heredado de COLISIONABLE
    bool isLookingLeft();               //devuelve true si la planta mira a la izquierda
    void setLookingLeft(bool look);
    void setCanMove(bool m);
    sf::Vector2f getPosition();
    void updateShooting();
    void updateMovement();
    void updateAnimation();
    void update();



protected:
    sf::Texture _plant_texture;
    sf::Sprite _plant_sprite;
    sf::IntRect _current_frame;
    sf::IntRect _first_frame_of_sheet;      //me sirve para saber las coordenadas donde arranca el frame de cada tipo de disparo
    int _end_of_frames_sheet;               //me sirve para saber hasta donde va cada sprite en los distintos tipos de disparos

    int _width_texture;
    int _height_texture;
    sf::Vector2f _speed;
    int _damage;
    sf::Vector2i _position;
    bool _looking_left;                     //booleano que indica si la planta mira a la izquierda o derecha(default:izq)
    TIPO _type;
    bool _can_move;
    sf::Clock _animationTimer;
    sf::Clock _spawn_shoot_timer;


    Gestor_disparos& _gestor_disparos;      //es una referencia al gestor disparos que gestionara todos los disparos generados por las plantas



    void initVariables();
    void initTexture();
    void initAnimation();



};

