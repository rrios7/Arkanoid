#include "game.h"

bool Game::getIsRunning() const
{
    return isRunning;
}

void Game::setIsRunning(bool value)
{
    isRunning = value;
}

SDL_Window *Game::getWindow() const
{
    return window;
}

void Game::setWindow(SDL_Window *value)
{
    window = value;
}

SDL_Renderer *Game::getRenderer() const
{
    return renderer;
}

void Game::setRenderer(SDL_Renderer *value)
{
    renderer = value;
}

int Game::getScreenWidth() const
{
    return screenWidth;
}

void Game::setScreenWidth(int value)
{
    screenWidth = value;
}

int Game::getScreenHeight() const
{
    return screenHeight;
}

void Game::setScreenHeight(int value)
{
    screenHeight = value;
}

void Game::init(const char *title, int w, int h, bool fullscreen)
{
    int flags = 0;
    screenWidth = w;
    screenHeight = h;

    if (fullscreen)
        flags = SDL_WINDOW_FULLSCREEN;

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);

        renderer = SDL_CreateRenderer(window, -1, 0);

        if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 1, 4096) == -1) {
            std::cout << "No se pudo inicializar los componentes de audio" << std::endl;
        }

        if (TTF_Init() == - 1) {
            std::cout << "No se pudo inicializar el TrueType Font" << std::endl;
        }

        if (renderer) {
            //SDL_SetRenderDrawColor(renderer, r, g, b, alpha)
            //r, g y b son valores entre 0 y 255
            // 0, 0, 0 es color negro
            // 255, 255, 255 es colo blanco
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

            isRunning = true;
        } else {
            std::cout << "Couldn't initialize renderer" << SDL_GetError() << std::endl;
        }
    }
}

Game::Game() : isRunning(false) {}
