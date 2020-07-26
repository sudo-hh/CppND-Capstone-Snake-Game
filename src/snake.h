#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <SDL2/SDL.h>

#define MAX_SPEED 0.140f

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2),
        _maxSpeed(MAX_SPEED) { }

  void update();

  void growBody();
  bool snakeCell(int x, int y);
  float getMaxSpeed() { return this->_maxSpeed; };

  Direction direction = Direction::kUp;

  float speed{0.01f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

  struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
  };

  void setCurrentColor(Color newColor);
  Color getColor() const { return currentColor; }

 private:
  Color currentColor;
  void updateHead();
  void updateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false};
  int grid_width;
  int grid_height;
  float _maxSpeed;
};

#endif