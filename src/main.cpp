#include <iostream>
#include<memory>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "SDL_ttf.h"
#include "menu.h"

int main() {
  constexpr std::size_t kFramesPerSecond{240};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  //Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Menu menu;
  menu.ShowMenu();
  std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;

  Game game(kGridWidth, kGridHeight, controller, std::move(renderer), kMsPerFrame);
  //std::thread t(&Game::Run, &game);
  //t.join();
  game.Run();
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}