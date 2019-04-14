#include "ball.h"

Ball::Ball(SDL_Renderer* renderer) : Block(renderer)
{
    SDL_Surface* surface = IMG_Load("pelotita.png");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

Ball::~Ball() {
    SDL_DestroyTexture(texture);
}

void Ball::render() {
    SDL_Rect rect;
    rect.x = getX();
    rect.y = getY();
    rect.w = getW();
    rect.h = getH();
    SDL_RenderCopy(getRenderer(), texture, nullptr, &rect);
}
