#pragma once
#include <vector>

#include "DISPARO.h"

class Gestor_disparos
{
public:
    Gestor_disparos();
    virtual ~Gestor_disparos();

    void agregarDisparo(Disparo* disp);



    //esto deberia de ser privado y tener un getter porque para el setter ya se hizo el agregar disparo
    std::vector<Disparo*> _array_disparos;

};


