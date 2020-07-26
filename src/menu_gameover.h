#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <stdlib.h>
#include <string>

#include "menu.h"

class MenuGameOver : public Menu {
    public:
        MenuGameOver();
        void showMenu();
        void showMenu(int newScore, std::vector<int> score_list);
};

#endif
