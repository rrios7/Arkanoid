#include "block.h"

using namespace std;

Block::Block(SDL_Renderer* renderer)
{
    this->renderer = renderer;

    this->x = 0;
    this->y = 0;
    this->w = 0;
    this->h = 0;

    this->r = 0;
    this->g = 0;
    this->b = 0;
}

Block::Block(SDL_Renderer* renderer, int r, int g, int b)
{
    this->renderer = renderer;

    this->x = 0;
    this->y = 0;
    this->w = 0;
    this->h = 0;

    this->r = r;
    this->g = g;
    this->b = b;
}

Block::~Block() {}

void Block::update()
{
    this->x = x + xDir;
    this->y = y + yDir;
}

void Block::render()
{
    SDL_Rect rect;

    rect.x = this->x;
    rect.y = this->y;
    rect.w = this->w;
    rect.h = this->h;

    SDL_SetRenderDrawColor(getRenderer(), this->r, this->g, this->b, 255);
    SDL_RenderFillRect(getRenderer(), &rect);
}

SDL_Renderer *Block::getRenderer() const
{
    return renderer;
}

int Block::getX() const
{
    return this->x;
}

void Block::setX(int x)
{
    this->x = x;
}

void Block::setY(int y)
{
    this->y = y;
}

int Block::getY() const
{
    return this->y;
}

void Block::setDirection(int x, int y) {
    this->xDir = x;
    this->yDir = y;
}

int Block::getXDir() const
{
    return xDir;
}

int Block::getYDir() const
{
    return yDir;
}

int Block::getW() const
{
    return w;
}

void Block::setW(int w)
{
    this->w = w;
}

int Block::getH() const
{
    return h;
}

void Block::setH(int h)
{
    this->h = h;
}

int Block::getR() const
{
    return this->r;
}

int Block::getG() const
{
    return this->g;
}

int Block::getB() const
{
    return this->b;
}
