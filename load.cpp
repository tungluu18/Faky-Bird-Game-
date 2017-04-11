#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "load.h"
#include "renderText.h"

using namespace std;

Mix_Music *epic, *johnCena, *sadViolin;
Mix_Chunk *whip, *ding, *dead;

void loadSound()
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    epic         = Mix_LoadMUS("sound/epic.mp3");
    sadViolin    = Mix_LoadMUS("sound/sadViolin.mp3");
    johnCena     = Mix_LoadMUS("sound/johnCena.mp3");

    whip         = Mix_LoadWAV("sound/whip.wav");
    ding         = Mix_LoadWAV("sound/ding.wav");
    dead         = Mix_LoadWAV("sound/dead.wav");
}

SDL_Texture *bird[6], *upPipe, *downPipe, *item, *forest, *youlost, *newHighscore;
void loadImage(SDL_Renderer* &renderer)
{
    for (int i = 0; i < 6; i++)
    {
        string filePath = "pic/bird" + convertIntToString(i) + ".png";
        bird[i]  = IMG_LoadTexture(renderer, filePath.c_str());
    }
    upPipe       = IMG_LoadTexture(renderer, "pic/UpPipe.png");
    downPipe     = IMG_LoadTexture(renderer, "pic/DownPipe.png");
    item         = IMG_LoadTexture(renderer, "pic/apple.png");
    forest       = IMG_LoadTexture(renderer, "pic/forest.jpg");
    youlost      = IMG_LoadTexture(renderer, "pic/youlost.png");
    newHighscore = IMG_LoadTexture(renderer, "pic/newHighscore.png");
}
