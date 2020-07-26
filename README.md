# CPPND: Capstone Project: Snake Game

This is the capstone project for Udacity's C++ Nanodegree [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* SDL_ttf (TrueType font rendering library)
  * Ubuntu: `sudo apt-get install -y libsdl2-ttf-dev`
  * Windows: [SDL_ttf](https://www.libsdl.org/projects/SDL_ttf/)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.


## Rubric points addressed

### Loops, Functions, I/O
| Rubric point  | Location |
| ------------- | ------------- |
| The project demonstrates an understanding of C++ functions and control structures.  |   Yes. Along the whole project.
| The project reads data from a file and process the data, or the program writes data to a file.  | [scores](src/scores.cpp)
| The project accepts user input and processes the input.  |   [Controller::handleInput](src/controller.cpp)

### Object Oriented Programming
| Rubric point  | Location |
| ------------- | ------------- |
| The project uses Object Oriented Programming techniques.  |   Yes. Along the whole project.
| Classes use appropriate access specifiers for class members. | Yes. E.g. [snake.h:42, 43](src/snake.cpp)
| Class constructors utilize member initialization lists. | Yes. E.g. [game.cpp:6](src/game.cpp)
| Classes abstract implementation details from their interfaces. | Yes. Along the whole project.
| Classes encapsulate behavior. | Yes.  Along the whole project. E.g. [scores.h](src/scores.h)
| Classes follow an appropriate inheritance hierarchy. | Yes. [menu_instructions.h](src/menu_instructions.h) and [menu_gameover.h](src/menu_gameover.h) are derived classes from [menu.h](src/menu.h)
| Overloaded functions allow the same function to operate on different parameters. | Yes. E.g. [menu_gameover.h:12, 13](src/menu_gameover.h)
| Derived class functions override virtual base class functions. | Yes. E.g. [menu_gameover.cpp:13](src/menu_gameover.cpp) and [menu_instructions.cpp:31](src/menu_instructions.cpp)
| Templates generalize functions in the project. | Yes. E.g. [renderer.h:18](src/renderer.h)

