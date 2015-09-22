#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdbool.h>
#include <stdio.h>
#include <math.h>

enum {
    SCREEN_WIDTH = 640,
    SCREEN_HEIGHT = 480,
};

/* Start up SDL and creates window */
static bool init();
/* Loads media */
static bool load_media();
/* Frees media and shuts down SDL */
static void close();
/* Load individual image as texture */
static SDL_Texture * load_texture(const char *path);
/* Load a text rendered texture */
static SDL_Texture * load_texture_from_text(const char *text, SDL_Color color);
/* Render Texture to render at specific position */
static bool render_texture(SDL_Texture *texture,
                           int x, int y,
                           SDL_Rect *clip);
static bool render_texture_ex(SDL_Texture *texture,
                              int x, int y,
                              SDL_Rect *clip,
                              double angle,
                              SDL_Point *center,
                              SDL_RendererFlip flip);

static const char * const G_WIN_CAPTION = "Lesson 16: True Type Fonts";
SDL_Window   *g_window = NULL;
SDL_Renderer *g_renderer = NULL;
SDL_Texture  *g_texture = NULL;
TTF_Font     *g_font = NULL;


static bool
init()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n",
               SDL_GetError());
        return false;
    }

    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        printf("Warning: Linear texture filtering not enabled!\n");
    }
    /* Create window */
    g_window = SDL_CreateWindow(G_WIN_CAPTION,
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH,
                                SCREEN_HEIGHT,
                                SDL_WINDOW_SHOWN);
    if(g_window == NULL) {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    g_renderer = SDL_CreateRenderer(g_window, -1,
                                    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(g_renderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    int img_flags = IMG_INIT_PNG;
    /* see IMG_Init doc */
    if((IMG_Init(img_flags) & img_flags) != img_flags) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n",
               IMG_GetError());
        return false;
    }

    if(TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error : %s\n",
               TTF_GetError());
        return false;
    }

    return true;
}

static bool
load_media()
{
    g_font = TTF_OpenFont("lazy.ttf", 28);
    if(g_font == NULL) {
        printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }
    SDL_Color color = {0, 0, 0};
    g_texture = load_texture_from_text("The quick brown fox jumps over the lazy dog",
                                       color);
    if(g_texture == NULL) {
        printf("Failed to render text texture!\n");
        return false;
    }

    return true;
}

static void
close()
{
    SDL_DestroyTexture(g_texture);
    g_texture = NULL;

    TTF_CloseFont(g_font);
    g_font = NULL;

    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);
    g_window = NULL;
    g_renderer = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

static SDL_Texture *
load_texture(const char *path)
{
    SDL_Texture *texture = NULL;

    SDL_Surface *surface = IMG_Load(path);
    if(surface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n",
               path, IMG_GetError());
    } else {
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));
        texture = SDL_CreateTextureFromSurface(g_renderer, surface);
        if(texture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n",
                   path, SDL_GetError());
        }
        SDL_FreeSurface(surface);
    }

    return texture;
}

static SDL_Texture *
load_texture_from_text(const char *text, SDL_Color color)
{
    SDL_Surface *surface = TTF_RenderText_Solid(g_font, text, color);
    if(surface == NULL) {
        printf("Unable to reander text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return NULL;
    } else {
        SDL_Texture *texture = SDL_CreateTextureFromSurface(g_renderer, surface);
        if(texture == NULL) {
            printf("Unable to create texture from render text! SDL Error: %s\n", SDL_GetError());
        }
        SDL_FreeSurface(surface);
        return texture;
    }
}

static bool
render_texture_ex(SDL_Texture *texture,
                  int x, int y,
                  SDL_Rect *clip,
                  double angle,
                  SDL_Point *center,
                  SDL_RendererFlip flip)
{
    int w, h;
    /* Query width and height of texture */
    if(SDL_QueryTexture(texture, NULL, NULL, &w, &h) < 0) {
        /* on error */
        printf("Unable to query texture. SDL Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_Rect rect = { x, y, w, h};
    if(clip) {
        rect.w = clip->w;
        rect.h = clip->h;
    }

    SDL_RenderCopyEx(g_renderer, texture, clip, &rect, angle, center, flip);
    return true;
}

static bool
render_texture(SDL_Texture *texture,
               int x, int y,
               SDL_Rect *clip)
{
    return render_texture_ex(texture, x, y, clip, 0.0, NULL, SDL_FLIP_NONE);
}


int main(int argc, char *argv[])
{
    if(init() == false) {
        printf("Failed to initialize!\n");
        return 1;
    }
    if(load_media() == false) {
        printf("Failed to load media!\n");
        return 1;
    }
    bool quit = false;
    SDL_Event e;

    while(!quit) {
        while(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT) {
                quit = true;
            }
        }
        SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(g_renderer);

        render_texture(g_texture, 20, 200, NULL);

        SDL_RenderPresent(g_renderer);
    }
    close();
    return 0;
}
