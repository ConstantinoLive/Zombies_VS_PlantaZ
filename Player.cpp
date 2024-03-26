#include "Player.h"
#include <iostream>

Player::Player() {
    _puntaje = 0;
    _nombre = "Player";
}

Player::Player(int puntaje, std::string nombre) {
    _puntaje = 0;
    _nombre = nombre;
}

void Player::setPuntaje(int puntaje) {
    _puntaje = puntaje;
}

void Player::setNombre(std::string nombre) {

    _nombre = nombre;

}
int Player::getPuntaje() {
    return _puntaje;

}
std::string Player::getNombre() {
    return _nombre;

}

std::string Player::ingresarNombre()
{
    sf::RenderWindow ventanita(sf::VideoMode(300, 50), "", sf::Style::None);
    ventanita.setFramerateLimit(60);
    ventanita.setPosition(sf::Vector2i(1100, 630));

    sf::Font font;
    font.loadFromFile("Font/TT Interphases Pro Trial Black.ttf");

    sf::Text texto;
    texto.setFont(font);

    texto.setCharacterSize(40);
    texto.setFillColor(sf::Color(255,255,255));

    std::string entrada = "";

    while (ventanita.isOpen()) {
        sf::Event event;
        while (ventanita.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                ventanita.close();
            }
            else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode >= 32 && event.text.unicode <= 126 && entrada.size() <= 10) {
                    entrada += static_cast<char>(event.text.unicode);
                    texto.setString(entrada);
                }
                else if (event.text.unicode == 8 && !entrada.empty()) {
                    entrada.pop_back();
                    texto.setString(entrada);
                }
            }
            else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter) {
                ventanita.close();
            }
        }

        ventanita.clear();
        ventanita.draw(texto);
        ventanita.display();
    }

    return entrada;
}

