#pragma once
#include<iostream>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//#include "SubMenu.h"
#include "Audio.h"

///MENU PRINCIPAL
#define     INICIO              0
#define     RANK                1
#define     REGLA               2
#define     CRED                3
#define     SALIR               4
///MENU SECUNDARIO
#define     JUGAR               0
#define     INGRESAR_NOMBRE     1
//#define     SELEC_ZOMB          2
#define     VOLVER_PPAL         2
///MENU RANKING, REGLAMENTO y CREDITOS
#define     VOLVER              0
#define     SALIR_RyC           1
///MENU SELECCION DE ZOMBIE
#define     MORTY               0
#define     SALLY               1
#define     IGOR                2
#define     VOLVER_SECUN        3
#define     VOLVER_AL_PPAL      4



enum TIPO_MENU
{
    PRINCIPAL,
    RANKING,
    REGLAMENTO,
    CREDITOS,
    SECUNDARIO,
    SELECCION_ZOMBIE,
    GAME_OVER,
    WINNER,
    EXIT
};

class Menu : public sf::Drawable
{
public:
    Menu(TIPO_MENU tipo);
    virtual ~Menu();

    void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
    const int getSelectedItem();
    void setSelectedItem(const int i);
    void updateSelection();
    void updateSelectedItem();

    const int getSizeArray();   ///para saber cuantos textos tenemos

    void agregarTexto(std::string s, int string_size, sf::Vector2f position, bool green);
    void initBackground();
    void initFont();
    void initTextos();
    void initTextosPrincipal();
    void initTextosRanking();
    void initTextosReglamento();
    void initTextosCreditos();
    void initTextosSecundarios();
    void initTextosSeleccionZombie();
    void initTextosGameOver();
    void initTextosWinner();


    void up();
    void down();


private:
    TIPO_MENU _tipo_menu;  /// elijo el tipo de menu
    int _selected_item;
    sf::Font _font;
    std::vector<sf::Text> _array_textos;
    sf::Sprite _background;
    sf::Texture _texture_background;

};

