#pragma once
#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>

#include "Menu.h"
#include "Player.h"
#include "Game_play.h"
#include "Partida.h"
#include "Ranking.h"
#include "Audio.h"
#include "Zombie.h"
#include "Partida.h"
#define _CRT_SECURE_NO_WARNINGS




class Juego2
{
public:
    Juego2();
    virtual ~Juego2();


    int run();

    TIPO_MENU menuPpal(sf::RenderWindow& window);
    TIPO_MENU ranking(sf::RenderWindow& window);
    TIPO_MENU reglamento(sf::RenderWindow& window);
    TIPO_MENU creditos(sf::RenderWindow& window);
    TIPO_MENU menuSecundario(sf::RenderWindow& window);
    TIPO_MENU seleccionZombie(sf::RenderWindow& window);
    TIPO_MENU gameOver(sf::RenderWindow& window);
    TIPO_MENU winner(sf::RenderWindow& window);

    void showStart(sf::RenderWindow& window);
    void showRule(sf::RenderWindow& window);
    void showBestTeam(sf::RenderWindow& window);
    void showZombieTeam(sf::RenderWindow& window);
    void showWinnerText(sf::RenderWindow& window);
    void showLoserText(sf::RenderWindow& window);
    void showRanking(sf::RenderWindow& window, Ranking& ranking);

    TIPO_MENU aJugarHijo(Player& player, int num_zombie, sf::RenderWindow& window);



private:
    int _n_zombie;

    TIPO_MENU _tipo_menu;
    Menu* _menu_ppal;
    Menu* _menu_ranking;
    Menu* _menu_reglamento;
    Menu* _menu_creditos;
    Menu* _menu_secundario;
    Menu* _menu_seleccion_zombie;
    Menu* _menu_game_over;
    Menu* _menu_winner;

    Player* _player;


};


