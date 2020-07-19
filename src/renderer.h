#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <memory>
#include "SDL.h"
#include "snake.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();
  Renderer(const Renderer &source) = delete; // Copy will be forbidden
  Renderer &operator=(const Renderer &source) = delete; // Copy will be forbidden
  Renderer(Renderer &&source); // Move constructor
  Renderer &operator=(Renderer &&source); // Move assignment operator

  void Render(Snake const snake, SDL_Point const &food);
  void UpdateWindowTitle(int score, int fps);

 private:
  //std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> sdl_window;
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  std::size_t screen_width;
  std::size_t screen_height;
  std::size_t grid_width;
  std::size_t grid_height;
};

#endif