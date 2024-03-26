#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Colisionable.h"
#include "Disparo.h"
#include "Gestor_disparos.h"
#include "Lifebar.h"
#include "EnergyBar.h"
#include "Audio.h"



class Zombie : public Colisionable
{
public:
    Zombie(int opc, Gestor_disparos& gestor);
    enum ESTADOS
    {
        NACIMIENTO,
        QUIETO,
        QUIETO_IZQ,
        CAMINANDO_DER,
        CAMINANDO_IZQ,
        SALTANDO,
        CAMINANDO_DER_SALTANDO,
        CAMINANDO_IZQ_SALTANDO,
        DISPARANDO,
        MURIENDO,

    };
    virtual ~Zombie();
    void update();
    void mobility();
    sf::Sprite& getDraw();
    void suelo(float x, float y);
    Disparo* _disparo;
    Lifebar lb;
    Audio sound_2;
    Audio Sound_6;
    float getjump_force();
    sf::FloatRect getBounds() const override;
    bool isZPressed = false;
    bool yaDisparo = false;
    bool zombieIzquierda;
    void update_muriendo();
    float gettimeshoot();
    void settimeshoot(sf::Time);

    int getvida() { return _vida; }
    void setOpcion(int opc) { _opcion = opc; }
    int getOpcion() { return _opcion; }

protected:
    Gestor_disparos& _gestor_disparos;
private:


    sf::Sprite _sprite_zombie;
    sf::Texture _texture_zombie;

    ESTADOS _estado;
    int _xtexture = 0;

    float _jump_force;
    bool _delaySalto;
    sf::Clock _energiaRegen;
    float _frame;
    sf::Vector2f _prevPos;
    sf::Clock _animationTimer;
    sf::Clock _spawn_shoot_timer;
    sf::Time segundos;
    sf::Time _time_shoot;
    int _vida = 3;
    int _energia = 100;
    int _opcion;
};

