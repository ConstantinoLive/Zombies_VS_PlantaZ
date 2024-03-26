#pragma once
//#include <iostream>

#include <SFML/Audio.hpp>

class Audio
{
public:
    Audio(int opc);
    virtual ~Audio();
    void audioON();
    void audioOFF();

protected:

private:
    int _opcion_musica;
    sf::Music musica;
    sf::SoundBuffer buffer1;
    sf::SoundBuffer buffer2;
    sf::SoundBuffer buffer3;
    sf::SoundBuffer buffer4;
    sf::SoundBuffer buffer5;
    sf::SoundBuffer buffer6;
    sf::SoundBuffer buffer7;
    sf::Sound _muerte_zombie;
    sf::Sound _muerte_planta;
    sf::Sound _audio_prize;
    sf::Sound _golpe_al_zombie;
    sf::Sound _disparo_zombie;
    sf::Sound _disparo_planta;
    sf::Music _audio_menu;


};

