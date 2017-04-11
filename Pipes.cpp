#include <bits/stdc++.h>
#include <SDL.h>
#include <time.h>

#include "Init.h"
#include "Pipes.h"
#include "renderImage.h"
#include "load.h"
#include "bird.h"

using namespace std;

inline int intersection(int a, int b, int x, int y)
{
    return (x < min(a,b) && min(a,b) < y) || (a < min(x,y) && min(x,y) < b) ;
}

inline int twoRectCut(const SDL_Rect &R1, const SDL_Rect &R2)
{
    return intersection(R1.x, R1.x+R1.w, R2.x, R2.x+R2.w)
           && intersection(R1.y, R1.y+R1.h, R2.y, R2.y+R2.h);
}

inline int hitThePipe(const structBird &faky, const typePipe &p)
{
    return twoRectCut(*faky.birdShape, p.up) || twoRectCut(*faky.birdShape, p.down);
}

void addNewPipes(vector <typePipe> &p)
{
    while ( p.begin() -> down.x < 0 )
        p.erase(p.begin());

    while ( p.back().up.x < SCREEN_WIDTH) {
        typePipe newPipe;
        if ( newPipe.up.h - p.back().up.h > 250 )
            newPipe.up.h -= 50;
        if ( p.back().up.h - newPipe.up.h > 250 )
            newPipe.up.h += 50;
        newPipe.down.y = newPipe.up.h + RANGE;
        newPipe.down.h = SCREEN_HEIGHT - newPipe.up.h - RANGE;

        newPipe.up.x = newPipe.down.x = p.back().up.x + 320;
        newPipe.item.x = newPipe.up.x - 150 + rand() % 50;
        p.push_back(newPipe);
    }
}

void runPipes(vector <typePipe> &p, structBird &faky, int &score, int &gameOver)
{
    for (int i = 0; i < (int)p.size(); i++) {
        p[i].up.x   -= VELOCITY;
        p[i].down.x -= VELOCITY;
        if ( p[i].haveItem ) p[i].item.x -= VELOCITY;

        if ( hitThePipe(faky, p[i]) )
            gameOver = 1;
        else if ( p[i].haveItem && twoRectCut(*faky.birdShape, p[i].item) )  //chim an duoc item
        {
            if ( p[i].typeItem < 2 )
                score += 5;
            else if ( p[i].typeItem == 2 )  //change bird's type
                faky.birdType = rand() % 6;
            else  //change bird's size
            {
                faky.birdShape->w = faky.birdShape->w + faky.birdSize * CHANGE_SIZE;
                faky.birdShape->h = faky.birdShape->h + faky.birdSize * CHANGE_SIZE;
                if ( faky.birdShape->w == BIRD_INIT_W )
                    faky.birdSize = 1 - 2 * (rand() % 2);
                else
                    faky.birdSize *= (-1);
            }
            p[i].haveItem = 0;
        }
    }
    //chim bay qua 1 cot thi xoa cot
    if ( !hitThePipe(faky, p[0]) && faky.birdShape->x > p[0].up.x + p[0].up.w) {
        score += p[0].eat;
        p[0].eat &= 0;
        //p.erase(p.begin());
    }
    if ( p[0].up.x < 0 ) {
        p[0].up.w   += p[0].up.x;
        p[0].down.w += p[0].up.x;
        p[0].up.x    = p[0].down.x = 0;
        if ( p[0].up.w <= 0 ) p.erase(p.begin());
    }
}

void drawPipes(SDL_Renderer* &renderer, typePipe pipe,
               SDL_Texture* &upPipe, SDL_Texture* &downPipe, SDL_Texture* &item)
{
    SDL_Rect* pUp = &(pipe.up);
    renderImage(renderer, pUp, upPipe);

    SDL_Rect* pDown = &(pipe.down);
    renderImage(renderer, pDown, downPipe);

    if ( pipe.haveItem ) {
        SDL_Rect* pItem = &(pipe.item);
        renderImage(renderer, pItem, item);
    }
}
