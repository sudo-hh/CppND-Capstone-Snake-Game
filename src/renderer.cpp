#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height),
      sdl_window(nullptr, SDL_DestroyWindow),
      sdl_renderer(nullptr, SDL_DestroyRenderer) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window.reset(SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN));

  if (nullptr == sdl_window.get()) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer.reset(SDL_CreateRenderer(sdl_window.get(), -1, SDL_RENDERER_ACCELERATED));
  if (nullptr == sdl_renderer.get()) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}
/*
Renderer::~Renderer() {
  if(nullptr != sdl_renderer && nullptr != sdl_window.get()) {
    std::cout << "~Renderer()" << this << std::endl;
    SDL_DestroyRenderer(sdl_renderer);
    SDL_DestroyWindow(sdl_window.get());
    SDL_Quit();
  }
}
/*
Renderer::Renderer(Renderer &&source) {
    std::cout << "MOVING (c’tor) Renderer instance " << &source << " to Renderer instance " << this << std::endl;

    std::cout << "source.sdl_window: " << source.sdl_window.get() << std::endl;
    std::cout << "source.sdl_renderer: " << source.sdl_renderer << std::endl;

    this->sdl_window = std::move(source.sdl_window);
    this->sdl_renderer = source.sdl_renderer;

    //source.sdl_window = nullptr;
    source.sdl_renderer = nullptr;

    this->screen_width = source.screen_width;
    this->screen_height = source.screen_height;
    this->grid_width = source.grid_width;
    this->grid_height = source.grid_height;

    source.screen_width = 0;
    source.screen_height = 0;
    source.grid_width = 0;
    source.grid_height = 0;

    std::cout << "this->sdl_window: " << this->sdl_window.get() << std::endl;
    std::cout << "this->sdl_renderer: " << this->sdl_renderer << std::endl;
}

Renderer &Renderer::operator=(Renderer &&source) {
    std::cout << "MOVING (assign) ChatBot instance " << &source << " to ChatBot instance " << this << std::endl;
    if (this == &source) {
        return *this;
    }

    if(this->sdl_window.get() != nullptr) {
      //SDL_DestroyWindow(sdl_window);
      std::cout << "SDL_DestroyWindow(sdl_window); // moving..." << std::endl;
    }

    if(this->sdl_renderer != nullptr) {
      SDL_DestroyRenderer(sdl_renderer);
      std::cout << "SDL_DestroyRenderer(sdl_renderer); // moving..." << std::endl;
    }

    this->sdl_window = std::move(source.sdl_window);
    this->sdl_renderer = source.sdl_renderer;

    //source.sdl_window = nullptr;
    source.sdl_renderer = nullptr;

    this->screen_width = source.screen_width;
    this->screen_height = source.screen_height;
    this->grid_width = source.grid_width;
    this->grid_height = source.grid_height;

    source.screen_width = 0;
    source.screen_height = 0;
    source.grid_width = 0;
    source.grid_height = 0;

    return *this;
}
*/
void Renderer::Render(Snake const snake, SDL_Point const &food) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer.get(), 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer.get());

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer.get(), 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer.get(), &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer.get(), &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer.get(), 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer.get(), 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer.get(), &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer.get());
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window.get(), title.c_str());
}
