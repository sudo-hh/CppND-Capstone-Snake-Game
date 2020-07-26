#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <memory>
#include <SDL2/SDL.h>

#include "snake.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);

  void render(Snake const snake, SDL_Point const &food);

// Template to set the description of the game window
  template <class T1, class T2>
  void updateWindowTitle(T1 score, T2 fps) {
      std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
      SDL_SetWindowTitle(sdl_window.get(), title.c_str());
  }

  //SDL_Renderer* getSDLrender() { return this->sdl_renderer.get(); }

 private:

  // Unique pointers, specifying the corresponding destructors
  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> sdl_window;
  std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> sdl_renderer;

  std::size_t screen_width;
  std::size_t screen_height;
  std::size_t grid_width;
  std::size_t grid_height;
};

#endif