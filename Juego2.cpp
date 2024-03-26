#include "Juego2.h"
Juego2::Juego2()
{
    _menu_ppal = new Menu(TIPO_MENU::PRINCIPAL);
    _menu_ranking = new Menu(TIPO_MENU::RANKING);
    _menu_reglamento = new Menu(TIPO_MENU::REGLAMENTO);
    _menu_creditos = new Menu(TIPO_MENU::CREDITOS);
    _menu_secundario = new Menu(TIPO_MENU::SECUNDARIO);
    _menu_seleccion_zombie = new Menu(TIPO_MENU::SELECCION_ZOMBIE);
    _menu_game_over = new Menu(TIPO_MENU::GAME_OVER);
    _menu_winner = new Menu(TIPO_MENU::WINNER);

    _player = new Player();

    _tipo_menu = TIPO_MENU::PRINCIPAL;
}

Juego2::~Juego2()
{
    delete _menu_ppal;
    delete _menu_ranking;
    delete _menu_reglamento;
    delete _menu_creditos;
    delete _menu_secundario;
    delete _menu_seleccion_zombie;
    delete _menu_game_over;
    delete _menu_winner;
}

int Juego2::run()      ///Estructura principal de la aplicacion
{
    sf::RenderWindow window(sf::VideoMode(1220, 800), "Zombies vs PlantaZ");
    window.setFramerateLimit(60);

    while (true)
    {
        switch (_tipo_menu)
        {
        case TIPO_MENU::PRINCIPAL:
            _tipo_menu = menuPpal(window);
            break;
        case TIPO_MENU::RANKING:
            _tipo_menu = ranking(window);
            break;
        case TIPO_MENU::REGLAMENTO:
            _tipo_menu = reglamento(window);
            break;
        case TIPO_MENU::CREDITOS:
            _tipo_menu = creditos(window);
            break;
        case TIPO_MENU::EXIT:
            window.close();
            return 0;
            break;
        case TIPO_MENU::SECUNDARIO:             ///aca esta el juego, o sea gameplay
            _tipo_menu = menuSecundario(window);
            break;
        case TIPO_MENU::SELECCION_ZOMBIE:
            _tipo_menu = seleccionZombie(window);
            break;
        case TIPO_MENU::WINNER:
            _tipo_menu = winner(window);
            break;
        case TIPO_MENU::GAME_OVER:
            _tipo_menu = gameOver(window);
            break;
        }
    }
}

TIPO_MENU Juego2::menuPpal(sf::RenderWindow& window)
{
    TIPO_MENU t = TIPO_MENU::PRINCIPAL;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyReleased:
                switch (event.key.code)     ///Pregunto que tecla fue, arriba/abajo/enter
                {
                case sf::Keyboard::Up:
                    _menu_ppal->up();
                    break;
                case sf::Keyboard::Down:
                    _menu_ppal->down();
                    break;
                case sf::Keyboard::Return:
                    switch (_menu_ppal->getSelectedItem())  ///por aca las opciones de menu ppal
                    {
                    case INICIO:                            ///seria el 0, corresponde a inicio
                        //std::cout << "INICIO" << std::endl;
                        t = TIPO_MENU::SECUNDARIO;
                        break;
                    case RANK:
                        //std::cout << "RANKING" << std::endl;
                        t = TIPO_MENU::RANKING;
                        break;
                    case REGLA:
                        //std::cout << "REGLAMENTO" << std::endl;
                        t = TIPO_MENU::REGLAMENTO;
                        break;
                    case CRED:
                       // std::cout << "CRÉDITOs" << std::endl;
                        t = TIPO_MENU::CREDITOS;
                        break;
                    case SALIR:
                        //std::cout << "SALIR" << std::endl;
                        t = TIPO_MENU::EXIT;
                        break;
                    }
                    break;
                }
                break;
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }


        window.clear(sf::Color(0, 0, 0));
        window.draw(*_menu_ppal);   ///dibujo el contendido , que es un menu dibujable :)
        showStart(window);
        window.display();
        return t;
    }
}

TIPO_MENU Juego2::ranking(sf::RenderWindow& window)
{
    TIPO_MENU t = TIPO_MENU::RANKING;

    Partida partida;

    Ranking ranking;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyReleased:
                switch (event.key.code)     ///Pregunto que tecla fue, arriba/abajo/enter
                {
                case sf::Keyboard::Up:
                    _menu_ranking->up();
                    break;
                case sf::Keyboard::Down:
                    _menu_ranking->down();
                    break;
                case sf::Keyboard::Return:
                    switch (_menu_ranking->getSelectedItem())   ///por aca las opciones en el menu RANKING
                    {
                    case VOLVER:                            ///seria el 0, corresponde a VOLVER
                       // std::cout << "VOLVER" << std::endl;
                        t = TIPO_MENU::PRINCIPAL;
                        break;
                    case SALIR_RyC:
                       // std::cout << "SALIR" << std::endl;
                        t = TIPO_MENU::EXIT;
                        break;
                    }
                    break;
                }
                break;
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }

        ///ACA VA EL RANKING!

        if (partida.contarPartidas() > 0)
        {
            ranking.setRanking();

            window.clear(sf::Color(0,0,0));
            window.draw(*_menu_ranking);   ///dibujo el contendido , que es un menu dibujable :)
            showRanking(window, ranking);
        }
        else
        {
            window.clear(sf::Color(0,0,0));
            window.draw(*_menu_ranking);   ///dibujo el contendido , que es un menu dibujable :)
        }


        window.display();

        return t;
    }
}

TIPO_MENU Juego2::creditos(sf::RenderWindow& window)
{
    TIPO_MENU t = TIPO_MENU::CREDITOS;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyReleased:
                switch (event.key.code)     ///Pregunto que tecla fue, arriba/abajo/enter
                {
                case sf::Keyboard::Up:
                    _menu_creditos->up();
                    break;
                case sf::Keyboard::Down:
                    _menu_creditos->down();
                    break;
                case sf::Keyboard::Return:
                    switch (_menu_creditos->getSelectedItem())   ///por aca las opciones en el menu CREDITOS
                    {
                    case VOLVER:                            ///seria el 0, corresponde a VOLVER
                        //std::cout << "VOLVER" << std::endl;
                        t = TIPO_MENU::PRINCIPAL;
                        break;
                    case SALIR_RyC:
                        //std::cout << "SALIR" << std::endl;
                        t = TIPO_MENU::EXIT;
                        break;
                    }
                    break;
                }
                break;
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(0,0,0));
        window.draw(*_menu_creditos);   ///dibujo el contendido , que es un menu dibujable :)
        showBestTeam(window);
        window.display();
        return t;
    }
}

TIPO_MENU Juego2::reglamento(sf::RenderWindow& window)
{
    TIPO_MENU t = TIPO_MENU::REGLAMENTO;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyReleased:
                switch (event.key.code)     ///Pregunto que tecla fue, arriba/abajo/enter
                {
                case sf::Keyboard::Up:
                    _menu_reglamento->up();
                    break;
                case sf::Keyboard::Down:
                    _menu_reglamento->down();
                    break;
                case sf::Keyboard::Return:
                    switch (_menu_reglamento->getSelectedItem())   ///por aca las opciones en el menu CREDITOS
                    {
                    case VOLVER:                            ///seria el 0, corresponde a VOLVER
                       // std::cout << "VOLVER" << std::endl;
                        t = TIPO_MENU::PRINCIPAL;
                        break;
                    case SALIR_RyC:
                       // std::cout << "SALIR" << std::endl;
                        t = TIPO_MENU::EXIT;
                        break;
                    }
                    break;
                }
                break;
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }


        window.clear(sf::Color(0,0,0));
        window.draw(*_menu_reglamento);   ///dibujo el contendido , que es un menu dibujable :)
        showRule(window);
        window.display();
        return t;
    }
}

TIPO_MENU Juego2::menuSecundario(sf::RenderWindow& window)
{
    TIPO_MENU t = TIPO_MENU::SECUNDARIO;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyReleased:
                switch (event.key.code)     ///Pregunto que tecla fue, arriba/abajo/enter
                {
                case sf::Keyboard::Up:
                    _menu_secundario->up();
                    break;
                case sf::Keyboard::Down:
                    _menu_secundario->down();
                    break;
                case sf::Keyboard::Return:
                    switch (_menu_secundario->getSelectedItem())  ///por aca las opciones de menu secundario
                    {
                    case JUGAR:                            ///seria el 0, corresponde a jugar
                       // std::cout << "JUGAR" << std::endl;
                        t = TIPO_MENU::SELECCION_ZOMBIE;
                        break;
                    case INGRESAR_NOMBRE:
                      //  std::cout << "INGRESAR NOMBRE" << std::endl;
                        _player->setNombre(_player->ingresarNombre());
                        break;
                    case VOLVER_PPAL:
                       // std::cout << "VOLVER PRINCIPAL" << std::endl;
                        t = TIPO_MENU::PRINCIPAL;
                        break;
                    }
                    break;
                }
                break;
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }


        window.clear(sf::Color(0,0,0));
        window.draw(*_menu_secundario);   ///dibujo el contendido , que es un menu dibujable :)
        window.display();
        return t;
    }
}

TIPO_MENU Juego2::seleccionZombie(sf::RenderWindow& window)
{
    TIPO_MENU t = TIPO_MENU::SELECCION_ZOMBIE;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyReleased:
                switch (event.key.code)     ///Pregunto que tecla fue, arriba/abajo/enter
                {
                case sf::Keyboard::Up:
                    _menu_seleccion_zombie->up();
                    break;
                case sf::Keyboard::Down:
                    _menu_seleccion_zombie->down();
                    break;
                case sf::Keyboard::Return:
                    switch (_menu_seleccion_zombie->getSelectedItem())  ///por aca las opciones de menu secundario
                    {
                    case MORTY:                            ///seria el 0, corresponde a Morty
                        //std::cout << "MORTY" << std::endl;
                        ///ACA VOY DIRECTO AL GAMEPLAY con MORTY
                        t = aJugarHijo(*_player, 0, window);
                        break;
                    case SALLY:
                       // std::cout << "SALLY" << std::endl;
                        ///ACA VOY DIRECTO AL GAMEPLAY con sally
                        t = aJugarHijo(*_player, 1, window);
                        break;
                    case IGOR:
                       // std::cout << "IGOR" << std::endl;
                        ///ACA VOY DIRECTO AL GAMEPLAY con igor
                        t = aJugarHijo(*_player, 2, window);
                        break;
                    case VOLVER_SECUN:
                       // std::cout << "VOLVER A SECUNDARIO" << std::endl;
                        t = TIPO_MENU::SECUNDARIO;
                        break;
                    case VOLVER_AL_PPAL:
                       // std::cout << "VOLVER A PRINCIPAL" << std::endl;
                        t = TIPO_MENU::PRINCIPAL;
                        break;
                    }
                    break;
                }
                break;
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }


        window.clear(sf::Color(0,0,0));
        window.draw(*_menu_seleccion_zombie);   ///dibujo el contendido , que es un menu dibujable :)
        showZombieTeam(window);
        window.display();
        return t;
    }
}

TIPO_MENU Juego2::winner(sf::RenderWindow& window)
{
    TIPO_MENU t = TIPO_MENU::WINNER;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyReleased:
                switch (event.key.code)     ///Pregunto que tecla fue, arriba/abajo/enter
                {
                case sf::Keyboard::Up:
                    _menu_winner->up();
                    break;
                case sf::Keyboard::Down:
                    _menu_winner->down();
                    break;
                case sf::Keyboard::Return:
                    switch (_menu_winner->getSelectedItem())   ///por aca las opciones en el menu WINNER
                    {
                    case VOLVER:                            ///seria el 0, corresponde a VOLVER
                       // std::cout << "VOLVER" << std::endl;
                        t = TIPO_MENU::PRINCIPAL;
                        break;
                    case SALIR_RyC:
                       // std::cout << "SALIR" << std::endl;
                        t = TIPO_MENU::EXIT;
                        break;
                    }
                    break;
                }
                break;
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(0,0,0));
        window.draw(*_menu_winner);   ///dibujo el contendido , que es un menu dibujable :)
        showWinnerText(window);
        window.display();
        return t;
    }
}

TIPO_MENU Juego2::gameOver(sf::RenderWindow& window)
{
    TIPO_MENU t = TIPO_MENU::GAME_OVER;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyReleased:
                switch (event.key.code)     ///Pregunto que tecla fue, arriba/abajo/enter
                {
                case sf::Keyboard::Up:
                    _menu_game_over->up();
                    break;
                case sf::Keyboard::Down:
                    _menu_game_over->down();
                    break;
                case sf::Keyboard::Return:
                    switch (_menu_game_over->getSelectedItem())   ///por aca las opciones en el menu GAME OVER
                    {
                    case VOLVER:                            ///seria el 0, corresponde a VOLVER
                       // std::cout << "VOLVER" << std::endl;
                        t = TIPO_MENU::PRINCIPAL;
                        break;
                    case SALIR_RyC:
                       // std::cout << "SALIR" << std::endl;
                        t = TIPO_MENU::EXIT;
                        break;
                    }
                    break;
                }
                break;
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(0,0,0));
        window.draw(*_menu_game_over);   ///dibujo el contendido , que es un menu dibujable :)
        showLoserText(window);
        window.display();
        return t;
    }
}

void Juego2::showStart(sf::RenderWindow& window)
{
    sf::Text text;
    sf::Font font;
    sf::Texture _texture_morty;
    sf::Sprite _sprite_morty;
    sf::Texture _texture_planta;
    sf::Sprite _sprite_planta;

    font.loadFromFile("Font/Lethal Slime.ttf");

    text = sf::Text("ZOMBIES VS. PLANTAZ", font, 30);
    text.setFillColor(sf::Color(255, 255, 255, 180));
    text.setPosition(350, 40);

    _texture_morty.loadFromFile("img/Morty.png");
    _sprite_morty.setTexture(_texture_morty);
    _sprite_morty.scale(0.5, 0.5);
    _sprite_morty.setPosition(150, 450);

    _texture_planta.loadFromFile("img/Planta.png");
    _sprite_planta.setTexture(_texture_planta);
    _sprite_planta.scale(0.4, 0.4);
    _sprite_planta.setPosition(900, 450);

    window.draw(text);
    window.draw(_sprite_morty);
    window.draw(_sprite_planta);
}

void Juego2::showBestTeam(sf::RenderWindow& window)
{
    sf::Text utn;
    sf::Text labo;
    sf::Text project;
    sf::Text fer;
    sf::Text charlie;
    sf::Text gonzo;

    sf::Font font;
    font.loadFromFile("Font/TT Interphases Pro Trial Black.ttf");

    utn = sf::Text("U.T.N.", font, 100);
    utn.setFillColor(sf::Color(255, 255, 255, 180));
    utn.setPosition(500, 50);

    labo = sf::Text("Laboratorio II", font, 60);
    labo.setFillColor(sf::Color(255, 255, 255, 180));
    labo.setPosition(450, 150);

    project = sf::Text("Proyecto realizado por:", font, 40);
    project.setFillColor(sf::Color(255, 255, 255, 180));
    project.setPosition(50, 350);

    fer = sf::Text("Fernando Daniel Clingo_______________________ Legajo xxxxx", font, 30);
    fer.setFillColor(sf::Color(255, 255, 255, 180));
    fer.setPosition(60, 420);

    charlie = sf::Text("Carlos Matias Marques_______________________ Legajo xxxxx", font, 30);
    charlie.setFillColor(sf::Color(255, 255, 255, 180));
    charlie.setPosition(60, 470);

    gonzo = sf::Text("Andres Gonzalo Bianchini_____________________ Legajo xxxxx", font, 30);
    gonzo.setFillColor(sf::Color(255, 255, 255, 180));
    gonzo.setPosition(60, 520);

    window.draw(utn);
    window.draw(labo);
    window.draw(project);
    window.draw(fer);
    window.draw(charlie);
    window.draw(gonzo);
}

void Juego2::showZombieTeam(sf::RenderWindow& window)
{
    sf::Texture _texture_morty;
    sf::Sprite _sprite_morty;

    sf::Texture _texture_sally;
    sf::Sprite _sprite_sally;

    sf::Texture _texture_igor;
    sf::Sprite _sprite_igor;


    _texture_morty.loadFromFile("img/Morty.png");
    _sprite_morty.setTexture(_texture_morty);
    _sprite_morty.scale(0.5, 0.5);
    _sprite_morty.setPosition(200, 260);

    _texture_sally.loadFromFile("img/Sally.png");
    _sprite_sally.setTexture(_texture_sally);
    _sprite_sally.scale(0.7, 0.7);
    _sprite_sally.setPosition(450, 230);

    _texture_igor.loadFromFile("img/Igor.png");
    _sprite_igor.setTexture(_texture_igor);
    _sprite_igor.scale(0.37, 0.37);
    _sprite_igor.setPosition(770, 230);

    window.draw(_sprite_morty);
    window.draw(_sprite_sally);
    window.draw(_sprite_igor);
}

void Juego2::showRule(sf::RenderWindow& window)
{
    sf::Sprite sprite_X;
    sf::Texture texture_X;
    sf::Sprite sprite_Z;
    sf::Texture texture_Z;
    sf::Sprite sprite_Izq;
    sf::Texture texture_Izq;
    sf::Sprite sprite_Der;
    sf::Texture texture_Der;
    sf::Sprite sprite_P;
    sf::Texture texture_P;
    sf::Texture _texture_morty;
    sf::Sprite _sprite_morty;
    sf::Texture _texture_historia;
    sf::Sprite _sprite_historia;
    sf::Text X;
    sf::Text Z;
    sf::Text Der;
    sf::Text Izq;
    sf::Text P;
    sf::Font font;
    sf::Text nombre_text;
    sf::Font nombre_font;

    nombre_font.loadFromFile("Font/Lethal Slime.ttf");

    nombre_text = sf::Text("ZOMBIES VS. PLANTAZ", nombre_font, 30);
    nombre_text.setFillColor(sf::Color(255, 255, 255, 180));
    nombre_text.setPosition(350, 40);

    font.loadFromFile("Font/TT Interphases Pro Trial Black.ttf");

    _texture_morty.loadFromFile("img/Morty.png");
    _sprite_morty.setTexture(_texture_morty);
    _sprite_morty.scale(0.5, 0.5);
    _sprite_morty.setPosition(200, 100);

    _texture_historia.loadFromFile("img/Historia.png");
    _sprite_historia.setTexture(_texture_historia);
    _sprite_historia.scale(0.8, 0.8);
    _sprite_historia.setPosition(510, 120);

    texture_X.loadFromFile("img/X.png");
    sprite_X.setTexture(texture_X);
    sprite_X.setPosition(110, 450);

    X = sf::Text("Saltar", font, 30);
    X.setFillColor(sf::Color(255, 255, 255, 180));
    X.setPosition(130, 600);

    texture_Z.loadFromFile("img/Z.png");
    sprite_Z.setTexture(texture_Z);
    sprite_Z.setPosition(310, 450);

    Z = sf::Text("Disparar", font, 30);
    Z.setFillColor(sf::Color(255, 255, 255, 180));
    Z.setPosition(310, 600);

    texture_Izq.loadFromFile("img/Izq.png");
    sprite_Izq.setTexture(texture_Izq);
    sprite_Izq.setPosition(510, 450);

    Izq = sf::Text("Izquierda", font, 30);
    Izq.setFillColor(sf::Color(255, 255, 255, 180));
    Izq.setPosition(510, 600);

    texture_Der.loadFromFile("img/Der.png");
    sprite_Der.setTexture(texture_Der);
    sprite_Der.setPosition(710, 450);

    Der = sf::Text("Derecha", font, 30);
    Der.setFillColor(sf::Color(255, 255, 255, 180));
    Der.setPosition(710, 600);

    texture_P.loadFromFile("img/P.png");
    sprite_P.setTexture(texture_P);
    sprite_P.setPosition(910, 450);

    P = sf::Text("Pausa", font, 30);
    P.setFillColor(sf::Color(255, 255, 255, 180));
    P.setPosition(930, 600);

    window.draw(nombre_text);
    window.draw(_sprite_morty);
    window.draw(_sprite_historia);
    window.draw(sprite_X);
    window.draw(sprite_Z);
    window.draw(sprite_Izq);
    window.draw(sprite_Der);
    window.draw(sprite_P);
    window.draw(X);
    window.draw(Z);
    window.draw(Izq);
    window.draw(Der);
    window.draw(P);
}

void Juego2::showWinnerText(sf::RenderWindow& window)
{
    sf::Text text;
    sf::Font font;
    sf::Text text_P;
    sf::Font font_P;

    font.loadFromFile("font/Come With Us.ttf");
    font_P.loadFromFile("Font/TT Interphases Pro Trial Black.ttf");

    text = sf::Text("WINER!!!", font, 150);
    text.setFillColor(sf::Color(255, 255, 255, 80));
    text.setPosition(420, 80);

    text_P = sf::Text("Ganaste 3000 puntos adicionales", font_P, 70);
    text_P.setFillColor(sf::Color(255, 255, 255, 100));
    text_P.setPosition(50, 500);

    window.draw(text);
    window.draw(text_P);
}

void Juego2::showLoserText(sf::RenderWindow& window)
{
    sf::Text text;
    sf::Font font;

    font.loadFromFile("font/Come With Us.ttf");

    text = sf::Text("GAME       OVER", font, 150);
    text.setFillColor(sf::Color(255, 255, 255, 80));
    text.setPosition(100, 400);
    window.draw(text);
}

void Juego2::showRanking(sf::RenderWindow& window, Ranking& ranking)
{
    Partida* p = ranking.getRanking();

    sf::Text text[10];
    sf::Font font;
    font.loadFromFile("font/TT Interphases Pro Trial Black.ttf");

    for (int i = 0; i < 10; i++)
    {
        text[i].setFont(font);
        text[i].setCharacterSize(20);
        text[i].setFillColor(sf::Color(255, 255, 255, 180));
        text[i].setPosition(450, 100 + i * 45);
        text[i].setString("Puesto n°:  " + std::to_string(i + 1) + "  " + p[i].getName() + " con " + std::to_string(p[i].getPuntos()) + " puntos");



        window.draw(text[i]);
    }
}


TIPO_MENU Juego2::aJugarHijo(Player& player, int num_zombie, sf::RenderWindow& window)
{
    sf::Sprite sprite_fondo;
    sf::Texture texture_fondo;

    texture_fondo.loadFromFile("img/background_zombie_1.png");
    sprite_fondo.setTexture(texture_fondo);

    Game_play gp(player, num_zombie, window);
    gp.setNombrePlayer(player.getNombre());

    Audio musica(1);

    musica.audioON();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        ///Por aca condicion de juego
        if ((gp.getGameOver() == false && gp.getEnemigos_eliminados() < 21) || (gp.getWinner() == false && gp.getEnemigos_eliminados() < 21))
        {
            gp.update(window);
            gp.cmd();

            window.clear(sf::Color(0,0,0));

            window.draw(sprite_fondo);
            gp.draw(window);

            window.display();
        }

        ///Por aca ganaste!
        if (gp.getWinner() == true && gp.getEnemigos_eliminados() == 21)
        {
            musica.audioOFF();
            ///Por aca hay que mostrar pantalla winner GONZOO!!
            gp.setPuntaje(3000);
            Partida partida(gp.getPuntaje(), gp.getNombrePlayer());
            FILE* pPartida = fopen("Partidas.dat", "ab");
            if (pPartida == nullptr)
            {
               // std::cout << "No se pudo abrir/crear archivo" << std::endl;

            }
            fwrite(&partida, sizeof(Partida), 1, pPartida);
            fclose(pPartida);
           // std::cout << "Archivo creado correctamente" << std::endl;
            return TIPO_MENU::WINNER;
        }
        else///Por aca perdiste!
        {
            if ((gp.getGameOver() == true) && (gp.getEnemigos_eliminados() <= 21))
            {
                musica.audioOFF();
                ///Por aca hay que mostrar pantalla GAMEOVER GONZOO!!
                Partida partida(gp.getPuntaje(), gp.getNombrePlayer());

                FILE* pPartida = fopen("Partidas.dat", "ab");
                if (pPartida == nullptr)
                {
                   // std::cout << "No se pudo abrir/crear archivo" << std::endl;
                }
                fwrite(&partida, sizeof(Partida), 1, pPartida);
                fclose(pPartida);
                //std::cout << "Archivo creado correctamente" << std::endl;
                return TIPO_MENU::GAME_OVER;
            }
        }
    }
}



