#include "arkanoidgame.h"

#include <ctime>
#include <functional>
#include <random>
#include <chrono>

using namespace  std;

ArkanoidGame::ArkanoidGame()
{
    srand(time(0));
    init("Arkanoid", 251, 400, false);

    //Cargamos Font
    font = TTF_OpenFont("segoeui.ttf", 16);

    //Iniciamos el Score
    score = 0;

    //Generamos la plataforma
    plat = new Block(getRenderer());
    plat->setX(getScreenWidth() / 2);
    plat->setY(getScreenHeight() - 50);
    plat->setW(36);
    plat->setH(10);

    //Generamos la bola
    ball = new Ball(getRenderer());
    ball->setX(plat->getX());
    ball->setY(plat->getY() - plat->getH());
    ball->setW(10);
    ball->setH(10);
    ballLaunched = false;

    //Generamos los targets
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 10; ++j) {
            Block* aux = new Block(getRenderer(), rand() % 255, rand() % 255, rand() % 255);

            aux->setX(j * 25);
            aux->setY(i * (getScreenHeight() / 30));
            aux->setW(25);
            aux->setH(getScreenHeight() / 30);

            targets.push_back(aux);
        }
    }


    run();
}

void ArkanoidGame::run()
{
    const int FPS = 60;
    const int FRAME_DELAY = 1000 / FPS;
    unsigned int frameStart;
    unsigned int frameTime;

    while (getIsRunning()) {
        //Tomamos el tiempo de inicio del frame
        frameStart = SDL_GetTicks();
        handleEvents();
        update();
        render();
        //Tomamos el tiempo que tardó el frame
        frameTime = SDL_GetTicks() - frameStart;

        if (FRAME_DELAY > frameTime)
            SDL_Delay(FRAME_DELAY - frameTime);

    }
    clean();
}

void ArkanoidGame::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        setIsRunning(false);
        break;
    case SDL_KEYDOWN:
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_LEFT:
            plat->setDirection(-3, 0);
            break;
        case SDLK_RIGHT:
            plat->setDirection(3, 0);
            break;
        case SDLK_SPACE:
        {
            if (!ballLaunched) {
                ballLaunched = true;
                int dir = rand() % 2;
                if (dir == 0) {
                    ball->setDirection(1, -1);
                } else {
                    ball->setDirection(-1, -1);
                }
            }
        }
            break;
        case SDLK_DELETE:
            targets.pop_front();
            break;
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

void ArkanoidGame::update()
{
    //Movimiento de la bola
    if (!ballLaunched) {
        moveBallWithPlat();
    } else {
        ball->update();
        manageBallPlatCollision();
    }
    manageBallCollision();
    manageTargetCollision();

    //Movimiento de la plataforma
    plat->update();
    managePlatCollision();

    //Ganar juego
    if (targets.size() == 0) {
        cout << "Ganaste" << endl;
        setIsRunning(false);
    }
}

void ArkanoidGame::render()
{
    //Limpiar el renderer
    SDL_RenderClear(getRenderer());

    //Dibujamos el score
    renderScore();

    //Dibujamos la plataforma
    plat->render();

    //Dibujamos la pelota
    ball->render();

    //Dibujamos los targets
    renderTargets();

    //Asignamos color para dibujar
    SDL_SetRenderDrawColor(getRenderer(), 255, 255, 255, 255);

    //Dibujamos con el renderer
    SDL_RenderPresent(getRenderer());
}

void ArkanoidGame::clean()
{
    SDL_DestroyWindow(getWindow());
    SDL_DestroyRenderer(getRenderer());
    Mix_CloseAudio();
    SDL_Quit();
}

void ArkanoidGame::renderScore()
{
    string text = "Score: " + to_string(score);
    SDL_Color color  = {0, 0, 0, 255};

    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(getRenderer(), surface);

    SDL_FreeSurface(surface);

    int textW = 0;
    int textH = 0;

    SDL_QueryTexture(texture, nullptr, nullptr, &textW, &textH);

    SDL_Rect rect = {0, 380, textW, textH};

    SDL_RenderCopy(getRenderer(), texture, nullptr, &rect);
}

void ArkanoidGame::renderTargets()
{
    for (auto it = targets.begin(); it != targets.end(); ++it) {
        Block* b = *it;

        b->render();
    }
}

void ArkanoidGame::moveBallWithPlat()
{
    ball->setX(plat->getX() + plat->getW() / 2);
    ball->setY(plat->getY() - plat->getH());
}

void ArkanoidGame::managePlatCollision()
{
    if (plat->getX() + plat->getXDir() <= 0) { //Limite Izquierdo
        plat->setDirection(2, 0);
    } else if (plat->getX() + plat->getXDir() >= getScreenWidth() - plat->getW()) { //Limite Derecho
        plat->setDirection(-2, 0);
    }
}

void ArkanoidGame::manageBallCollision()
{
    //Velocidad random
    int speed = rand() % 2 + 1;

    //Inversión de dirección en X
    if (ball->getX() + ball->getXDir() <= 0) { //Limite Izquierdo
        ball->setDirection(speed, ball->getYDir());
    } else if (ball->getX() + ball->getXDir() >= getScreenWidth() - ball->getW()) { //Limite Derecho
        ball->setDirection(speed * -1, ball->getYDir());
    }

    //Inversión de dirección en Y
    if (ball->getY() + ball->getYDir() <= 0) { //Limite Superior
        ball->setDirection(speed, 2);
    } else if (ball->getY() + ball->getYDir() >= getScreenHeight() - ball->getH()) { //Limite Inferior
        cout << "Perdiste puto" << endl;
        setIsRunning(false); //Fin del juego
    }
}

void ArkanoidGame::manageTargetCollision()
{
    //Velocidad random
    int speed = rand() % 2 + 1;

    for (auto it = targets.begin(); it != targets.end(); ++it) { //Checamos todos los bloques
        Block* aux = *it;

        if (ball->getX() + ball->getW() > aux->getX() && ball->getX() < aux->getX() + aux->getW()
                && ball->getY() + ball->getH() > aux->getY() && ball->getY() < aux ->getY() + aux->getH()) {
            ++score;
            targets.erase(it);

            ball->setDirection(speed * -1, ball->getYDir() * -1 ); //Invertimos posiciones
        }
    }
}

void ArkanoidGame::manageBallPlatCollision()
{
    //Velocidad random
    int speed = rand() % 3 + 1;

    if (ball->getX() + ball->getW() > plat->getX() && ball->getX() < plat->getX() + plat->getW() && ball->getY() + ball->getH() > plat->getY() && ball->getY() < plat->getY() + plat->getH()) {
        ball->setDirection(speed * -1, ball->getYDir() * -1);
    }
}
