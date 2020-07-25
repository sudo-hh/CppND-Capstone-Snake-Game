#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

void Controller::ChangeDirection(Snake &snake, Snake::Direction input, Snake::Direction opposite) const {
  if (snake.direction != opposite || snake.size == 1) snake.direction = input;
}

void Controller::HandleInput(bool &running, Snake &snake) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(snake, Snake::Direction::kUp,
                          Snake::Direction::kDown);
          break;

        case SDLK_DOWN:
          ChangeDirection(snake, Snake::Direction::kDown,
                          Snake::Direction::kUp);
          break;

        case SDLK_LEFT:
          ChangeDirection(snake, Snake::Direction::kLeft,
                          Snake::Direction::kRight);
          break;

        case SDLK_RIGHT:
          ChangeDirection(snake, Snake::Direction::kRight,
                          Snake::Direction::kLeft);
          break;

        case SDLK_ESCAPE:
          running = false;
          break;
      }
    }
  }
}
/*
void Controller::MenuController() const {
  SDL_Event event;
  while(SDL_PollEvent(&event))
  {
    switch(event.type)
    {
      case SDL_QUIT:
        SDL_FreeSurface(menus[0]);
        SDL_FreeSurface(menus[1]);
        return 1;
      case SDL_KEYDOWN:
        if(event.key.keysym.sym == SDLK_ESCAPE)
        {
          SDL_FreeSurface(menus[0]);
          SDL_FreeSurface(menus[1]);
          //return 0;
        }
    }
  }
}
*/