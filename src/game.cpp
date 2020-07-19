#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height, Controller controller, Renderer renderer, std::size_t const target_frame_duration)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)),
      _controller(controller),
      _renderer(std::move(renderer)),
      _target_frame_duration(target_frame_duration),
       score(0)
{
  PlaceFood();
}

void Game::Run() {

  std::promise<void> prms;
  std::future<void> future = prms.get_future();
  //std::thread t(&Game::MoveSnake, this, std::move(prms));

  //future.get();
  //std::cout << "Thread terminated!" << std::endl;

  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start(0);
  Uint32 frame_end(0);
  Uint32 frame_duration(0);
  int frame_count(0);
  bool running = true;
  std::cout << "Before While, game.cpp:36" << std::endl;
  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    _controller.HandleInput(running, snake);
    //std::cout << "After handle, game.cpp:42" << std::endl;
    Update();
    //std::cout << "After update, game.cpp:44" << std::endl;
    _renderer.Render(snake, food);
    //std::cout << "After render, game.cpp:46" << std::endl;

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      _renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < _target_frame_duration) {
      SDL_Delay(_target_frame_duration - frame_duration);
    }
  }

}

void Game::MoveSnake(std::promise<void> && prms) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start(0);
  Uint32 frame_end(0);
  Uint32 frame_duration(0);
  int frame_count(0);
  bool running = true;
  std::cout << "Before While, game.cpp:36" << std::endl;
  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    _controller.HandleInput(running, snake);
    //std::cout << "After handle, game.cpp:42" << std::endl;
    Update();
    //std::cout << "After update, game.cpp:44" << std::endl;
    _renderer.Render(snake, food);
    //std::cout << "After render, game.cpp:46" << std::endl;

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      _renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < _target_frame_duration) {
      SDL_Delay(_target_frame_duration - frame_duration);
    }
  }
  prms.set_value();
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      //std::cout << "X: " << x << "\nY: " << y << std::endl;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    std::cout << "Food eaten!" << std::endl;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    if(snake.getMaxSpeed() > snake.speed) {
      snake.speed += 0.005;
    }
    std::cout << "Current speed: " << snake.speed << std::endl;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }