#include <bits/stdc++.h>
#include <SDL.h>
#include <time.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "Init.h"
#include "bird.h"
#include "Pipes.h"
#include "renderText.h"
#include "renderImage.h"
#include "load.h"

using namespace std;
/*---------------------------------------------------------------------------------------------------------*/
enum EVENT { SPACE,  ESC,  P,  QUIT,  NOPE };
EVENT waitEvent()
{
    SDL_Event e;
    while ( SDL_PollEvent(&e) ) {
        if ( e.type == SDL_QUIT ) return QUIT;
        if ( e.type != SDL_KEYDOWN ) return NOPE;
        if ( e.key.keysym.sym == SDLK_SPACE ) return SPACE;
        if ( e.key.keysym.sym == SDLK_ESCAPE ) return ESC;
        if ( e.key.keysym.sym == SDLK_p ) return P;
    }
    return NOPE;
}
/*---------------------------------------------------------------------------------------------------------*/
void display(SDL_Renderer* &renderer, SDL_Rect* &rect, vector <typePipe> &p, int &score);
int playGame(SDL_Renderer* &renderer);
void mainMenuGame(SDL_Renderer *renderer);
int menuLostGame(SDL_Renderer* &renderer);
/*---------------------------------------------------------------------------------------------------------*/
int best = 0, newBest = 0;
int main(int argc, char* argv[])
{
    srand(time(NULL));

    TTF_Init();
    SDL_Window *window;
    SDL_Renderer *renderer;
    initSDL(window, renderer);

    loadSound();
    loadImage(renderer);
    mainMenuGame(renderer);

    Mix_FreeMusic(epic);
    Mix_FreeMusic(johnCena);
    Mix_FreeMusic(sadViolin);
    Mix_FreeChunk(whip);
    Mix_FreeChunk(dead);
    Mix_FreeChunk(ding);
    Mix_Quit();

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}
/*---------------------------------------------------------------------------------------------------------*/
void display(SDL_Renderer* &renderer, structBird &faky, vector <typePipe> &p, int &score)
{
    //xoa man hinh ve mau trang
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    //background
    renderImageAt(renderer, forest, 0, 0, SCREEN_WIDTH*2, SCREEN_HEIGHT);
    //in con chim va ong nuoc
    for (int i = 0; i < (int)p.size(); i++)
        drawPipes(renderer, p[i], upPipe, downPipe, item);
    renderImage(renderer, faky.birdShape, bird[faky.birdType]);
    //in diem
    if ( score > best ) newBest = 1;  //xac nhan ky luc moi
    best = max(best, score);
    renderText(renderer, 20, 20, 40, "2203.ttf", "SCORE : " + convertIntToString(score));  //diem hien tai
    renderText(renderer, 20, 60, 40, "2203.ttf", "BEST : " + convertIntToString(best));    //diem best

    //hien thi
    SDL_RenderPresent(renderer);
}
/*---------------------------------------------------------------------------------------------------------*/
void mainMenuGame(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    //background
    renderImageAt(renderer, forest, 0, 0, SCREEN_WIDTH*2, SCREEN_HEIGHT);
    //press SPACE to play and ESC to quit
    renderText(renderer, 180, 350, 70, "BOMBARD.ttf", "Press SPACE to Play");
    renderText(renderer, 300, 500, 35, "BOMBARD.ttf", "Press ESC to Quit");
    renderImageAt(renderer, bird[3], 300, 250, 75, 75);
    renderImageAt(renderer, bird[1], 400, 250, 75, 75);
    renderImageAt(renderer, bird[5], 500, 250, 75, 75);

    EVENT e = NOPE;
    while ( e == NOPE )
    {
        e = waitEvent();
        SDL_RenderPresent(renderer);
    }
    if ( e == SPACE )
    {
        int continuePlay;
        do {
            continuePlay = playGame(renderer);
        } while ( continuePlay );  //neu sau game nay nguoi choi chon choi tiep
    } else return;
}
/*---------------------------------------------------------------------------------------------------------*/
int menuLostGame(SDL_Renderer* &renderer, structBird &faky, vector <typePipe> &p, int &score)
{
    //falling bird
    while ( faky.birdShape->y < SCREEN_HEIGHT - faky.birdShape->h + 15 )
    {
        faky.birdShape->y = min(faky.birdShape->y + 3*GRAVITY, SCREEN_HEIGHT - faky.birdShape->h + 15);
        display(renderer, faky, p, score);
    }

    renderText(renderer, 230, 350, 33, "BOMBARD.ttf",
               "[SPACE] - Retry    [ESC] - Quit Game");

    //new highscore
    if ( newBest )
    {
        renderImageAt(renderer, newHighscore, 220, 250, 525, 100);
        renderText(renderer, 250, 400, 27, "BOMBARD.ttf",
                   "You get new highscore : " + convertIntToString(best));
        Mix_PlayMusic(johnCena, -1);
    }
    else
    {
        Mix_PlayMusic(sadViolin, -1);
        renderImageAt(renderer, youlost, 220, 250, 500, 75);
    }

    SDL_RenderPresent(renderer);

    EVENT e = NOPE;
    //doi sau khi hien thi youlost 2 giay moi nhan lenh moi
    int currentTime = SDL_GetTicks();
    while ( e == NOPE || SDL_GetTicks() - currentTime < 2000 )
    {
        e = waitEvent();
        SDL_RenderPresent(renderer);
    }

    delete faky.birdShape;
    Mix_HaltMusic();
    return e == SPACE;
}
/*---------------------------------------------------------------------------------------------------------*/
int playGame(SDL_Renderer* &renderer)
{
    //bat nhac
    Mix_PlayMusic(epic, -1);
    //tao con chim
    structBird faky;
    //tao ong nuoc
    vector < typePipe > p(1);
    p[0].up.x = p[0].down.x = 400;
    p[0].haveItem = 0;
    addNewPipes(p);

    SDL_Event e;
    int score = 0, gameOver = 0, jump = 0, prevScore = 0;
    newBest = 0;
    while ( !gameOver )
    {
        if ( SDL_PollEvent(&e) )
        {
            if ( e.type == SDL_QUIT )               break;
            if ( e.type != SDL_KEYDOWN )            continue;
            if ( e.key.keysym.sym == SDLK_ESCAPE )  break;
            if ( e.key.keysym.sym == SDLK_SPACE )
            {
                jump = JUMPING;
                Mix_PlayChannel(-1, whip, 0);
            }
        }

        faky.birdShape->y = max(0, faky.birdShape->y - jump + GRAVITY);

        if ( !faky.birdShape->y )
            jump = 0;
        else
            jump = max(0, jump - GRAVITY);

        if ( faky.birdShape->y >= SCREEN_HEIGHT - faky.birdShape->h + 20 )
            gameOver = 1;  //chim roi xuong dat

        runPipes(p, faky, score, gameOver);

        if ( score > prevScore )  //ghi diem
        {
            prevScore = score;
            Mix_PlayChannel(-1, ding, 0);
        }
        addNewPipes(p);

        display(renderer, faky, p, score);
    }

    //tat nhac
    Mix_HaltMusic();
    if ( gameOver )
    {
        Mix_PlayChannel(-1, dead, 0);
        return menuLostGame(renderer, faky, p, score);
    }

    delete faky.birdShape;
    return 0;
}
/*---------------------------------------------------------------------------------------------------------*/
