#ifndef BIRD__H
#define BIRD__H
const int JUMPING = 25;
const int GRAVITY = 5;
const int CHANGE_SIZE = 15;
const int BIRD_INIT_W = 60;
const int BIRD_INIT_H = 50;

struct structBird
{
    SDL_Rect* birdShape = new SDL_Rect;
    structBird()
    {
        birdShape->x = 100;             birdShape->y = SCREEN_HEIGHT/2 - 15;
        birdShape->w = BIRD_INIT_W;     birdShape->h = BIRD_INIT_H;
    }
    int birdType = rand() % 6,
        birdSize = 1 - 2 * (rand() % 2);
};
#endif //BIRD__H
