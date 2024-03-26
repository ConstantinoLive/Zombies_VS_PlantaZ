#include "Planta.h"
Planta::Planta(TIPO tipo, sf::Vector2i pos, bool look, Gestor_disparos& gestor) : _gestor_disparos(gestor)
{
    _type = tipo;
    _position = pos;
    _looking_left = look;
    initVariables();
    initTexture();
    initAnimation();

}


Planta::~Planta()
{

}

////////Funciones privadas////////

void Planta::initVariables()
{
    _width_texture = 650;
    _height_texture = 760;
    _end_of_frames_sheet = 2600;
    _speed = { 0.f,0.f };
    _can_move = true;

    switch (_type)
    {
    case FIRE:
        _damage = 3;
        _first_frame_of_sheet = sf::IntRect(0, 1520, _width_texture, _height_texture);
        _plant_sprite.setPosition(_position.x, _position.y);     //prueba de posicion
        break;
    case GREEN:
        _damage = 1;
        _first_frame_of_sheet = sf::IntRect(0, 0, _width_texture, _height_texture);
        _plant_sprite.setPosition(_position.x, _position.y);     //prueba de posicion
        break;
    case ICE:
        _damage = 2;
        _first_frame_of_sheet = sf::IntRect(0, 760, _width_texture, _height_texture);
        _plant_sprite.setPosition(_position.x, _position.y);     //prueba de posicion
        break;
    case SUPER_GREEN:
        _damage = 5;
        _first_frame_of_sheet = sf::IntRect(0, 2280, _width_texture, _height_texture);
        _plant_sprite.setPosition(_position.x, _position.y);     //prueba de posicion
        break;
    default:    //GREEN
        _damage = 1;
        _first_frame_of_sheet = sf::IntRect(0, 0, _width_texture, _height_texture);
        _plant_sprite.setPosition(_position.x, _position.y);     //prueba de posicion
        break;

    }
}

void Planta::initAnimation()
{
    _animationTimer.restart();
}


////////Funciones publicas////////

void Planta::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_plant_sprite, states);
}

sf::FloatRect Planta::getBounds() const
{
    return _plant_sprite.getGlobalBounds();
}


bool Planta::isLookingLeft()
{
    return _looking_left;
}

void Planta::setLookingLeft(bool look)
{
    _looking_left = look;
}

void Planta::setCanMove(bool m)
{
    _can_move = m;
}


void Planta::updateMovement()
{
    if (_can_move)
    {
        if (_looking_left)
            _speed.x = -1.f;
        else
            _speed.x = 1.f;

        _plant_sprite.move(_speed);
    }

}

sf::Vector2f Planta::getPosition()
{
    return _plant_sprite.getPosition();
}


void Planta::updateAnimation()
{
    ///cada 0.2 seg cambio la animacion

    if (_animationTimer.getElapsedTime().asSeconds() >= 0.3)
    {
        _current_frame.left += _width_texture;
        if (_current_frame.left >= _end_of_frames_sheet)
        {
            _current_frame.left = _first_frame_of_sheet.left;
        }
        _animationTimer.restart();
        _plant_sprite.setTextureRect(_current_frame);

    }


    if (isLookingLeft())
        _plant_sprite.setScale(0.11, 0.11);
    else if (!isLookingLeft())
        _plant_sprite.setScale(-0.11, 0.11);


}


void Planta::updateShooting()
{

    if (_spawn_shoot_timer.getElapsedTime().asSeconds() >= 3)            //spawneo disparos cada 3 segundos
    {
        //// Corrijo que el disparo salga de la boca de la planta///
        float position_shoot_x = _plant_sprite.getPosition().x;
        float position_shoot_y = _plant_sprite.getPosition().y;

        if (isLookingLeft())
        {
            position_shoot_x -= 40;
        }
        else
        {
            position_shoot_x += 40;
        }
        position_shoot_y += 10;
        /////////////////////////////////////////////////////////////


        _gestor_disparos.agregarDisparo(new Disparo(_type, { position_shoot_x,position_shoot_y }, _looking_left));
        _spawn_shoot_timer.restart();
    }
}

void Planta::update()
{
    updateMovement();
    updateAnimation();
    updateShooting();   //se encarga de spawnear disparos y pasarselos al gestor de disparos
}


void Planta::initTexture()
{
    _plant_texture.loadFromFile("img/enemigos.png");
    _plant_sprite.setTexture(_plant_texture);
    _current_frame = sf::IntRect(_first_frame_of_sheet.left, _first_frame_of_sheet.top, _width_texture, _height_texture);
    _plant_sprite.setTextureRect(_current_frame);
    _plant_sprite.setOrigin(_width_texture / 2, 0.f);   //desplazo el origen al medio del sprite para que al rotar quede ok
    _plant_sprite.setScale(0.11, 0.11); //0.11
}

