
---

# Game Documentation

## Table of Contents

1. Introduction
2. Prerequisites
3. Code Overview
   - Main Function
   - Game States
   - Event Handling
   - Game Logic
   - Rendering
4. Usage
5. Conclusion
5. Team members

## 1. Introduction

This documentation explains the structure and functionality of the "Zombie Jumper" game code. The game is developed in C++ using the Simple and Fast Multimedia Library (SFML) for graphics and event handling. It consists of a main menu, gameplay, game over screen, and a guide.

## 2. Prerequisites

Before running the code, make sure you have the following prerequisites installed:

- C++ compiler (e.g., g++)
- SFML library

## 3. Code Overview

The code can be divided into several key components:

### Main Function

- The `main()` function is the entry point of the program.
- It initializes the random number generator and creates an SFML window.
- Loads game textures and creates sprite objects.
- Defines game states and enters the game loop.

### Game States

- The code uses an enumeration `GameState` to manage different game states:
  - `MENU`: Displays the main menu.
  - `GUIDE`: Shows the game guide.
  - `GAMEPLAY`: Manages the main gameplay.
  - `GAME_OVER`: Displays the game over screen.

### Event Handling

- The code uses SFML's event handling to respond to user interactions.
- It handles mouse clicks to navigate between menu screens and exit the game.

### Game Logic

- In the `GAMEPLAY` state:
  - Player character (zombie) movement is controlled using arrow keys.
  - The player jumps on platforms to score points.
  - The player loses when falling off the screen.
  - Platforms are randomly generated and moved downward.
  - Collisions between the player and platforms are checked.

### Rendering

- The code uses SFML to render game elements such as background, player, platforms, buttons, and score.
- Text is displayed on the screen to show the player's score.
- Different screens (main menu, guide, game over) are displayed based on the game state.

## 4. Usage

To run the "Zombie Jumper" game, follow these steps:

1. Make sure you have the required prerequisites installed (C++ compiler and SFML library).
2. Compile the code using a C++ compiler, linking against the SFML library. For example:

   ```shell
   g++ main.cpp -o ZombieJumper -lsfml-graphics -lsfml-window -lsfml-system
   ```
3. Execute the compiled binary:

   ```shell
   ./ZombieJumper
   ```
4. The game window should open, allowing you to interact with the main menu and play the game.

## 5. Conclusion

In summary, "Zombie Jumper" is a simple 2D game developed in C++ using the SFML library. It features a main menu, gameplay, game over screen, and a guide. Players control a zombie character to jump on randomly generated platforms and score points. This documentation provides an overview of the code's structure, key components, and how to run the game.


## 6. Team members 
- IM/2021/088 – INDUWARA S.M.P.N.
- IM/2021/087 – NIMSHAN K.P.W.N.
- IM/2021/036 - SOMARATHNA W.M.B.T.
- IM/2021/035 - SAMPATH R.L.L.T.
