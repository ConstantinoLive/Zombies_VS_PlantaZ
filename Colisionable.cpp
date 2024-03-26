#include "Colisionable.h"
#include<SFML/Graphics.hpp>


bool Colisionable::isCollision(Colisionable& obj) const
{
    return getBounds().intersects(obj.getBounds());
}
