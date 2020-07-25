#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define COMMON_COLOR_MAX 255
#define COMMON_WINDOW_WIDTH 640
#define COMMON_WINDOW_HEIGHT (COMMON_WINDOW_WIDTH)
#define MAX_STRING_LEN 4

class Menu {
    public:
        Menu();
        void ShowMenu();

    private:
        void render_text(SDL_Renderer *renderer, int x, int y, const char *text, TTF_Font *font, SDL_Rect *rect, SDL_Color *color);
        void cleanMenu();

        SDL_Color color;
        SDL_Event event;
        SDL_Rect rect;
        std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> _menu_window;
        std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> _menu_renderer;

        std::vector<std::string> _title;
        static const std::string _title_1;
        static const std::string _title_2;
        static const std::string _title_3;

        std::vector<std::string> _instructions;
        static const std::string _instructions_1;
        static const std::string _instructions_2;
        static const std::string _instructions_3;
        static const std::string _instructions_4;
};