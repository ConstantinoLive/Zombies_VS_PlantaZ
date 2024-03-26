#include "Zombie.h"
Zombie::Zombie(int opc, Gestor_disparos& gestor) : _gestor_disparos(gestor), sound_2(2), Sound_6(6)
{
    setOpcion(opc);
    segundos = sf::seconds(1.f);
    if (getOpcion() == 0)
    {
        _texture_zombie.loadFromFile("img/zombie_DI6.png");
        _sprite_zombie.setTexture(_texture_zombie);
        _sprite_zombie.setPosition(0, 485); // posicion inicial
        _estado = ESTADOS::NACIMIENTO; //estado inicial
        _jump_force = 0; //Fuerza de salto inicial

    }
    else
    {
        if (getOpcion() == 1)
        {
            _texture_zombie.loadFromFile("img/zombie_girl_DI6.png");
            _sprite_zombie.setTexture(_texture_zombie);
            _sprite_zombie.setScale(0.8, 0.8);
            _sprite_zombie.setPosition(0, 485); // posicion inicial
            _estado = ESTADOS::QUIETO; //estado inicial
            _jump_force = 0; //Fuerza de salto inicial
        }
        else
        {
            if (getOpcion() == 2)
            {
                _frame = 0;
                _texture_zombie.loadFromFile("img/protagonista_2.png");
                _sprite_zombie.setTexture(_texture_zombie);
                _sprite_zombie.setTextureRect({ 0,0,378,890 });
                _sprite_zombie.setOrigin(_sprite_zombie.getGlobalBounds().width / 2, _sprite_zombie.getGlobalBounds().height / 11);
                _sprite_zombie.setPosition(50, 485);
                _estado = ESTADOS::QUIETO;
                _jump_force = 0; //Fuerza de salto inicial
            }
        }
    }
}

Zombie::~Zombie()
{
    //dtor
}

void Zombie::update()
{
    _time_shoot = _spawn_shoot_timer.getElapsedTime();
    if (getOpcion() == 0)
    {
        //*********************MORTY*********************************
        switch (_estado)
        {
        case NACIMIENTO:

            _xtexture = (int)_sprite_zombie.getPosition().x / 10 % 6;
            _xtexture = _xtexture * 76, 5;//75
            _sprite_zombie.setTextureRect(sf::IntRect(_xtexture, 385, 76.5, 77));//x,385,75,90
            _sprite_zombie.move(0.7, 0);
            _estado = ESTADOS::QUIETO;
            break;
        case QUIETO:

            _sprite_zombie.setTextureRect(sf::IntRect(0, 204, 51, 82)); //_sprite_zombie.setTextureRect(sf::IntRect(0,189.50,65,94.75));
            if (_energiaRegen.getElapsedTime().asSeconds() >= 5)
            {
                if (_energia <= 95)
                    _energia += 5;
                zombieIzquierda = false;
            }

            break;
        case QUIETO_IZQ:

            _sprite_zombie.setTextureRect(sf::IntRect(0, 311, 51, 80));//_sprite_zombie.setTextureRect(sf::IntRect(401,284.25,65.55,94.75));
            if (_energiaRegen.getElapsedTime().asSeconds() >= 5)
            {
                if (_energia <= 95)
                    _energia += 5;
                zombieIzquierda = true;
            }

            break;
        case CAMINANDO_DER: //desplazamiento a la derecha y animacion

            _xtexture = (int)_sprite_zombie.getPosition().x / 10 % 7;
            _xtexture = _xtexture * 55.28;//58
            _sprite_zombie.setTextureRect(sf::IntRect(_xtexture, 209, 55.28, 73));//_sprite_zombie.setTextureRect(sf::IntRect(_xtexture,189.50,58,94.75));
            _sprite_zombie.move(4, 0);
            zombieIzquierda = false;
            _estado = ESTADOS::QUIETO;

            break;

        case CAMINANDO_IZQ: //desplazamiento a la izquierda y animacion

            _xtexture = (int)_sprite_zombie.getPosition().x / 10 % 7;
            _xtexture = _xtexture * 56.5;//55.71
            _sprite_zombie.setTextureRect(sf::IntRect(_xtexture, 311, 56.5, 76));//_sprite_zombie.setTextureRect(sf::IntRect(_xtexture,284.25,56.55,94.75));
            _sprite_zombie.move(-4, 0);
            zombieIzquierda = true;
            _estado = ESTADOS::QUIETO_IZQ;

            break;
        case SALTANDO:

            if (zombieIzquierda == false)
            {
                _sprite_zombie.setTextureRect(sf::IntRect(113.2, 88, 54.5, 94.75));//56.55
            }
            else
            {
                _sprite_zombie.setTextureRect(sf::IntRect(113.2, 0, 55.5, 94.75));//56.55
            }

            break;
        case MURIENDO:

            break;
        case CAMINANDO_DER_SALTANDO:

            _xtexture = (int)_sprite_zombie.getPosition().x / 10 % 7;
            _xtexture = _xtexture * 56.55;
            _sprite_zombie.setTextureRect(sf::IntRect(_xtexture, 88, 56.55, 94.75));
            _sprite_zombie.move(4, 0);
            _jump_force -= 3.2;
            _sprite_zombie.move(0, -_jump_force);
            zombieIzquierda = false;
            _estado = ESTADOS::QUIETO;

            break;
        case CAMINANDO_IZQ_SALTANDO:

            _xtexture = (int)_sprite_zombie.getPosition().x / 10 % 7;
            _xtexture = _xtexture * 56.55;
            _sprite_zombie.setTextureRect(sf::IntRect(_xtexture, 0, 56.55, 94.75));
            _sprite_zombie.move(-4, 0);
            _jump_force -= 3.2;
            _sprite_zombie.move(0, -_jump_force);
            zombieIzquierda = true;
            _estado = ESTADOS::QUIETO_IZQ;

            break;
        case DISPARANDO:
            if (!yaDisparo)
            {
                if (_time_shoot.asSeconds() >= 2)
                {
                    Sound_6.audioON();
                    settimeshoot(_time_shoot);
                    float positionX = _sprite_zombie.getPosition().x;
                    float positionY = _sprite_zombie.getPosition().y;

                    if (zombieIzquierda)
                    {
                        positionX -= 30;
                        _disparo = new Disparo(TIPO::BRAIN, { positionX,positionY }, zombieIzquierda);
                        _gestor_disparos.agregarDisparo(_disparo);
                        _spawn_shoot_timer.restart();
                        settimeshoot(_time_shoot);
                        _xtexture = (int)_sprite_zombie.getPosition().x % 7;
                        _xtexture = _xtexture * 57.14;
                        _sprite_zombie.setTextureRect(sf::IntRect(_xtexture, 107, 57.14, 82));
                        _sprite_zombie.move(-4, 0);
                        zombieIzquierda = true;
                        _estado = ESTADOS::QUIETO_IZQ;
                        yaDisparo = true;
                    }
                    else
                    {
                        positionX += 30;
                        _disparo = new Disparo(TIPO::BRAIN, { positionX,positionY }, false);
                        _gestor_disparos.agregarDisparo(_disparo);
                        _spawn_shoot_timer.restart();
                        settimeshoot(_time_shoot);
                        _xtexture = (int)_sprite_zombie.getPosition().x % 7;
                        _xtexture = _xtexture * 57.14;
                        _sprite_zombie.setTextureRect(sf::IntRect(_xtexture, 107, 57.14, 82));
                        _sprite_zombie.move(4, 0);
                        zombieIzquierda = false;
                        _estado = ESTADOS::QUIETO;
                        yaDisparo = true;
                    }
                }
            }
            break;
        }
        _jump_force -= 2; //fuerza de gravedad. Se ejerse siempre
        _sprite_zombie.move(0, -_jump_force);
    }
    else
    {
        if (getOpcion() == 1)
        {
            //*************** SALLY***********************
            switch (_estado)
            {
            case NACIMIENTO:
                _sprite_zombie.setTextureRect(sf::IntRect(0, 494, 90.66, 121));
                break;
            case QUIETO:

                _sprite_zombie.setTextureRect(sf::IntRect(0, 494, 90.66, 121)); //Textura quieto.... x,y,
                if (_energiaRegen.getElapsedTime().asSeconds() >= 5)
                {
                    if (_energia <= 95)
                    {
                        _energia += 5;
                        zombieIzquierda = false;
                    }
                }

                break;
            case QUIETO_IZQ:

                _sprite_zombie.setTextureRect(sf::IntRect(0, 614, 90.66, 121));
                if (_energiaRegen.getElapsedTime().asSeconds() >= 5)
                {
                    if (_energia <= 95)
                    {
                        _energia += 5;
                        zombieIzquierda = true;
                    }
                }

                break;
            case CAMINANDO_DER: //desplazamiento a la derecha y animacion

                _xtexture = (int)_sprite_zombie.getPosition().x / 10 % 9;
                _xtexture = _xtexture * 72;
                _sprite_zombie.setTextureRect(sf::IntRect(_xtexture, 11, 72, 93));
                _sprite_zombie.move(3, 0);
                zombieIzquierda = false;
                _estado = ESTADOS::QUIETO;

                break;

            case CAMINANDO_IZQ: //desplazamiento a la izquierda y animacion

                _xtexture = (int)_sprite_zombie.getPosition().x / 10 % 9;
                _xtexture = _xtexture * 72;
                _sprite_zombie.setTextureRect(sf::IntRect(_xtexture, 129, 72, 93));
                _sprite_zombie.move(-3, 0);
                zombieIzquierda = true;
                _estado = ESTADOS::QUIETO_IZQ;

                break;
            case SALTANDO:

                if (zombieIzquierda == false)
                {
                    _sprite_zombie.setTextureRect(sf::IntRect(459, 494, 80, 102));
                }
                else
                {
                    _sprite_zombie.setTextureRect(sf::IntRect(473, 617, 80, 102));
                }

                break;
            case MURIENDO:


                break;
            case CAMINANDO_DER_SALTANDO:

                _xtexture = (int)_sprite_zombie.getPosition().x / 10 % 15;
                _xtexture = _xtexture * 91.8;
                _sprite_zombie.setTextureRect(sf::IntRect(_xtexture, 498, 91.8, 96));
                _sprite_zombie.move(4, 0);
                _jump_force -= 3.2;
                _sprite_zombie.move(0, -_jump_force);
                zombieIzquierda = false;
                _estado = ESTADOS::QUIETO;

                break;
            case CAMINANDO_IZQ_SALTANDO:

                _xtexture = (int)_sprite_zombie.getPosition().x / 10 % 15;
                _xtexture = _xtexture * 91.8;
                _sprite_zombie.setTextureRect(sf::IntRect(_xtexture, 623, 91.8, 96));
                _sprite_zombie.move(-4, 0);
                _jump_force -= 3.2;
                _sprite_zombie.move(0, -_jump_force);
                zombieIzquierda = true;
                _estado = ESTADOS::QUIETO_IZQ;

                break;
            case DISPARANDO:
                if (!yaDisparo)
                {
                    if (_time_shoot.asSeconds() >= 2)
                    {
                        Sound_6.audioON();
                        settimeshoot(_time_shoot);
                        float positionX = _sprite_zombie.getPosition().x;
                        float positionY = _sprite_zombie.getPosition().y;

                        if (zombieIzquierda)
                        {
                            positionX -= 30;
                            _disparo = new Disparo(TIPO::BRAIN, { positionX,positionY }, zombieIzquierda);
                            _gestor_disparos.agregarDisparo(_disparo);
                            _spawn_shoot_timer.restart();
                            settimeshoot(_time_shoot);
                            _xtexture = (int)_sprite_zombie.getPosition().x % 4;
                            _xtexture = _xtexture * 95.25;
                            _sprite_zombie.setTextureRect(sf::IntRect(_xtexture, 752, 95.25, 97));
                            _sprite_zombie.move(-4, 0);
                            zombieIzquierda = true;
                            _estado = ESTADOS::QUIETO_IZQ;
                            yaDisparo = true;
                        }
                        else
                        {
                            positionX += 30;
                            _disparo = new Disparo(TIPO::BRAIN, { positionX,positionY }, false);
                            _gestor_disparos.agregarDisparo(_disparo);
                            _spawn_shoot_timer.restart();
                            settimeshoot(_time_shoot);
                            _xtexture = (int)_sprite_zombie.getPosition().x % 4;
                            _xtexture = _xtexture * 95.25;
                            _sprite_zombie.setTextureRect(sf::IntRect(_xtexture, 872, 95.25, 97));
                            _sprite_zombie.move(4, 0);
                            zombieIzquierda = false;
                            _estado = ESTADOS::QUIETO;
                            yaDisparo = true;
                        }
                    }
                }
                break;
            }
            _jump_force -= 2; //fuerza de gravedad. Se ejerse siempre
            _sprite_zombie.move(0, -_jump_force);
        }
        else
        {
            if (getOpcion() == 2)
            {
                //***************IGOR***********************
                _frame += 0.2;
                if (_frame >= 4)
                {
                    _frame = 0;
                }
                switch (_estado)
                {
                case NACIMIENTO:
                    _sprite_zombie.setTextureRect(sf::IntRect(0, 0, 380, 890));
                    _sprite_zombie.setScale(0.095, 0.095);
                    _jump_force -= 1.8;

                    _sprite_zombie.move(0, -_jump_force);

                    if (_energiaRegen.getElapsedTime().asSeconds() >= 5)
                    {
                        if (_energia <= 95)
                            _energia += 5;
                        zombieIzquierda = false;
                    }

                    break;
                case QUIETO:

                    _sprite_zombie.setTextureRect(sf::IntRect(0, 0, 380, 890));
                    _sprite_zombie.setScale(0.095, 0.095);
                    _jump_force -= 1.8;

                    _sprite_zombie.move(0, -_jump_force);

                    if (_energiaRegen.getElapsedTime().asSeconds() >= 5)
                    {
                        if (_energia <= 95)
                            _energia += 5;
                        zombieIzquierda = false;
                    }

                    break;
                case QUIETO_IZQ:
                    _sprite_zombie.setTextureRect(sf::IntRect(0, 0, 380, 890));
                    _sprite_zombie.setScale(-0.095, 0.095);
                    _jump_force -= 1.8;

                    _sprite_zombie.move(0, -_jump_force);

                    if (_energiaRegen.getElapsedTime().asSeconds() >= 5)
                    {
                        if (_energia <= 95)
                            _energia += 5;
                        zombieIzquierda = true;
                    }
                    break;

                case CAMINANDO_DER: //desplazamiento a la derecha y animacion
                    _sprite_zombie.setTextureRect({ 0 + int(_frame) * 590,885,590,885 });
                    _sprite_zombie.setScale(0.095, 0.095);

                    _sprite_zombie.move(2, 0);
                    _jump_force -= 1.8;
                    _sprite_zombie.move(0, -_jump_force);
                    _estado = ESTADOS::QUIETO;
                    zombieIzquierda = false;
                    break;

                case CAMINANDO_IZQ: //desplazamiento a la izquierda y animacion


                    _sprite_zombie.move(-2, 0);
                    _sprite_zombie.setTextureRect({ 0 + int(_frame) * 590,885,590,885 });
                    _sprite_zombie.setScale(-0.095, 0.095);
                    _estado = ESTADOS::QUIETO_IZQ;
                    _jump_force -= 1.8;
                    zombieIzquierda = true;

                    _sprite_zombie.move(0, -_jump_force);


                    break;

                case SALTANDO:
                    if (zombieIzquierda)
                    {
                        _sprite_zombie.setScale(-0.095, 0.095);
                        _jump_force -= 2.8;
                        _sprite_zombie.setTextureRect({ 0 + int(_frame) * 590,885,590,885 });
                        _sprite_zombie.move(0, -_jump_force);

                    }
                    else
                    {
                        _sprite_zombie.setScale(0.095, 0.095);
                        _jump_force -= 2.8;
                        _sprite_zombie.setTextureRect({ 0 + int(_frame) * 590,885,590,885 });
                        _sprite_zombie.move(0, -_jump_force);
                    }
                    break;
                case CAMINANDO_DER_SALTANDO:
                    _sprite_zombie.move(3, 0);
                    _sprite_zombie.setScale(0.095, 0.095);
                    _jump_force -= 3.2;
                    _sprite_zombie.setTextureRect({ 0 + int(_frame) * 590,885,590,885 });
                    _sprite_zombie.move(0, -_jump_force);
                    zombieIzquierda = false;

                    break;
                case CAMINANDO_IZQ_SALTANDO:
                    _sprite_zombie.move(-3, 0);
                    _sprite_zombie.setScale(-0.095, 0.095);
                    _sprite_zombie.setTextureRect({ 0 + int(_frame) * 590,885,590,885 });
                    _jump_force -= 3.2;
                    _sprite_zombie.move(0, -_jump_force);
                    zombieIzquierda = true;
                    break;
                case MURIENDO:

                    break;
                case DISPARANDO:
                    if (!yaDisparo)
                    {

                        if (_time_shoot.asSeconds() >= 2)
                        {
                            Sound_6.audioON();
                            settimeshoot(_time_shoot);
                            float positionX = _sprite_zombie.getPosition().x;
                            float positionY = _sprite_zombie.getPosition().y;

                            if (zombieIzquierda)
                            {
                                positionX -= 30;
                                _disparo = new Disparo(TIPO::BRAIN, { positionX,positionY }, zombieIzquierda);
                                _gestor_disparos.agregarDisparo(_disparo);
                                _spawn_shoot_timer.restart();
                                settimeshoot(_time_shoot);
                                _estado = ESTADOS::QUIETO_IZQ;
                                yaDisparo = true;
                            }
                            else
                            {

                                positionX += 30;
                                _disparo = new Disparo(TIPO::BRAIN, { positionX,positionY }, false);
                                _gestor_disparos.agregarDisparo(_disparo);
                                _spawn_shoot_timer.restart();
                                settimeshoot(_time_shoot);
                                _estado = ESTADOS::QUIETO;
                                yaDisparo = true;
                            }
                        }
                    }
                    break;
                }
            }
        }
    }

}

void Zombie::update_muriendo()
{
    _vida--;
    sound_2.audioON();
    _jump_force -= 1.8;


    if (getOpcion() == 0)
    {
        if (zombieIzquierda == false)
        {
            _xtexture = (int)_sprite_zombie.getPosition().x / 12 % 5;
            _xtexture = _xtexture * 92;
            _sprite_zombie.setTextureRect(sf::IntRect(_xtexture, 558, 92, 80));
            _sprite_zombie.move(0.7, 0);
            zombieIzquierda = false;
            _estado = ESTADOS::QUIETO;


        }
        else
        {
            _xtexture = (int)_sprite_zombie.getPosition().x / 12 % 5;
            _xtexture = _xtexture * 92;
            _sprite_zombie.setTextureRect(sf::IntRect(_xtexture, 478, 92, 80));
            _sprite_zombie.move(0.7, 0);
            zombieIzquierda = true;
            _estado = ESTADOS::QUIETO_IZQ;
        }
    }
    else
    {
        if (getOpcion() == 1)
        {
            if (zombieIzquierda == false)
            {
                _xtexture = (int)_sprite_zombie.getPosition().x / 15 % 9;
                _xtexture = _xtexture * 100;//105.77
                _sprite_zombie.setTextureRect(sf::IntRect(_xtexture, 245, 100, 102));
                _sprite_zombie.move(0.7, 0);
                zombieIzquierda = false;
                _estado = ESTADOS::NACIMIENTO;
            }
            else
            {
                _xtexture = (int)_sprite_zombie.getPosition().x / 15 % 9;
                _xtexture = _xtexture * 100;
                _sprite_zombie.setTextureRect(sf::IntRect(_xtexture, 371, 100, 102));
                _sprite_zombie.move(0.7, 0);
                zombieIzquierda = true;
                _estado = ESTADOS::NACIMIENTO;
            }
        }
        else
        {

            if (getOpcion() == 2)
            {
                _sprite_zombie.setTextureRect(sf::IntRect(816, 216, 630, 675));
                _sprite_zombie.setScale(0.15, 0.15);
                _jump_force -= 3.2;
                _sprite_zombie.move(0, -_jump_force);
                _estado = ESTADOS::NACIMIENTO;
            }
        }

    }

}

void Zombie::mobility()
{
    if (_animationTimer.getElapsedTime().asSeconds() < 1.3)
    {
        _estado = ESTADOS::NACIMIENTO;
    }

    if (_estado == ESTADOS::QUIETO || _estado == ESTADOS::DISPARANDO || _estado == ESTADOS::QUIETO_IZQ)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
        {
            if (_energia >= 25)
            {
                _estado = ESTADOS::SALTANDO;
                _jump_force = 22;
                _energia -= 25;
            }

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            _estado = ESTADOS::CAMINANDO_DER;

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            _estado = ESTADOS::CAMINANDO_IZQ;

        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::X))
        {
            _estado = ESTADOS::CAMINANDO_DER_SALTANDO;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::X))
        {
            _estado = ESTADOS::CAMINANDO_IZQ_SALTANDO;

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && !isZPressed)
        {
            isZPressed = true;
            _estado = ESTADOS::DISPARANDO;
        }
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        {
            isZPressed = false;
            yaDisparo = false;

        }

    }
    //*******************Validacion para que el zombie no salga de la pantalla***************

    if (_sprite_zombie.getPosition().x < 0)
    {
        _sprite_zombie.setPosition(0, _sprite_zombie.getPosition().y);
    }
    if (_sprite_zombie.getPosition().x + _sprite_zombie.getGlobalBounds().width < 0)
    {
        _sprite_zombie.setPosition(0, _sprite_zombie.getPosition().y);
    }
    if (_sprite_zombie.getPosition().x + _sprite_zombie.getGlobalBounds().width > 1220)
    {
        _sprite_zombie.setPosition(1220 - _sprite_zombie.getGlobalBounds().width, _sprite_zombie.getPosition().y);
    }



}

sf::Sprite& Zombie::getDraw()
{
    return _sprite_zombie;
}

void Zombie::suelo(float x, float y)
{

    if (zombieIzquierda)
    {
        _estado = ESTADOS::QUIETO_IZQ;
        _jump_force = 0;
        _sprite_zombie.setPosition(x, y);
    }
    else
    {
        _estado = ESTADOS::QUIETO;
        _jump_force = 0;
        _sprite_zombie.setPosition(x, y);
    }
}

float Zombie::getjump_force()
{
    return _jump_force;
}

sf::FloatRect Zombie::getBounds()const
{
    return _sprite_zombie.getGlobalBounds();
}

float Zombie::gettimeshoot()
{
    return _time_shoot.asSeconds();
}

void Zombie::settimeshoot(sf::Time time)
{
    _time_shoot = time;

}
