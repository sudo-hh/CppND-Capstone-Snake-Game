#ifndef GAME_H
#define GAME_H

#include <random>
#include <future>
#include <SDL.h>

#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, Controller controller, std::unique_ptr<Renderer> renderer, std::size_t const target_frame_duration);
  void Run();
  int GetScore() const;
  int GetSize() const;

 private:
  Snake snake;
  SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
  Controller _controller;
  std::shared_ptr<Renderer> _renderer;
  std::size_t _target_frame_duration;

  int score;
  void MoveSnake();
  void PlaceFood();
  void Update();
};

#endif