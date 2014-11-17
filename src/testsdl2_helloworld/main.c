#include "SDL2/SDL.h"

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;
    SDL_Surface *hello = NULL;
    SDL_Surface *screen = NULL;

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("SDL Tutorial",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            640, 480, SDL_WINDOW_SHOWN);

    screen = SDL_GetWindowSurface(window);

    hello = SDL_LoadBMP("../assets/images/helloworld.bmp");

    SDL_BlitSurface(hello, NULL, screen, NULL);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(2000);

    SDL_FreeSurface(hello);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
