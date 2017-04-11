#include <bits/stdc++.h>
#include <SDL_ttf.h>
#include "renderText.h"

using namespace std;

string convertIntToString(int a)
{
    stringstream ss;
    ss << a;
    return ss.str();
}

void renderText(SDL_Renderer* &renderer, const int x, const int y, const int sizeText, string fontname, string s)
{
    TTF_Font *font = TTF_OpenFont(fontname.c_str(), sizeText);
    SDL_Surface *surfaceText = TTF_RenderText_Solid(font, s.c_str(), BLACK_COLOR);
    SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, surfaceText);

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    SDL_QueryTexture(text, NULL, NULL, &rect.w, &rect.h);

    SDL_RenderCopy(renderer, text, NULL, &rect);

    SDL_FreeSurface(surfaceText);
    SDL_DestroyTexture(text);
    text = nullptr;
}

