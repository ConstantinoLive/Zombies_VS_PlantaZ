#include "Gestor_plantas.h"
Gestor_plantas::Gestor_plantas()
{
    //ctor
}

Gestor_plantas::~Gestor_plantas()
{
    //dtor
}

void Gestor_plantas::agregarPlanta(Planta* p)
{
    _array_plantas.push_back(p);
}