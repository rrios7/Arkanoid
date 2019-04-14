#ifndef BALL_H
#define BALL_H

#include "block.h"

class Ball : public Block
{
private:
    SDL_Texture* texture;

public:
    Ball(SDL_Renderer* renderer);
    ~Ball();

    void render();
};

#endif // BALL_H
