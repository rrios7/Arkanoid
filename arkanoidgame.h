#ifndef ARKANOIDGAME_H
#define ARKANOIDGAME_H

#include "game.h"
#include "block.h"
#include "ball.h"

#include <list>

class ArkanoidGame : public Game
{
private:
    std::list<Block*> targets;
    Block* plat;
    Ball* ball;
    bool ballLaunched;

    TTF_Font* font;
    int score;

    void renderScore();
    void renderTargets();

    void moveBallWithPlat();

    void managePlatCollision();
    void manageBallCollision();
    void manageTargetCollision();
    void manageBallPlatCollision();
public:
    ArkanoidGame();

    void run();
    void handleEvents();
    void update();
    void render();
    void clean();
};

#endif // ARKANOIDGAME_H
