#include <iostream>
#include<memory>
#include <fstream>
#include <string>

#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "SDL_ttf.h"
#include "menu_instructions.h"
#include "menu_gameover.h"
#include "scores.h"

int main() {
  constexpr std::size_t kFramesPerSecond{240};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  MenuInstr menu;
  menu.showMenu();

  std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;

  Game game(kGridWidth, kGridHeight, controller, std::move(renderer), kMsPerFrame);

  game.run();

  Scores score;
  score.saveScores(game.getScore());

  std::vector<int> score_list = score.getScores();

  MenuGameOver gameover;
  gameover.showMenu(game.getScore(), score_list);


  std::cout << "Game has terminated successfully!\n";

  return 0;
}