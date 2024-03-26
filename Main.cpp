#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include<cstdlib>       //para rand y srand
#include <ctime>        //para time

#include "Menu.h"
#include "GAME_PLAY.h"
#include "Juego2.h"
#include "Audio.h"


int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));  //inicio semilla para rand

    Audio Sound_3c(3);
    Juego2 zombies_vs_plantas;
   

    Sound_3c.audioON();

    zombies_vs_plantas.run();
    return 0;
}
