#include "Audio.h"
Audio::Audio(int opc)
{
    _opcion_musica = opc;

    if (_opcion_musica == 1)
    {
        //Musica de fondo
        if (!musica.openFromFile("Audio/ArcLight-_192-Kbps_.mp3"))
        {
            //std::cout << "Error al cargar sonido" << std::endl;
            return;
        }
    }
    else
    {
        //Muerte del zombie
        if (_opcion_musica == 2)
        {
            if (!buffer1.loadFromFile("Audio/Muerte_zombie.mp3"))
            {
                //std::cout << "Error al cargar sonido" << std::endl;
                return;
            }
            _muerte_zombie.setBuffer(buffer1);
        }
        else
        {
            //Menu
            if (_opcion_musica == 3)
            {
                if (!_audio_menu.openFromFile("Audio/Audio_menu.mp3"))
                {
                   // std::cout << "Error al cargar sonido" << std::endl;
                    return;
                }
            }
            else
            {
                //agarrar premio
                if (_opcion_musica == 4)
                {
                    if (!buffer3.loadFromFile("Audio/Decline.mp3"))
                    {
                       // std::cout << "Error al cargar sonido" << std::endl;
                        return;
                    }
                    _audio_prize.setBuffer(buffer3);
                }
                else
                {
                    //Golpe al zombie
                    if (_opcion_musica == 5)
                    {
                        if (!buffer4.loadFromFile("Audio/Golpe_al_zombie.mp3"))
                        {
                            //std::cout << "Error al cargar sonido" << std::endl;
                            return;
                        }
                        _golpe_al_zombie.setBuffer(buffer4);
                    }
                    else
                    {
                        //Disparo zombie
                        if (_opcion_musica == 6)
                        {
                            if (!buffer5.loadFromFile("Audio/shade10.mp3"))
                            {
                                //std::cout << "Error al cargar sonido" << std::endl;
                                return;
                            }
                            _disparo_zombie.setBuffer(buffer5);
                        }
                        else
                        {
                            //Muerte planta
                            if (_opcion_musica == 7)
                            {
                                if (!buffer6.loadFromFile("Audio/slime6.mp3"))
                                {
                                    //std::cout << "Error al cargar sonido" << std::endl;
                                    return;
                                }
                                _muerte_planta.setBuffer(buffer6);
                            }
                            else
                            {
                                //Disparo planta
                                if (_opcion_musica == 8)
                                {
                                    if (!buffer7.loadFromFile("Audio/random4.mp3"))
                                    {
                                        //std::cout << "Error al cargar sonido" << std::endl;
                                        return;
                                    }
                                    _disparo_planta.setBuffer(buffer7);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

Audio::~Audio()
{
    //dtor
}

void Audio::audioON()
{
    if (_opcion_musica == 1)
    {
        //Musica de fondo
        musica.play();
    }
    else
    {
        //Muerte del zombie
        if (_opcion_musica == 2)
        {
            _muerte_zombie.play();
        }
        else
        {
            //Menu
            if (_opcion_musica == 3)
            {
                _audio_menu.play();
            }
            else
            {
                if (_opcion_musica == 4)
                {
                    _audio_prize.play();
                }
                else
                {
                    if (_opcion_musica == 5)
                    {
                        _golpe_al_zombie.play();
                    }
                    else
                    {
                        if (_opcion_musica == 6)
                        {
                            _disparo_zombie.play();
                        }
                        else
                        {
                            if (_opcion_musica == 7)
                            {
                                _muerte_planta.play();
                            }
                            else
                            {
                                if (_opcion_musica == 8)
                                {
                                    _disparo_planta.play();
                                }
                            }
                        }
                    }
                }
            }
        }
    }

}

void Audio::audioOFF()
{
    if (_opcion_musica == 1)
    {
        //Musica de fondo
        musica.stop();
    }
    else
    {
        //Muerte del zombie
        if (_opcion_musica == 2)
        {
            _muerte_zombie.stop();
        }

        else
        {
            //Menu
            if (_opcion_musica == 3)
            {
                _audio_menu.stop();
            }
            else
            {
                if (_opcion_musica == 4)
                {
                    _audio_prize.stop();
                }
                else
                {
                    if (_opcion_musica == 5)
                    {
                        _golpe_al_zombie.stop();
                    }
                    else
                    {
                        if (_opcion_musica == 6)
                        {
                            _disparo_zombie.stop();
                        }
                        else
                        {
                            if (_opcion_musica == 7)
                            {
                                _muerte_planta.stop();
                            }
                            else
                            {
                                if (_opcion_musica == 8)
                                {
                                    _disparo_planta.stop();
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
