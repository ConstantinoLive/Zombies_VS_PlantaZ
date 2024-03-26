#pragma once
#include <random>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Zombie.h"
#include "Plataforma.h"
#include "Colisionable.h"
#include "Planta.h"
#include "Disparo.h"
#include "Gestor_disparos.h"
#include "Gestor_plantas.h"
#include "Prize.h"
#include "Lifebar.h"
#include <iostream>
#include "Partida.h"
#include "EnergyBar.h"
#include "Audio.h"
#include "Player.h"



class Game_play
{
public:
    Game_play(Player& player, int numeroZombie, sf::RenderWindow& window);
    virtual ~Game_play();
    void draw(sf::RenderWindow& window);
    void cmd();
    void check_collision_platform();

    void updateShoot(sf::RenderTarget& window);
    void updatePrize();
    void update(sf::RenderTarget& window);

    bool getGameOver() { return _game_over; }
    int getEnemigos() { return enemigos; }
    int getEnemigos_eliminados() { return enemigos_eliminados; }
    int getPuntaje() { return puntaje; }
    void setPuntaje(int n) { puntaje = puntaje + n; }
    std::string getNombrePlayer() { return _namePlayer; }

    void updatePlants2();
    void updatePlantGeneration();
    void updatePlantDeletion();
    void updatePlantsSelfMovement();
    Plataforma findPlatform(Planta plantita);
    sf::Vector2i getRandomPosition();
    void setNombrePlayer(std::string nombre);
    bool getWinner();

    std::vector<sf::Vector2i> _position =
    {
        {30,80},
        {60,80},
        {90,80},
        {120,80},
        {310,80},
        {330,80},
        {350,80},
        {380,80},
        {720,80},
        {750,80},
        {800,80},
        {1050,80},
        {1100,80},
        {1150,80},
        //14
        {360,210},
        {700,210},
        {710,210},
        {730,210},
        {920,210},
        {1050,210},
        {1100,210},
        {1120,210},
        //10
        {280,340},
        {300,340},
        {530,340},
        {540,340},
        {780,340},
        {800,340},
        {820,340},
        {850,340},
        //9
        {100,500},  //estas son del suelo
        {200,500},
        {300,500},
        {400,500},
        {500,500},
        {600,500},
        {700,500},
        {800,500},
        {900,500},
        {1000,500},
        {1100,500},
        //11
    };

protected:

private:
    Gestor_disparos _shoot_manager;
    Zombie* Z1;
    int numeroZombie;
    EnergyBar _energy_bar;
    Disparo* disparoZombie;
    std::string _namePlayer;

    int puntaje = 0;
    int vidas;
    int enemigos = 0;
    int enemigos_eliminados = 0;
    bool _winner = false;


    TIPO tipoDisparo;

    Gestor_plantas _plant_manager;
    sf::Clock _plant_spawn_timer;

    Prize* _prize = nullptr;
    sf::Clock _prize_timer;
    sf::Clock _dead;
    bool _prize_generated;
    bool colisionPlanta;
    Lifebar _life_bar;
    Audio Sound_4;
    Audio Sound_5;
    Audio Sound_7;



    bool _is_dead = false;      //bandera para ver si la vida llego al final,puede servir, revisar posible getter()
    bool _game_over = false;

    TIPO _random_type;

    Plataforma Plats[30];


    enum ESTADOS_GAME_PLAY {
        ACTION,
        PAUSE
    };

    ESTADOS_GAME_PLAY _estado;
    sf::Font _font_pause;
    sf::Text _text_pause;
    sf::Font _fontPlayer;
    sf::Text _textPlayer;
    sf::Font _fontPuntaje;
    sf::Text _textPuntaje;
    sf::Text _textvidas;
    sf::Text _cantvidas;

};
