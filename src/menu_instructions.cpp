#include "menu_instructions.h"
#include <iostream>

MenuInstr::MenuInstr() {

        std::string _title_1 = "***************************************";
        std::string _title_2 = "*********The Crazy Snake*********";
        std::string _title_3 = "***************************************";
        std::string _instructions_1 = "To move the snake's direction, use the arrow keys.";
        std::string _instructions_2 = "Once your snake eats a food unit, the speed will increase!";
        std::string _instructions_3 = "If your snake eats itself, the game is over.";
        std::string _instructions_4 = "Press SPACE to continue.";
        std::string _instructions_5 = "During the game, press ESC to quit.";

        _title.push_back(_title_1);
        _title.push_back(_title_2);
        _title.push_back(_title_3);

        _instructions.push_back(_instructions_1);
        _instructions.push_back(_instructions_2);
        _instructions.push_back(_instructions_3);
        _instructions.push_back(_instructions_4);
        _instructions.push_back(_instructions_5);

        color.r = COMMON_COLOR_MAX;
        color.g = COMMON_COLOR_MAX;
        color.b = COMMON_COLOR_MAX;
        color.a = COMMON_COLOR_MAX;
}

void MenuInstr::showMenu()
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
    TTF_Font *font = TTF_OpenFont(font_path.c_str(), 24);
    if (font == NULL) {
        std::cout << "Error: font not found!" << std::endl;
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
                case SDLK_ESCAPE:
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
}
