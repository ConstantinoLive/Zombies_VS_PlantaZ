#pragma once
#include <iostream>

#include "Partida.h"
#define _CRT_SECURE_NO_WARNINGS

class Ranking
{
public:
    Ranking();
    virtual ~Ranking();

    void setRanking();
    Partida* getRanking();

private:
    Partida _partidas[10];
};

