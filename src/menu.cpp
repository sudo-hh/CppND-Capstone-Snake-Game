#include "menu.h"
#include <iostream>

Menu::Menu() : _menu_window(nullptr, SDL_DestroyWindow), _menu_renderer(nullptr, SDL_DestroyRenderer) { }

void Menu::render_text(SDL_Renderer *renderer, int x, int y, const char *text, TTF_Font *font, SDL_Rect *rect, SDL_Color *color) {
    SDL_Surface *surface;
    SDL_Texture *texture;
    //std::cout << "Text: " << text << std::endl;
    surface = TTF_RenderText_Solid(font, text, *color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    rect->x = x;
    rect->y = y;
    rect->w = surface->w;
    rect->h = surface->h;

    SDL_RenderCopy(renderer, texture, NULL, rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

Menu::~Menu() {
    TTF_Quit();
    SDL_Quit();
    SDL_Delay(200);
    std::cout << "Menu destructor executed!" << std::endl;
}

Menu::Menu(Menu &&source) : _menu_window(std::move(source._menu_window)), _menu_renderer(std::move(source._menu_renderer)) {
    std::cout << "MOVING (c’tor) Menu instance " << &source << " to Menu instance " << this << std::endl;

    color = std::move(source.color);
    event = std::move(source.event);
    rect = std::move(source.rect);

    source.color = {};
    source.event = {};
    source.rect = {};
}

Menu &Menu::operator=(Menu &&source) {
    std::cout << "MOVING (assign) Menu instance " << &source << " to Menu instance " << this << std::endl;
    if (this == &source) {
        return *this;
    }

    _menu_window = std::move(source._menu_window);
    _menu_renderer = std::move(source._menu_renderer);

    color = std::move(source.color);
    event = std::move(source.event);
    rect = std::move(source.rect);

    source.color = {};
    source.event = {};
    source.rect = {};

    return *this;
}
