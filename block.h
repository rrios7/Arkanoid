#ifndef BLOCK_H
#define BLOCK_H

#include <SDL.h>
#include <SDL_image.h>

class Block
{
private:
    SDL_Renderer* renderer;

    int xDir;
    int yDir;

    int x;
    int y;
    int w;
    int h;

    int r;
    int g;
    int b;
public:
    Block(SDL_Renderer* renderer);
    Block(SDL_Renderer*, int r, int g, int b);
    virtual ~Block();

    void update();
    virtual void render();

    SDL_Renderer *getRenderer() const;

    int getX() const;
    void setX(int x);
    int getY() const;
    void setY(int y);

    void setDirection(int x, int y);
    int getXDir() const;
    int getYDir() const;

    int getW() const;
    void setW(int w);
    int getH() const;
    void setH(int h);


    int getR() const;
    int getG() const;
    int getB() const;
};

#endif // BLOCK_H
