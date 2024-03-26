#include "Menu.h"
#include "Menu.h"

Menu::Menu(TIPO_MENU tipo)
{
    _tipo_menu = tipo;        //en base a uno de los 7 posibles tipos de menu
    initFont();
    initBackground();
    initTextos();
    _selected_item = 0;

}

Menu::~Menu()
{
    //dtor
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_background, states);
    for (sf::Text _t : _array_textos)
    {
        target.draw(_t, states);
    }
}

const int Menu::getSelectedItem()
{
    return _selected_item;
}

void Menu::setSelectedItem(const int i)
{
    _selected_item = i;
}


void Menu::up()
{
    if (_selected_item - 1 >= 0)
    {
        _array_textos[_selected_item].setFillColor(sf::Color(255, 255, 255, 80));
        _selected_item--;

        _array_textos[_selected_item].setFillColor(sf::Color(0,255,102));
    }
}

void Menu::down()
{
    if (_selected_item + 1 < getSizeArray())
    {
        _array_textos[_selected_item].setFillColor(sf::Color(255, 255, 255, 80));
        _selected_item++;

        _array_textos[_selected_item].setFillColor(sf::Color(0, 255, 102));
    }
}


void Menu::updateSelection()
{
    updateSelectedItem();
    for (sf::Text t : _array_textos)
    {
        t.setFillColor(sf::Color(255, 255, 255, 80));                  ///Des-seleccionamos todos
    }
    _array_textos[_selected_item].setFillColor(sf::Color(0, 255, 102));   ///Pintamos el seleccionado
}


void Menu::updateSelectedItem()
{
    if (_selected_item <= 0)
        _selected_item = 0;
    else if (_selected_item >= getSizeArray())
        _selected_item = getSizeArray() - 1;

}

const int Menu::getSizeArray()
{
    return int(_array_textos.size());
}

void Menu::agregarTexto(std::string s, int string_size, sf::Vector2f position, bool green)
{
    sf::Text texto;
    
    texto = sf::Text(s, _font, string_size);
    texto.setPosition(position);
    if (green)
    {
        texto.setFillColor(sf::Color(0, 255, 102));
    }
    else
    {
        texto.setFillColor(sf::Color(255, 255, 255, 80));
    }
    _array_textos.push_back(texto);
}


void Menu::initBackground()
{
    sf::Vector2f scale;
    switch (_tipo_menu)
    {
    case TIPO_MENU::PRINCIPAL:
        _texture_background.loadFromFile("img/tumba.png");
        scale = { 0.23,0.2 };

        break;
    case TIPO_MENU::RANKING:
        _texture_background.loadFromFile("img/background_subMenu.png");
        scale = { 1.36,1.25 };
        break;
    case TIPO_MENU::REGLAMENTO:
        _texture_background.loadFromFile("img/background_subMenu.png");
        scale = { 1.36,1.25 };
        break;
    case TIPO_MENU::CREDITOS:
        _texture_background.loadFromFile("img/background_subMenu.png");
        scale = { 1.36,1.25 };
        break;
    case TIPO_MENU::SECUNDARIO:
        _texture_background.loadFromFile("img/background_subMenu.png");
        scale = { 1.36,1.25 };
        break;
    case TIPO_MENU::SELECCION_ZOMBIE:
        _texture_background.loadFromFile("img/background_subMenu.png");
        scale = { 1.36,1.25 };
        break;
    case TIPO_MENU::GAME_OVER:
        _texture_background.loadFromFile("img/mano_zombie.jpg");
        scale = { 0.23,0.2 };
        break;
    case TIPO_MENU::WINNER:
        _texture_background.loadFromFile("img/background_subMenu.png");
        scale = { 1.36,1.25 };
        break;
    default:
        _texture_background.loadFromFile("img/tumba.png");
        scale = { 0.23,0.2 };
        break;
    }
    _background.setTexture(_texture_background);
    _background.setScale(scale);
}

void Menu::initFont()
{
    _font.loadFromFile("font/Come With Us.ttf");
}



void Menu::initTextos()
{
    switch (_tipo_menu)
    {
    case TIPO_MENU::PRINCIPAL:
        initTextosPrincipal();
        break;
    case TIPO_MENU::RANKING:
        initTextosRanking();
        break;
    case TIPO_MENU::REGLAMENTO:
        initTextosReglamento();
        break;
    case TIPO_MENU::CREDITOS:
        initTextosCreditos();
        break;
    case TIPO_MENU::SECUNDARIO:
        initTextosSecundarios();
        break;
    case TIPO_MENU::SELECCION_ZOMBIE:
        initTextosSeleccionZombie();
        break;
    case TIPO_MENU::GAME_OVER:
        initTextosGameOver();
        break;
    case TIPO_MENU::WINNER:
        initTextosWinner();
        break;
    default:
        initTextosPrincipal();
        break;
    }
}

void Menu::initTextosPrincipal()
{
    int width = 1220;
    int height = 800;

    agregarTexto("INICIO", 35, sf::Vector2f(width / 2.08, height / 5 * 1.2), true);
    agregarTexto("RANKING", 35, sf::Vector2f(width / 2.17, height / 5 * 1.7), false);
    agregarTexto("REGLAS", 35, sf::Vector2f(width / 2.17, height / 5 * 2.2), false);
    agregarTexto("CREDITOS", 35, sf::Vector2f(width / 2.17, height / 5 * 2.7), false);
    agregarTexto("SALIR", 35, sf::Vector2f(width / 2.07, height / 5 * 3.2), false);
}

void Menu::initTextosRanking()
{
    //int width=1220;
    //int height=800;

    agregarTexto("VOLVER", 30, { 300,685 }, true);
    agregarTexto("SALIR", 30, { 813,685 }, false);
}

void Menu::initTextosCreditos()
{
    //int width=1220;
    //int height=800;

    agregarTexto("VOLVER", 30, { 300,685 }, true);
    agregarTexto("SALIR", 30, { 813,685 }, false);
}

void Menu::initTextosReglamento()
{
    //int width=1220;
    //int height=800;

    agregarTexto("VOLVER", 30, { 300,685 }, true);
    agregarTexto("SALIR", 30, { 813,685 }, false);
}

void Menu::initTextosSecundarios()
{
    int width = 1220;
    int height = 800;

    agregarTexto("JUGAR", 40, sf::Vector2f(width / 6, height / 3.5 * 1.5), true);
    agregarTexto("INGRESAR NOMBRE", 40, sf::Vector2f(width / 6, height / 3.5 * 2), false);
    agregarTexto("VOLVER", 40, sf::Vector2f(width / 6, height / 3.5 * 2.5), false);
    //agregarTexto("SELECCIONAR TIPO DE ZOMBIE",40,sf::Vector2f(width / 6, height / 3.5 * 2),false);
    //agregarTexto("VOLVER",40,sf::Vector2f(width / 6, height / 3.5 * 2.5),false);
}

void Menu::initTextosSeleccionZombie()
{
    int width = 1220;
    int height = 800;

    agregarTexto("MORTY", 30, sf::Vector2f(width / 6, height / 3.5 * 2.5), true);
    agregarTexto("SALLY", 30, sf::Vector2f(width / 2.3, height / 3.5 * 2.5), false);
    agregarTexto("IGOR", 30, sf::Vector2f(width / 1.5, height / 3.5 * 2.5), false);
    agregarTexto("VOLVER", 30, sf::Vector2f(width / 6, height / 3.5 * 3), false);
    agregarTexto("VOLVER AL INICIO", 30, sf::Vector2f(width / 1.5, height / 3.5 * 3), false);
}

void Menu::initTextosGameOver()
{
    int width = 1220;
    int height = 800;

    agregarTexto("VOLVER", 30, { 300,685 }, true);
    agregarTexto("SALIR", 30, { 813,685 }, false);
}

void Menu::initTextosWinner()
{
    initTextosGameOver();///son las mismas opciones al ganar o perder :)
}

