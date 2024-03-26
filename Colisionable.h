#pragma once
#include<SFML/Graphics.hpp>

class Colisionable     //Clase abstracta para ser heredada por players,enemies,shoot,platform,etc
{
public:
    virtual sf::FloatRect getBounds()const = 0;     //este metodo devuelve un Float Rect, es virtual porque la voy a definir en cada clase hija
    //es constante porque no modifica el objeto, const=0 obliga a definirla luego
    bool isCollision(Colisionable& obj) const;     //devuelve true si el objeto que la llama collisiona con COL un objeto collisionable

};
