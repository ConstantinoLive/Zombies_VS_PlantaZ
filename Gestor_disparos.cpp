#include "Gestor_disparos.h"
#include<vector>

Gestor_disparos::Gestor_disparos()
{
    //ctor
}

Gestor_disparos::~Gestor_disparos()
{
    //dtor
}


void Gestor_disparos::agregarDisparo(Disparo* disp)
{
    _array_disparos.push_back(disp);

}
