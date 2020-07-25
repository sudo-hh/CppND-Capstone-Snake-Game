#include "menu.h"
#include <iostream>

const std::string Menu::_title_1 = "***************************************";
const std::string Menu::_title_2 = "*********The Crazy Snake*********";
const std::string Menu::_title_3 = "***************************************";
const std::string Menu::_instructions_1 = "To move the snake's direction, use the arrow keys.";
const std::string Menu::_instructions_2 = "Once your snake eats a food unit, the speed will increase!";
const std::string Menu::_instructions_3 = "If your snake eats itself, the game is over.";
const std::string Menu::_instructions_4 = "Press SPACE to continue";

Menu::Menu() : _menu_window(nullptr, SDL_DestroyWindow), _menu_renderer(nullptr, SDL_DestroyRenderer) {

        _title.push_back(_title_1);
        _title.push_back(_title_2);
        _title.push_back(_title_3);

        _instructions.push_back(_instructions_1);
        _instructions.push_back(_instructions_2);
        _instructions.push_back(_instructions_3);
        _instructions.push_back(_instructions_4);

        color.r = COMMON_COLOR_MAX;
        color.g = COMMON_COLOR_MAX;
        color.b = COMMON_COLOR_MAX;
        color.a = COMMON_COLOR_MAX;
}

void Menu::ShowMenu()
{
    /* Init window. */
    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    _menu_window.reset(SDL_CreateWindow("Snake Game",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        COMMON_WINDOW_WIDTH,
                                        COMMON_WINDOW_HEIGHT,
                                        SDL_WINDOW_SHOWN));
    _menu_renderer.reset(SDL_CreateRenderer(_menu_window.get(), -1, SDL_RENDERER_ACCELERATED));

    /* Init TTF. */
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("../src/FreeSans.ttf", 24);
    if (font == NULL) {
        std::cout << "Error: font not found!" << std::endl;     /// TODO: Error handle
        cleanMenu();
        return;
    }

    bool exit_menu = false;
    while (!exit_menu) {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT) {
            exit_menu = true;
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_SPACE:
                    exit_menu = true;
                    break;
            }
        }

        /* Use TTF. */
        SDL_SetRenderDrawColor(_menu_renderer.get(), 0x1E, 0x1E, 0x1E, 0xFF);
        SDL_RenderClear(_menu_renderer.get());
        int w, h;
        TTF_SizeText(font, _title.front().c_str(), &w, &h);
        int text_position = COMMON_WINDOW_WIDTH/2 - w/2;
        int h_position = 0;
        for(auto title : _title) {
                render_text(_menu_renderer.get(), text_position, h_position, title.c_str(), font, &rect, &color);
                h_position += h;
        }
        render_text(_menu_renderer.get(), text_position, rect.y + rect.h + 100, " ", font, &rect, &color);
        for(auto instruction : _instructions) {
                render_text(_menu_renderer.get(), 0, rect.y + rect.h, instruction.c_str(), font, &rect, &color);
        }
        SDL_RenderPresent(_menu_renderer.get());
        SDL_Delay(10);
    }
    cleanMenu();
}


void Menu::render_text(SDL_Renderer *renderer, int x, int y, const char *text, TTF_Font *font, SDL_Rect *rect, SDL_Color *color) {
    SDL_Surface *surface;
    SDL_Texture *texture;

    surface = TTF_RenderText_Solid(font, text, *color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    rect->x = x;
    rect->y = y;
    rect->w = surface->w;
    rect->h = surface->h;

    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, rect);
    SDL_DestroyTexture(texture);
}


void Menu::cleanMenu() {
    TTF_Quit();
    //SDL_DestroyRenderer(_menu_renderer.get());
    //SDL_DestroyWindow(_menu_window.get());
    SDL_Quit();
    SDL_Delay(200);
}