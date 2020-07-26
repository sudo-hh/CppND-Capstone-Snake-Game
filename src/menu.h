#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <memory>

#define COMMON_COLOR_MAX 255
#define COMMON_WINDOW_WIDTH 640
#define COMMON_WINDOW_HEIGHT (COMMON_WINDOW_WIDTH)
#define MAX_STRING_LEN 4

class Menu {
    public:
        Menu();
        ~Menu();
        Menu(const Menu &source) = delete; // Copy will be forbidden
        Menu &operator=(const Menu &source) = delete; // Copy will be forbidden
        Menu(Menu &&source); // Move constructor
        Menu &operator=(Menu &&source); // Move assignment operator

        virtual void showMenu() = 0;

    protected:
        void render_text(SDL_Renderer *renderer, int x, int y, const char *text, TTF_Font *font, SDL_Rect *rect, SDL_Color *color);

        SDL_Color color;
        SDL_Event event;
        SDL_Rect rect;
        std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> _menu_window;
        std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> _menu_renderer;

        const std::string font_path = "../src/fonts/FreeSans.ttf";

};

#endif