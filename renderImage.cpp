#include <bits/stdc++.h>
#include <SDL_ttf.h>
#include <SDL.h>
#include <SDL_image.h>

#include "renderImage.h"
#include "load.h"

using namespace std;

void renderImage(SDL_Renderer* &renderer, SDL_Rect* &rect, SDL_Texture* &imgTexture)
{
    SDL_RenderCopy(renderer, imgTexture, NULL, rect);
}

void renderImageAt(SDL_Renderer* &renderer, SDL_Texture* &imgTexture, int x, int y, int w, int h)
{
    SDL_Rect *a = new SDL_Rect;
    a->x = x;
    a->y = y;
    a->w = w;
    a->h = h;
    renderImage(renderer, a, imgTexture);
    delete a;
}
