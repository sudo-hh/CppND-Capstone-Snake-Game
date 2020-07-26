#include <iostream>

#include "game.h"

// Game constructor using initialization list
Game::Game(std::size_t grid_width, std::size_t grid_height, Controller controller, std::unique_ptr<Renderer> renderer, std::size_t const target_frame_duration)
    : _snake(grid_width, grid_height),
      _engine(_dev()),
      _random_w(0, static_cast<int>(grid_width - 1)),
      _random_h(0, static_cast<int>(grid_height - 1)),
      _controller(controller),
      _renderer(std::move(renderer)),
      _target_frame_duration(target_frame_duration),
      _score(0),
      _ready(false),
      _processed(false)
{ }

// Place the first food and calls MoveSnake
void Game::run() {
  std::promise<void> prms;
  std::future<void> future = prms.get_future();
  std::thread t(&Game::placeFood, this, std::move(prms));
  future.get();
  t.join();
  moveSnake();
}

void Game::moveSnake() {
  uint32_t title_timestamp = SDL_GetTicks();
  uint32_t frame_start(0);
  uint32_t frame_end(0);
  uint32_t frame_duration(0);
  int frame_count(0);
  bool running = true;
  bool changeColor = false;

  Snake::Color newColor;
  std::thread t;
  std::future<Snake::Color> future_color;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    _controller.handleInput(running, _snake);

    if(update(running)) {
      changeColor = true;

      // Generate the next color
      std::promise<Snake::Color> prms;
      future_color = prms.get_future();
      t = std::thread(&Game::generateColor, this, std::move(prms));

      std::lock_guard<std::mutex> lk(_snakeMutex);
      _ready = true;
      _cond.notify_one();
    }

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      _renderer.get()->updateWindowTitle<int, int>(_score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    if(changeColor) {

      // Get the previously generated color

      // Wait for condition signaling from "GenerateColor"
      std::unique_lock<std::mutex> lk(_snakeMutex);
      _cond.wait(lk, [this]{return _processed;});

      // Ready! Now get the result
      Snake::Color newColor = future_color.get();

      // Thread barrier
      t.join();

      // Set new snake color
      _snake.setCurrentColor(newColor);
      changeColor = false;
    }

    _renderer.get()->render(_snake, _food);

    // Reset signaling
    _ready = false;
    _processed = false;

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < _target_frame_duration) {
      SDL_Delay(_target_frame_duration - frame_duration);
    }
  }

  // For a nicer transition after the game is over
  if(!_snake.alive){
    SDL_Delay(1500);
  }

  SDL_Quit();
  SDL_Delay(500);
}


// Lauched as a thread, generated a new snake color
void Game::generateColor(std::promise<Snake::Color> &&prms) {
  Snake::Color newColor;
  std::uniform_int_distribution<uint8_t> random_color;

  // Wait for condition signaling...
  std::unique_lock<std::mutex> lck(_snakeMutex);
  _cond.wait(lck, [this]{return _ready;});

  newColor.r = random_color(_engine);
  newColor.g = random_color(_engine);
  newColor.b = random_color(_engine);
  newColor.a = random_color(_engine);

  // Notify the readiness of the data
  _processed = true;
  lck.unlock();
  _cond.notify_one();
  prms.set_value(newColor);
}


// Places a new "food" in the screen
void Game::placeFood(std::promise<void> &&prms) {
  int x, y;
  bool food_ready = false;
  while (!food_ready) {
    x = _random_w(_engine);
    y = _random_h(_engine);

    std::unique_lock<std::mutex> lck(_snakeMutex);

    // Check that the location is not occupied by a snake item before placing food
    if (!_snake.snakeCell(x, y)) {
      _food.x = x;
      _food.y = y;
      food_ready = true;
    }
  }
  prms.set_value();
}

// Update the current scene
bool Game::update(bool &running) {

  // If dead, game over
  if (!_snake.alive) {
    running = false;
    return false;
  }

  _snake.update();
  int new_x = static_cast<int>(_snake.head_x);
  int new_y = static_cast<int>(_snake.head_y);

  // Check if there's food over here
  if (_food.x == new_x && _food.y == new_y) {
    std::promise<void> prms;
    std::future<void> fut = prms.get_future();
    std::thread t(&Game::placeFood, this, std::move(prms));
    _score++;
    std::cout << "Food eaten!" << std::endl;

    // Grow snake and increase speed.
    _snake.growBody();
    if(_snake.getMaxSpeed() > _snake.speed) { _snake.speed += 0.005; }
    std::cout << "Current speed: " << _snake.speed << std::endl;

    // Wait until PlaceFood thread has finished
    fut.get();
    t.join();

    return true;
  } else { return false; }
}

