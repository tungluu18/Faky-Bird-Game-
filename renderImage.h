#ifndef RENDERIMAGE__H
#define RENDERIMAGE__H
void renderImage(SDL_Renderer* &renderer, SDL_Rect* &rect, SDL_Texture* &imgTexture);
void renderImageAt(SDL_Renderer* &renderer, SDL_Texture* &imgTexture, int x, int y, int w, int h);
#endif // RENDERIMAGE__H


