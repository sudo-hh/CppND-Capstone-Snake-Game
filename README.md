# CPPND: Capstone Project: Snake Game

This is the capstone project for Udacity's C++ Nanodegree [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

In this version, you will have first some basic instructions before starting the game.

Once in the game, you will notice that our crazy snake will randomly change its color everytime a fruit is eaten.

The color generation for the next event happens in a thread, which is synchronized by means of an unique mutex and a condition variable.

If your snake eats itself, the game is over. You'll notice quite easy.

Finally, you will get information about the maximun score registered and the score you just got.

I hope you like it.

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

### Memory Management
| Rubric point  | Location |
| ------------- | ------------- |
| The project makes use of references in function declarations.  |  Yes. E.g. [game.h:42](src/game.h) and [menu_instructions.cpp:69](src/menu_instructions.cpp)
| The project uses destructors appropriately. | Yes. E.g. [menu.cpp:22](src/menu.cpp) is called automatically when menus are out of scope at the end of the game. Also the destructors for the SDL_render and SDL_window are addressed in [render.h:28](src/render.h)
| The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate. | Yes. Along the whole project. See [main file](src/main.cpp) for example.
| The project follows the Rule of 5. | Yes. E.g: [menu.h:18-21](src/menu.h)
| The project uses move semantics to move data, instead of copying it, where possible. | Yes. E.g. [main.cpp:28](src/main.cpp) and many more...
| The project uses smart pointers instead of raw pointers. | Yes. E.g. [main.cpp:25](src/main.cpp), [renderer.h:29-30](src/renderer.h). For some specific cases, a row pointer is used for compatibility with the SDL library, however no between user scopes.

### Concurrency
| Rubric point  | Location |
| ------------- | ------------- |
| The project uses multithreading. | Yes. E.g. [game.cpp:23,54,177](src/game.cpp)
| A promise and future is used in the project. | Yes. E.g. [game.cpp:21,52,84,175](src/game.cpp)
| A mutex or lock is used in the project. | Yes. E.g. [game.cpp:56,80,124...](src/game.cpp)
| A condition variable is used in the project. | Yes. E.g. [game.cpp:58,81,125,135](src/game.cpp) for sync between moveSnake() and generateColor()
