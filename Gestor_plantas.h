#pragma once
#include <vector>

#include "PLANTA.h"

class Gestor_plantas
{
public:
    Gestor_plantas();
    virtual ~Gestor_plantas();

    void agregarPlanta(Planta* p);

    std::vector<Planta*>  _array_plantas;

};
