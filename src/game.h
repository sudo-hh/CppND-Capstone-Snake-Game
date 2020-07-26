#ifndef GAME_H
#define GAME_H

#include <random>
#include <future>
#include <SDL2/SDL.h>
#include <mutex>

#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, Controller controller, std::unique_ptr<Renderer> renderer, std::size_t const target_frame_duration);
  void run();
  int getScore() const { return _score; }
  int getSize() const { return _snake.size; }

 private:
  Snake _snake;
  SDL_Point _food;

  std::random_device _dev;
  std::mt19937 _engine;
  std::uniform_int_distribution<int> _random_w;
  std::uniform_int_distribution<int> _random_h;
  Controller _controller;
  std::shared_ptr<Renderer> _renderer;
  std::size_t _target_frame_duration;

  std::mutex _snakeMutex;
  std::condition_variable _cond;

  bool _ready;
  bool _processed;

  int _score;
  void moveSnake();
  void placeFood(std::promise<void> &&prms);
  void generateColor(std::promise<Snake::Color> &&prms);
  bool update(bool &running);
};

#endif
