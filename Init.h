#ifndef INIT__H
#define INIT__H
const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;

void logSDLError(std::ostream& os, const std::string &msg, bool fatal);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
#endif // INIT__H




