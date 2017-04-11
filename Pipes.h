#ifndef PIPES__H
#define PIPES__H
#include "bird.h"

const int VELOCITY = 4;
const int RANGE = 170;

/*
    itemType
       0 .. 1 : bonus 5 scores
       2 : change bird type
       3 : change bird size
*/

struct typePipe {
    SDL_Rect down, up, item;
    int haveItem = rand() % 10, typeItem = rand() % 4,
        eat = 1;
    typePipe()
    {
        up.w = down.w = 70;

        up.h = rand() % (SCREEN_HEIGHT-200) + 40;
        up.y = 0;

        down.h = SCREEN_HEIGHT - up.h - RANGE;
        down.y = up.h + RANGE;

        //item
        if ( haveItem < 3 )
        {
            item.y = up.h - 30 + rand() % (60 + RANGE);
            item.w = item.h = 25;
        }
    }
};

void addNewPipes(std::vector <typePipe> &p);
void runPipes(std::vector <typePipe> &p, structBird &faky, int &score, int &gameOver);
void drawPipes(SDL_Renderer* &renderer, typePipe pipe,
               SDL_Texture* &upPipe, SDL_Texture* &downPipe, SDL_Texture* &item);
#endif // PIPES__H
