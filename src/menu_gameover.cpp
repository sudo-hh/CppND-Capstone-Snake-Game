#include "menu_gameover.h"
#include <iostream>

MenuGameOver::MenuGameOver() {

    color.r = COMMON_COLOR_MAX;
    color.g = COMMON_COLOR_MAX;
    color.b = COMMON_COLOR_MAX;
    color.a = COMMON_COLOR_MAX;
}
void MenuGameOver::showMenu() {}

void MenuGameOver::showMenu(int newScore, std::vector<int> score_list)
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

        std::string best_score = "All-time score: " + std::to_string(score_list.back());
        render_text(_menu_renderer.get(), 0, 0, best_score.c_str(), font, &rect, &color);

        std::string new_score = "Your score: " + std::to_string(newScore);
        render_text(_menu_renderer.get(), 0, rect.y + rect.h, new_score.c_str(), font, &rect, &color);

        SDL_RenderPresent(_menu_renderer.get());
        SDL_Delay(10);
    }
}
