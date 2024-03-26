#include "Disparo.h"
Disparo::Disparo(TIPO tipo, sf::Vector2f pos, bool direct)//: Sound_8(8)
{
    _start_position = pos;
    _type = tipo;
    _direction = direct;
    initVariables();
    initTexture();
    initAnimation();
}

Disparo::Disparo()//: Sound_8(8)
{

}

Disparo::~Disparo()
{

}

void Disparo::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_shoot_sprite, states);
}

sf::FloatRect Disparo::getBounds() const
{
    return _shoot_sprite.getGlobalBounds();
}



void Disparo::initVariables()
{
    //En este caso, y a diferencia del sprite sheet de las plantas, este sprite sheet esta mas desordenado
    //esta mas desordenado y por ende las variables son todas distintas en cada tipo de disparo
//Sound_8.audioON();
    switch (_type)
    {
    case FIRE:
        _width_texture = 20;
        _height_texture = 16;
        _first_frame_of_sheet = sf::IntRect(106, 173, _width_texture, _height_texture);
        _end_of_frames_sheet = 186;
        _damage_shoot = 3;
        _shoot_sprite.setPosition(_start_position.x, _start_position.y);
        esTipo = TIPO::FIRE;
        break;
    case GREEN:
        _width_texture = 15;
        _height_texture = 15;
        _first_frame_of_sheet = sf::IntRect(320, 75, _width_texture, _height_texture);
        _end_of_frames_sheet = 380;
        _damage_shoot = 1;
        _shoot_sprite.setPosition(_start_position.x, _start_position.y);
        esTipo = TIPO::GREEN;
        break;
    case ICE:
        _width_texture = 20;
        _height_texture = 17;
        _first_frame_of_sheet = sf::IntRect(20, 137, _width_texture, _height_texture);
        _end_of_frames_sheet = 59;
        _damage_shoot = 2;
        _shoot_sprite.setPosition(_start_position.x, _start_position.y);
        esTipo = TIPO::ICE;
        break;
    case SUPER_GREEN:
        _width_texture = 22;
        _height_texture = 17;
        _first_frame_of_sheet = sf::IntRect(86, 136, _width_texture, _height_texture);
        _end_of_frames_sheet = 171;
        _damage_shoot = 5;
        _shoot_sprite.setPosition(_start_position.x, _start_position.y);
        esTipo = TIPO::SUPER_GREEN;
        break;
    case BRAIN:
        _width_texture = 30;
        _height_texture = 23;
        _first_frame_of_sheet = sf::IntRect(357, 224, _width_texture, _height_texture);
        _end_of_frames_sheet = 477;
        _damage_shoot = 1;
        _shoot_sprite.setPosition(_start_position.x, _start_position.y);
        esTipo = TIPO::BRAIN;
        break;
    default:
        _width_texture = 15;
        _height_texture = 15;
        _first_frame_of_sheet = sf::IntRect(320, 75, _width_texture, _height_texture);
        _end_of_frames_sheet = 380;
        _damage_shoot = 1;
        _shoot_sprite.setPosition(_start_position.x, _start_position.y);
        esTipo = TIPO::GREEN;
        break;
    }


}


void Disparo::initAnimation()
{
    _animationTimer.restart();
}

void Disparo::initTexture()     //unica de todos los disparos
{
    _shoot_texture.loadFromFile("img/shoot45.png");
    _shoot_sprite.setTexture(_shoot_texture);
    _current_frame = sf::IntRect(_first_frame_of_sheet.left, _first_frame_of_sheet.top, _width_texture, _height_texture);
    _shoot_sprite.setTextureRect(_current_frame);
    _shoot_sprite.setOrigin(_width_texture / 2, 0);
    _shoot_sprite.setScale(2.f, 2.f);
}


int Disparo::getDamage() const
{
    return _damage_shoot;
}

void Disparo::updateMovement()
{
    if (_direction)
        _speed.x = -2;//1.5
    else if (!_direction)
        _speed.x = 2;

    _shoot_sprite.move(_speed);
}


void Disparo::updateAnimation()
{
    ///cada 0.1 seg cambio la animacion
    if (_animationTimer.getElapsedTime().asSeconds() >= 0.1)
    {
        _current_frame.left += _width_texture;
        if (_current_frame.left >= _end_of_frames_sheet)
        {
            _current_frame.left = _first_frame_of_sheet.left;
        }
        _animationTimer.restart();
        _shoot_sprite.setTextureRect(_current_frame);
    }

    //ahora invierto o no, segun la direccion

    if (_speed.x > 0.f)  //va a la derecha?
    {
        _shoot_sprite.setScale(2.f, 2.f);
    }
    else if (_speed.x < 0.f) //va a la izquierda?
    {
        _shoot_sprite.setScale(-2.f, 2.f);
    }
}


void Disparo::update()
{
    updateMovement();
    updateAnimation();
}

bool Disparo::checkWindowBounds(sf::RenderTarget& target)
{
    if ((_shoot_sprite.getPosition().x < 0) || (_shoot_sprite.getPosition().x > target.getSize().x))
        return true;
    else
        return false;
}

TIPO Disparo::getTipo()
{
    return esTipo;
}
