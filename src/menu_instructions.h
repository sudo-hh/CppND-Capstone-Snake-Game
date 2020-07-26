#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdlib.h>
#include <string>

#include "menu.h"

class MenuInstr : public Menu {
    public:
        MenuInstr();
        void showMenu();

    private:
        std::vector<std::string> _title;
        std::string _title_1;
        std::string _title_2;
        std::string _title_3;

        std::vector<std::string> _instructions;
        std::string _instructions_1;
        std::string _instructions_2;
        std::string _instructions_3;
        std::string _instructions_4;
        std::string _instructions_5;
};

#endif
