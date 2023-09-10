/*
This program is a simple platformer game where the player controls a zombie that jumps on platforms to score points.
The player loses if the zombie falls off the screen.
The game starts with a start menu, where the player can start the game, view the guide, or exit the game.
The player can control the zombie using the left and right arrow keys.
The player can jump on the platforms to score points.
The player loses if the zombie falls off the screen.
If the player loses, the game over screen is shown, where the player can restart the game or exit.
The game is developed using SFML.

INTE 11223 - PROGRAMMING CONCEPTS
The game is developed by _Team 17.
IM/2021/088 – INDUWARA S.M.P.N.
IM/2021/087 – NIMSHAN K.P.W.N.
IM/2021/036 - SOMARATHNA W.M.B.T.
IM/2021/035 - SAMPATH R.L.L.T.
*/

#include <SFML/Graphics.hpp>
#include <iostream>

// The point struct is used to store the x and y coordinates of the platforms.
struct point {
    int x, y;
};


int main() {

    // Create a window with a size of 400x533 pixels and a title.
    sf::RenderWindow app(sf::VideoMode(400, 533), "Zombie Jumper v1.4.0");

    //Limit the framerate to 60 frames per second.
    //To achieve a steady frame rate and to keep the program from operating too fast on high-performance platforms.
    app.setFramerateLimit(60);


    // Load the textures from the files.
    sf::Texture background, 
                platform, 
                zombie, 
                startMenuBackground, 
                startButtonTexture,
                exitButtonTexture, 
                guideWindowBackgroundTexture, 
                guideButtonTexture,
                backToMenuButtonTexture, 
                endGameScreen, 
                restartButtonTexture;


    // If the textures fail to load, print an error message and return 1.
    // The program will not run if the textures fail to load.
    if (!background.loadFromFile("images/background.png") ||
        !platform.loadFromFile("images/platform.png") ||
        !zombie.loadFromFile("images/zombie.png") ||
        !startMenuBackground.loadFromFile("images/start_menu_background.png") ||
        !startButtonTexture.loadFromFile("images/start_button.png") ||
        !exitButtonTexture.loadFromFile("images/exit_button.png") ||
        !guideWindowBackgroundTexture.loadFromFile("images/guidewindowbg.png") ||
        !guideButtonTexture.loadFromFile("images/guide.png") ||
        !backToMenuButtonTexture.loadFromFile("images/backtomenu.png") ||
        !endGameScreen.loadFromFile("images/end_game_screen.png") ||
        !restartButtonTexture.loadFromFile("images/restart_button.png")) {
        std::cout << "Failed to load textures." << std::endl;
        std::cout << "Game will be closed now." << std::endl;
        return 1;
    }

    // Create sprites from the textures.
    //sprites allows to easily display a texture on a render target.
    sf::Sprite sBackground(background), 
               sPlat(platform), 
               sPers(zombie), 
               sStartMenuBackground(startMenuBackground),
               sStartButton(startButtonTexture), 
               sExitButton(exitButtonTexture), 
               sGuideWindowBackground(guideWindowBackgroundTexture),
               sGuideButton(guideButtonTexture), 
               sBackToMenuButton(backToMenuButtonTexture), 
               sEndGameScreen(endGameScreen),
               sRestartButton(restartButtonTexture);
  
    //getLocalBounds() returns the bounds of the sprite in the local coordinates of the sprite.
    sf::FloatRect startButtonBounds = sStartButton.getLocalBounds(),
        guideButtonBounds = sGuideButton.getLocalBounds(),
        exitButtonBounds = sExitButton.getLocalBounds(),
        backToMenuButtonBounds = sBackToMenuButton.getLocalBounds(),
        restartButtonBounds = sRestartButton.getLocalBounds();


        // Set the positions of the sprites.
        sStartButton.setPosition(200 - startButtonBounds.width / 2, 360);
        sGuideButton.setPosition(200 - guideButtonBounds.width / 2, 410);
        sExitButton.setPosition(200 - exitButtonBounds.width / 2, 460);
        sBackToMenuButton.setPosition(200 - backToMenuButtonBounds.width / 2, 410);
        sRestartButton.setPosition(200 - restartButtonBounds.width / 2, 410);


// Initialize the positions of the first 10 platforms with random values.
// The platforms are represented by a structure with x and y coordinates.
// The x coordinate is the horizontal position of the platform in between 0 and 400(Window Width).
// The y coordinate is the vertical position of the platform in between 0 and 533(Window Height).

    // The platforms are stored in an array of 10 elements.
    point plat[10];

    // The platforms are initialized with random values.
    //rand() is a function that generates a random number.
    for (int i = 0; i < 10; i++) {
        plat[i].x = rand() % 400;
        plat[i].y = rand() % 533;
    }

    // Initialize the position of the player.
    int x = 100, y = 100, h = 200;

    // Initialize the speed of the player.
    float dx = 0, dy = 0;
    // Initialize the score.
    int score = 0;


// Define game states
// Create a list of game states. This is used to determine what to draw on the screen.

    enum GameState { MENU, GAMEPLAY, GAME_OVER, GUIDE };
    GameState gameState = MENU;


    // The main loop of the program.
    while (app.isOpen()) {

        // Create an event to handle events.
        sf::Event e;
        while (app.pollEvent(e)) {
            // If the window is closed, close the window.
            if (e.type == sf::Event::Closed)
                app.close();

            // If the mouse is clicked, check if the mouse is clicked on a button.
            if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
                // If the mouse is clicked on a button, change the game state.
                // The game state determines what to draw on the screen.
                // Check if the game state is MENU.

                if (gameState == MENU) {
                    if (sStartButton.getGlobalBounds().contains(e.mouseButton.x, e.mouseButton.y)) {
                        //change the game state to GAMEPLAY.
                        gameState = GAMEPLAY;
                        x = 100;//initialize the  x position of the player.
                        y = 100;//initialize the y position of the player.
                        dx = 0;//initialize the x speed of the player.
                        dy = 0;//initialize the y speed of the player.
                        score = 0;//initialize the score.
                        //initialize the positions of the first 10 platforms with random values.
                        for (int i = 0; i < 10; i++) {
                            plat[i].x = rand() % 400;
                            plat[i].y = rand() % 533;
                        }
                    }
                    // If the mouse is clicked on the exit button, close the window.
                    else if (sExitButton.getGlobalBounds().contains(e.mouseButton.x, e.mouseButton.y)) {
                        app.close();
                    }

                    // If the mouse is clicked on the guide button, change the game state to GUIDE.
                    else if (sGuideButton.getGlobalBounds().contains(e.mouseButton.x, e.mouseButton.y)) {
                        gameState = GUIDE;
                    }
                }

                else if (gameState == GAME_OVER) {
                    // If the mouse is clicked on a button, change the game state.
                    if (sRestartButton.getGlobalBounds().contains(e.mouseButton.x, e.mouseButton.y)) {

                        //change the game state to GAMEPLAY.
                        gameState = GAMEPLAY;
                        x = 100;//initialize the  x position of the player.
                        y = 100;//initialize the y position of the player.
                        dx = 0;//initialize the x speed of the player.
                        dy = 0;//initialize the y speed of the player.
                        score = 0;//initialize the score.

                        for (int i = 0; i < 10; i++) {
                            //initialize the positions of the first 10 platforms with random values.
                            plat[i].x = rand() % 400;
                            plat[i].y = rand() % 533;
                        }
                    }
                    // If the mouse is clicked on the exit button, close the window.
                    else if (sExitButton.getGlobalBounds().contains(e.mouseButton.x, e.mouseButton.y)) {
                        app.close();
                    }
                }

                else if (gameState == GUIDE) {
                    // If the mouse is clicked on the back to menu button, change the game state to MENU.
                    if (sBackToMenuButton.getGlobalBounds().contains(e.mouseButton.x, e.mouseButton.y)) {

                        //change the game state to MENU.
                        gameState = MENU;
                    }
                }
            }
        }

        if (gameState == MENU) {
            // If the game state is MENU, draw the start menu.
            app.draw(sStartMenuBackground);
            app.draw(sStartButton);
            app.draw(sExitButton);
            app.draw(sGuideButton);
        }

        else if (gameState == GUIDE) {
            // If the game state is GUIDE, draw the guide.
            app.draw(sGuideWindowBackground);
            app.draw(sBackToMenuButton);

            // Create a text to display the guide.
            sf::Font font;
            font.loadFromFile("arial.ttf");
            sf::Text guideText;
            guideText.setFont(font);
            guideText.setString(
                "Welcome to Zombie Jumper!\n\n"


                "Instructions:\n"

                "- Use the arrow keys to move the character\n"

                "   left and right.\n\n"


                "- Jump on the platforms to score points.\n\n"


                "- Don't fall off the screen!\n\n"


                "           Good luck and have fun!\n\n"


                "______________________________________\n\n"


                "                   _developed by team 17\n"

                "______________________________________");

            guideText.setCharacterSize(16);
            guideText.setFillColor(sf::Color::White);
            guideText.setPosition(40, 60);
            app.draw(guideText);
        }

        else if (gameState == GAMEPLAY) {
            // If the game state is GAMEPLAY, draw the game.

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {

                // If the right arrow key is pressed, move the player to the right.
                x += 2;//increase the x position of the player.

                //if the player goes off the screen, move the player to the left side of the screen.
                if (x > 400)
                    x = -sPers.getLocalBounds().width;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                // If the left arrow key is pressed, move the player to the left.
                x -= 2;//decrease the x position of the player.

                //if the player goes off the screen, move the player to the right side of the screen.
                if (x < -sPers.getLocalBounds().width)
                    x = 400;
            }

            dy += 0.2;//increase the y speed of the player.
            y += dy;//increase the y position of the player.

            if (y > 533) {
                // If the player falls off the screen, change the game state to GAME_OVER.
                gameState = GAME_OVER;
            }

            // If the player jumps on a platform, increase the score and jump.
            if (y < h) {
                for (int i = 0; i < 10; i++) {
                    y = h;

                    //move the platforms down.
                    plat[i].y = plat[i].y - dy;
                    if (plat[i].y > 533) {

                        //if the platform goes off the screen, move the platform to the top of the screen.
                        plat[i].y = 0;
                        plat[i].x = rand() % 400;
                     
                    }
                }
            }

            // Check if the player jumps on a platform.
            for (int i = 0; i < 10; i++) {
                if ((x + 50 > plat[i].x) && (x + 20 < plat[i].x + 68) && (y + 70 > plat[i].y) && (y + 70 < plat[i].y + 14) && (dy > 0)) {
                    // If the player jumps on a platform, jump.
                    dy = -10;
                    // Increase the score.
                    score += 1;
                }
            }


            // Draw the game. 
            sPers.setPosition(x, y);
            app.draw(sBackground);
            app.draw(sPers);

            // Draw the platforms.
            for (int i = 0; i < 10; i++) {
                // Set the position of the platform.
                sPlat.setPosition(plat[i].x, plat[i].y);
                app.draw(sPlat);
            }

            // Draw the score.
            sf::Font font;
            font.loadFromFile("arial.ttf");
            sf::Text scoreText;
            scoreText.setFont(font);
            scoreText.setString("Score: " + std::to_string(score));
            scoreText.setCharacterSize(20);
            scoreText.setFillColor(sf::Color::White);
            scoreText.setPosition(10, 10);
            app.draw(scoreText);
        }

        // If the game state is GAME_OVER, draw the game over screen.
        else if (gameState == GAME_OVER) {
 
            app.draw(sEndGameScreen);
            app.draw(sRestartButton);
            app.draw(sExitButton);

            // Draw the score.
            sf::Font font;
            font.loadFromFile("arial.ttf");
            sf::Text scoreText;
            scoreText.setFont(font);
            scoreText.setString("Final Score: " + std::to_string(score));
            scoreText.setCharacterSize(20);
            scoreText.setFillColor(sf::Color::White);
            scoreText.setPosition(10, 10);
            app.draw(scoreText);
        }

        // Display the window.
        app.display();
    }

    // Exit the program.
    return 0;
}