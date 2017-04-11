#ifndef VARI__H
#define VARI__H
#include <SDL_mixer.h>

extern SDL_Texture *bird[6], *upPipe, *downPipe, *item, *forest, *youlost, *newHighscore;
extern Mix_Music *epic, *johnCena, *sadViolin;
extern Mix_Chunk *whip, *ding, *dead;

void loadSound();
void loadImage(SDL_Renderer*& renderer);
#endif // VARI__H

