#include "Game_play.h"


Game_play::Game_play(Player& player, int numZombie, sf::RenderWindow& window) : Sound_4(4), Sound_5(5), Sound_7(7)
{
    _estado = ESTADOS_GAME_PLAY::ACTION;

    //1er nivel plats

    Plats[0].getDraw().setPosition(250, 400);
    Plats[1].getDraw().setPosition(310, 400);
    Plats[2].getDraw().setPosition(500, 400);
    Plats[3].getDraw().setPosition(560, 400);
    Plats[4].getDraw().setPosition(750, 400);
    Plats[5].getDraw().setPosition(810, 400);
    Plats[6].getDraw().setPosition(870, 400);

    //2do nivel plats


    Plats[7].getDraw().setPosition(70, 270);    //1era
    Plats[8].getDraw().setPosition(240, 270);    //2da
    Plats[9].getDraw().setPosition(300, 270);    //2da
    Plats[10].getDraw().setPosition(470, 270);   //3ra
    Plats[11].getDraw().setPosition(530, 270);   //3ra
    Plats[12].getDraw().setPosition(700, 270);   //3ra
    Plats[13].getDraw().setPosition(870, 270);   //4ta
    Plats[14].getDraw().setPosition(1040, 270);  //5ta
    Plats[15].getDraw().setPosition(1100, 270);  //5ta
    Plats[16].getDraw().setPosition(1160, 270);  //5ta


    //3er nivel plats

    Plats[17].getDraw().setPosition(0, 140);     //1era
    Plats[18].getDraw().setPosition(60, 140);    //1era
    Plats[19].getDraw().setPosition(120, 140);   //1era
    Plats[20].getDraw().setPosition(300, 140);   //2da
    Plats[21].getDraw().setPosition(360, 140);   //2da
    Plats[22].getDraw().setPosition(420, 140);   //2da
    Plats[23].getDraw().setPosition(700, 140);   //3ra
    Plats[24].getDraw().setPosition(760, 140);   //3ra
    Plats[25].getDraw().setPosition(820, 140);   //3ra
    Plats[26].getDraw().setPosition(880, 140);   //3ra
    Plats[27].getDraw().setPosition(1040, 140);  //4ta
    Plats[28].getDraw().setPosition(1100, 140);  //4ta
    Plats[29].getDraw().setPosition(1160, 140);  //4ta


    _prize_timer.restart(); //inicializo el timer de premio
    _prize_generated = false;

    //inicio los valores aleatorios del generador y mezclo el vector de posiciones
    std::mt19937 g(rand());

    std::shuffle(_position.begin(), _position.end(), g);


    _plant_spawn_timer.restart();
    numeroZombie = numZombie;
    Z1 = new Zombie(numZombie, _shoot_manager);
    _namePlayer = player.getNombre();
    _is_dead = false;


    /*****************NOMBRE DE JUGADOR   **************/

    if (!_fontPlayer.loadFromFile("font/BITWA___.ttf"))
    {
       // std::cout << "Error al cargar texto" << std::endl;
    }
    //std::cout << _namePlayer << std::endl;
    _textPlayer.setFont(_fontPlayer);
    _textPlayer.setString(_namePlayer);
    _textPlayer.setFillColor(sf::Color(255,0,11));
    _textPlayer.setPosition(400, 710);
    /*****************PUNTAJE**************************/
    puntaje = 0;
    if (!_fontPuntaje.loadFromFile("font/BITWA___.ttf"))
    {
        //std::cout << "Error al cargar texto" << std::endl;
    }
    //std::cout << puntaje << std::endl;
    _textPuntaje.setFont(_fontPuntaje);
    _textPuntaje.setString(std::to_string(puntaje));
    _textPuntaje.setFillColor(sf::Color(255, 0, 11));
    _textPuntaje.setPosition(500, 740);

    /*********************Vidas*****************/

    _textvidas.setFont(_fontPlayer);
    _textvidas.setString("Vidas");
    _textvidas.setFillColor(sf::Color(255, 0, 11));
    _textvidas.setPosition(930, 710);
    /*****************vidas**************************/

    _cantvidas.setFont(_fontPuntaje);
    _cantvidas.setFillColor(sf::Color(255, 0, 11));
    _cantvidas.setPosition(940, 740);


}

Game_play::~Game_play()
{
    //dtor
}

void Game_play::draw(sf::RenderWindow& window)
{
    ///Dibujo Zombie///
    window.draw(Z1->getDraw());

    ///Dibujo Plantas///
    for (auto p : _plant_manager._array_plantas)
    {
        window.draw(*p);
    }


    ///Dibujo Disparos///
    for (auto disparo : _shoot_manager._array_disparos)
    {
        window.draw(*disparo);
    }
    ///Dibujo Plataformas///
    for (Plataforma& Plat_1 : Plats)
    {
        window.draw(Plat_1.getDraw());
    }
    ///Dibujo Premio///
    if (_prize_generated)
    {
        window.draw(*_prize);
    }


    ///Dibujo elementos varios///
    window.draw(_life_bar);
    window.draw(_energy_bar);
    window.draw(_text_pause);

    window.draw(_textPlayer);
    window.draw(_textPuntaje);
    window.draw(_textvidas);
    window.draw(_cantvidas);
}


void Game_play::cmd()
{

    if (_estado == ESTADOS_GAME_PLAY::ACTION)//SE EJECUTA SI EL JUEGO NO ESTÁ EN PAUSA
    {
        Z1->mobility();
        //...........comandos para poner en pausa el juego......

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        {
            _estado = ESTADOS_GAME_PLAY::PAUSE;

            if (!_font_pause.loadFromFile("font/Lethal Slime.ttf"))
            {
               // std::cout << "Error al cargar texto" << std::endl;
            }
            //std::cout << "Pausa" << std::endl;
            _text_pause.setFont(_font_pause);
            _text_pause.setString("PAUSA");
            _text_pause.setFillColor(sf::Color(255, 0, 11));
            _text_pause.setPosition(488, 228.50);

        }
    }
    else
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        {
            _estado = ESTADOS_GAME_PLAY::ACTION;
            _text_pause.setString("             ");
            _text_pause.setPosition(480, 228.50);
        }
    }
}
/////////////////////////////
void Game_play::check_collision_platform()
{

    for (Plataforma& Plat_1 : Plats)
    {
        if (Z1->getDraw().getGlobalBounds().intersects(Plat_1.getDraw().getGlobalBounds()) && Z1->getjump_force() < 0)
        {
            if (numeroZombie == 0 || numeroZombie == 1)
            {
                Z1->suelo(Z1->getDraw().getPosition().x, Plat_1.getDraw().getGlobalBounds().top - 70); //80 es la altura del Sprite
            }
            else if (numeroZombie == 2)
            {
                Z1->suelo(Z1->getDraw().getPosition().x, Plat_1.getDraw().getGlobalBounds().top - 70);
            }
        }

    }
}


void Game_play::updateShoot(sf::RenderTarget& window)
{

    for (auto it = _shoot_manager._array_disparos.begin(); it != _shoot_manager._array_disparos.end();)
    {
        Disparo* disp = *it;
        tipoDisparo = disp->getTipo();      //con esto le asignamos el tipo de disparo a la variable para poder validar las colisiones
        disp->update();


        if (Z1->isCollision(*disp) && tipoDisparo != TIPO::BRAIN || disp->checkWindowBounds(window))
        {
            if (Z1->isCollision(*disp) && tipoDisparo != TIPO::BRAIN)
            {
                _life_bar.setLifePoints(_life_bar.getLifePoints() - 1);

                Sound_5.audioON();
            }

            delete disp;

            it = _shoot_manager._array_disparos.erase(it);
        }
        else
        {
            ++it;
        }


    }
    ///Verifico si el tiro del zombie choca una planta, es necesario recorrer todas las plantas...
    for (auto it = _plant_manager._array_plantas.begin(); it != _plant_manager._array_plantas.end();)
    {
        Planta* planta = *it;
        planta->update();
        colisionPlanta = false;
        for (auto itDisparo = _shoot_manager._array_disparos.begin(); itDisparo != _shoot_manager._array_disparos.end();)
        {
            Disparo* disp = *itDisparo;
            disp->update();

            tipoDisparo = disp->getTipo();
            if (disp->isCollision(*planta) && tipoDisparo == TIPO::BRAIN)
            {
                colisionPlanta = true;
                puntaje += 45;
                itDisparo = _shoot_manager._array_disparos.erase(itDisparo);
                delete disp;
            }
            else
            {
                itDisparo++;
            }
        }
        if (colisionPlanta)
        {
            Sound_7.audioON();
            enemigos_eliminados++;
            it = _plant_manager._array_plantas.erase(it);
            delete planta;
        }
        else
        {
            it++;
        }
    }
}


///////////////////////////////////////

void Game_play::updatePrize()
{

    if (!_prize_generated)   //pregunto y entro si no hay premio generado
    {
        if (_prize_timer.getElapsedTime().asSeconds() >= 5) //pregunto si llego al tiempo de spawn de premio
        {
            _prize = new Prize((sf::Vector2f)getRandomPosition());     //Prueba posicion!!!
            _prize_generated = true;
            _prize_timer.restart();
        }
    }
    else                    //se genero un premio
    {
        if (Z1->isCollision(*_prize) || _prize_timer.getElapsedTime().asSeconds() >= 10)
        {
            if (Z1->isCollision(*_prize))
            {
                _life_bar.setLifePoints(_life_bar.getLifePoints() + 1);
                puntaje += 500;
                Sound_4.audioON();
            }
            _prize_generated = false;
            _prize_timer.restart();
            delete _prize;
        }
    }
}
//////////////////////////////////

void Game_play::update(sf::RenderTarget& window)
{
    if (_game_over == false)
    {
        if (_estado == ESTADOS_GAME_PLAY::ACTION) //SE EJECUTA SI EL JUEGO NO ESTÁ EN PAUSA
        {

            if (_is_dead == false && _dead.getElapsedTime().asSeconds() > 0.01)
            {
                if (_life_bar.getLifePoints() <= 5 && _life_bar.getLifePoints() >= 1)
                {

                    Z1->update();


                }
                else
                {
                    if (_is_dead == false)
                    {
                        _dead.restart();
                    }
                    if (_life_bar.getLifePoints() == 0 && _dead.getElapsedTime().asSeconds() < 1.5)
                    {

                        Z1->update_muriendo();
                        _is_dead = true;

                    }

                    if (_is_dead == true && _dead.getElapsedTime().asSeconds() > 1.5)
                    {

                        _dead.restart();

                    }
                }

            }
            if (_is_dead == true && _life_bar.getLifePoints() == 0 && _dead.getElapsedTime().asSeconds() > 1.5)
            {
                _is_dead = false;
                _life_bar.setLifePoints(5);
                _dead.restart();

            }
            if (Z1->getvida() >= 1)
            {
                vidas = Z1->getvida();
                _game_over = false;
                _winner = true;
            }
            else
            {
                if (Z1->getvida() < 1)
                {
                    _game_over = true;
                    _winner = false;
                }

            }

            //////////////////////////


            if (Z1->gettimeshoot() > 2.0)
            {
                _energy_bar.setEnergyPoints(5);

            }
            else
            {
                if (Z1->gettimeshoot() >= 0.0 && Z1->gettimeshoot() < 0.4)
                {
                    _energy_bar.setEnergyPoints(0);
                }
                else
                {
                    if (Z1->gettimeshoot() > 0.4 && Z1->gettimeshoot() < 0.8)
                    {
                        _energy_bar.setEnergyPoints(1);
                    }
                    else
                    {
                        if (Z1->gettimeshoot() > 0.8 && Z1->gettimeshoot() < 1.2)
                        {
                            _energy_bar.setEnergyPoints(2);
                        }
                        else
                        {
                            if (Z1->gettimeshoot() > 1.2 && Z1->gettimeshoot() < 1.6)
                            {
                                _energy_bar.setEnergyPoints(3);
                            }
                            else
                            {
                                if (Z1->gettimeshoot() > 1.6 && Z1->gettimeshoot() < 2.0)
                                {
                                    _energy_bar.setEnergyPoints(4);
                                }
                            }
                        }
                    }
                }
            }

            updatePrize();
            _life_bar.update();
            _energy_bar.update();
            updatePlants2();
            updateShoot(window);


            _textPuntaje.setString(std::to_string(puntaje));
            _cantvidas.setString(std::to_string(vidas));

            if (Z1->getDraw().getPosition().y > 498) //485 Suelo... limite de caida
            {
                Z1->suelo(Z1->getDraw().getPosition().x, 498);
            }

            check_collision_platform();
        }
    }
    else
    {
        std::cout << "GAME OVER!!!" << std::endl;
    }
}

void Game_play::updatePlants2()
{

    updatePlantGeneration();
    updatePlantDeletion();
    updatePlantsSelfMovement();
}

void Game_play::updatePlantGeneration()
{
    ///GENERACION DE PLANTAS

    _random_type = TIPO(rand() % 4);   //Genero un tipo aleatorio, casteo a TIPO
    bool look = rand() % 2;

    if (_plant_manager._array_plantas.size() <= 6 && enemigos <= 20)   //define la cantidad de plantas en pantalla y condicion de winner
    {

        if (_plant_spawn_timer.getElapsedTime().asSeconds() >= 1.5)    //spawneo cada 3 seg
        {
            _plant_manager.agregarPlanta(new Planta(_random_type, getRandomPosition(), look, _shoot_manager));
            enemigos++;
            _plant_spawn_timer.restart();

        }

    }

}

void Game_play::updatePlantDeletion()
{
    ///DELETEO DE PLANTAS
    ////recorro el array de plantas del gestor y deleteo plantas si corresponde////
    for (auto it = _plant_manager._array_plantas.begin(); it != _plant_manager._array_plantas.end();)   //inicio el iterador IT en el principio del array y recorro hasta el final de array
    {
        Planta* planta = *it;       //defino el puntero a PLANTA llamado planta y apunta igual que IT, sera el objeto a actualizar y/o borrar
        planta->update();
        //chequeo colision zombie-planta
        if (Z1->isCollision(*planta))
        {
            _life_bar.setLifePoints(_life_bar.getLifePoints() - 1);
            enemigos_eliminados++;
            Sound_5.audioON();

            delete planta;                                  //libera memoria del objeto planta, pero ojo! el puntero planta aun tiene la direccion
            //de memoria del objeto eliminado, es decir, el objeto esta en la lista pero no es valido.
            _plant_spawn_timer.restart();                   //Tanto para la generacion como para el deleteo de plantas, reseteo el timer
            it = _plant_manager._array_plantas.erase(it);    //con esto elimino completamente de la lista y el iterador IT queda apuntando al siguiente elemento
        }
        else
        {
            ++it;                           //Si no se elimina el enemigo, avanza al siguiente elemento
        }
    }
}

void Game_play::updatePlantsSelfMovement()
{

    sf::FloatRect bounds = Z1->getDraw().getGlobalBounds();
    Plataforma plataformita;
    for (Planta* plantita : _plant_manager._array_plantas)  //recorro todas las plantas
    {


        plataformita = findPlatform(*plantita);
        if (plantita->getPosition().y == 500 && plantita->getPosition().x > bounds.left)   //pregunto si esta en el suelo no se mueve y ya
        {
            plantita->setCanMove(false);
            plantita->setLookingLeft(true);
        }
        else
        {
            if (plantita->getPosition().y == 500 && plantita->getPosition().x < bounds.left)   //pregunto si esta en el suelo no se mueve y ya
            {
                plantita->setCanMove(false);
                plantita->setLookingLeft(false);
            }
            else
            {
                if (!plantita->isCollision(plataformita))                     //pregunto por si deja de chocar con la plataforma
                {
                    plantita->setLookingLeft(!plantita->isLookingLeft());     //invierto el sentido
                }
            }

        }
        if (plantita->getPosition().x > bounds.left && bounds.left + 150 > plantita->getPosition().x && plantita->getPosition().y<bounds.top + 20 && plantita->getPosition().y>bounds.top - 20 && plantita->getPosition().y != 500)   //pregunto si esta en el suelo no se mueve y ya
        {
            plantita->setCanMove(false);
            plantita->setLookingLeft(true);

            plantita->updateShooting();

        }
        else
        {
            if (plantita->getPosition().x < bounds.left && bounds.left - 150 < plantita->getPosition().x && plantita->getPosition().y<bounds.top + 20 && plantita->getPosition().y>bounds.top - 20 && plantita->getPosition().y != 500)   //pregunto si esta en el suelo no se mueve y ya
            {
                plantita->setCanMove(false);
                plantita->setLookingLeft(false);
                plantita->updateShooting();

            }
            else
            {
                if (plantita->getPosition().y != 500)
                {
                    plantita->setCanMove(true);
                }

            }
        }
    }
}


Plataforma Game_play::findPlatform(Planta plantita)
{
    for (Plataforma& plat : Plats)
    {
        sf::FloatRect bounds = plat.getDraw().getGlobalBounds();

        if (plantita.getPosition().x >= bounds.left && plantita.getPosition().x <= bounds.left + bounds.width &&
            plantita.isCollision(plat))
        {
            return plat;
        }
    }
    return Plats[0];
}



sf::Vector2i Game_play::getRandomPosition()
{
    sf::Vector2i pos = _position.back();             //elemento que me interesa, el ultimo elemento del vector

    _position.insert(_position.begin(), pos);         //pongo al principio del vector el elemento que me interesa
    _position.pop_back();                            //saco el ultimo elemento del array



    return pos;
}

void Game_play::setNombrePlayer(std::string nombre)
{
    _namePlayer = nombre;
}
bool Game_play::getWinner()
{
    return _winner;
}
