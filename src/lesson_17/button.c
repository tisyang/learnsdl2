#include "button.h"

#include "texture.h"



enum ButtonSprite {
    BUTTON_SPRITE_MOUSE_OUT,
    BUTTON_SPRITE_MOUSE_OVER_MOTION,
    BUTTON_SPRITE_MOUTSE_DOWN,
    BUTTON_SPRITE_MOUSE_UP,
    BUTTON_SPRITE_TOTAL,
};

static SDL_Rect BUTTON_CLIPS[] = {
    {0, BUTTON_HEIGHT * 0, BUTTON_WIDTH, BUTTON_HEIGHT},
    {0, BUTTON_HEIGHT * 1, BUTTON_WIDTH, BUTTON_HEIGHT},
    {0, BUTTON_HEIGHT * 2, BUTTON_WIDTH, BUTTON_HEIGHT},
    {0, BUTTON_HEIGHT * 3, BUTTON_WIDTH, BUTTON_HEIGHT},
};

static SDL_Texture * Button_Texture = NULL;

bool Button_InitSprite(SDL_Renderer *render, const char *imgpath)
{
    Button_Texture = Texture_Load(render, imgpath);
    return (Button_Texture != NULL);
}

void Button_Init(struct Button *button)
{
    button->x = 0;
    button->y = 0;
    button->w = BUTTON_WIDTH;
    button->h = BUTTON_HEIGHT;
    button->sprite = BUTTON_SPRITE_MOUSE_OUT;
}

void Button_SetPoisiton(struct Button *button, int x, int y)
{
    button->x = x;
    button->y = y;
}
void Button_HandleEvent(struct Button *button, SDL_Event *e)
{
    if(e->type == SDL_MOUSEMOTION ||
       e->type == SDL_MOUSEBUTTONDOWN ||
       e->type == SDL_MOUSEBUTTONUP) {

        int x, y;
        bool inside = true;
        SDL_GetMouseState(&x, &y);

        if(x < button->x) {
            inside = false;
        } else if(x > (button->x + button->w)) {
            inside = false;
        } else if(y < button->y) {
            inside = false;
        } else if(y > (button->y + button->h)) {
            inside = false;
        }

        if(!inside) {
            button->sprite = BUTTON_SPRITE_MOUSE_OUT;
        } else {
            switch(e->type) {
            case SDL_MOUSEMOTION:
                button->sprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                break;
            case SDL_MOUSEBUTTONDOWN:
                button->sprite = BUTTON_SPRITE_MOUTSE_DOWN;
                break;
            case SDL_MOUSEBUTTONUP:
                button->sprite = BUTTON_SPRITE_MOUSE_UP;
                break;
            }
        }
    }
}

void Button_Render(struct Button *button, SDL_Renderer *renderer)
{
    Texture_Render(Button_Texture, renderer, button->x, button->y, &BUTTON_CLIPS[button->sprite]);
}
