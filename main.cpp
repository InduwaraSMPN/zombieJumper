// Include the SFML Graphics Library. This is the main header file that contains all the graphics related functions.
#include <SFML/Graphics.hpp>

// Use the sf namespace to simplify the code.
using namespace sf;

// Define a structure to represent a point with x and y coordinates.
struct point {
    int x, y;
};

int main() {

    // Create a window with a size of 400x533 pixels and a title.
    RenderWindow app(VideoMode(400, 533), "Zombie Jumper v1.4.0");

    //Limit the framerate to 60 frames per second.
    //To achieve a steady frame rate and to keep the program from operating too fast on high-performance platforms.
    app.setFramerateLimit(60);

    // Load the textures from the files.
    Texture background,
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

    background.loadFromFile("images/background.png");
    platform.loadFromFile("images/platform.png");
    zombie.loadFromFile("images/zombie.png");
    startMenuBackground.loadFromFile("images/start_menu_background.png");
    startButtonTexture.loadFromFile("images/start_button.png");
    exitButtonTexture.loadFromFile("images/exit_button.png");
    guideWindowBackgroundTexture.loadFromFile("images/guidewindowbg.png");
    guideButtonTexture.loadFromFile("images/guide.png");
    backToMenuButtonTexture.loadFromFile("images/backtomenu.png");
    endGameScreen.loadFromFile("images/end_game_screen.png");
    restartButtonTexture.loadFromFile("images/restart_button.png");

    // Create sprites from the textures.
    //sprites allows to easily display a texture on a render target.
    Sprite  sBackground(background),
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


    // Set the positions of the buttons.
    sf::FloatRect startButtonBounds = sStartButton.getLocalBounds();
    sf::FloatRect guideButtonBounds = sGuideButton.getLocalBounds();
    sf::FloatRect exitButtonBounds = sExitButton.getLocalBounds();
    sf::FloatRect backToMenuButtonBounds = sBackToMenuButton.getLocalBounds();
    sf::FloatRect restartButtonBounds = sRestartButton.getLocalBounds();

    sStartButton.setPosition(200 - startButtonBounds.width / 2, 360);
    sGuideButton.setPosition(200 - guideButtonBounds.width / 2, 410);
    sExitButton.setPosition(200 - exitButtonBounds.width / 2, 460);
    sBackToMenuButton.setPosition(200 - backToMenuButtonBounds.width / 2, 410);
    sRestartButton.setPosition(200 - restartButtonBounds.width / 2, 410);


    // Initialize the positions of the first 10 platforms with random values.
    //The platforms are represented by a structure with x and y coordinates.
    //The x coordinate is the horizontal position of the platform in between 0 and 400(Window Width).
    //The y coordinate is the vertical position of the platform in between 0 and 533(Window Height).
    point plat[10];// Create an array of 10 platforms.


    for (int i = 0; i < 10; i++)
    {
        //rand() is a function that generates a random number.
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
    // Create a list  of game states. This is used to determine what to draw on the screen.
    enum GameState { MENU, GAMEPLAY, GAME_OVER, GUIDE };
    GameState gameState = MENU;


    // Start the game loop.
    while (app.isOpen())
    {   
        // Create an event object to handle events.
        Event e;

        // Check if there is an event.
        while (app.pollEvent(e))
        {
            // Check if the window is closed by the user, and close the application if so.
            if (e.type == Event::Closed)
                app.close();

            // Handle mouse click events
            // Check if the left mouse button is pressed.
            if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left){

                // Check if the game state is MENU.
                if (gameState == MENU){
                    
                    // Check if the mouse is over the start button.
                    if (sStartButton.getGlobalBounds().contains(e.mouseButton.x, e.mouseButton.y)){

                        // Change the game state to GAMEPLAY.
                        gameState = GAMEPLAY;
                        x = 100;// Reset the player's x position.
                        y = 100;// Reset the player's y position.
                        dx = 0;// Reset the player's x speed.
                        dy = 0;// Reset the player's y speed.
                        score = 0;// Reset the score.

                        // Reset the positions of the platforms.
                        for (int i = 0; i < 10; i++){
                            plat[i].x = rand() % 400;
                            plat[i].y = rand() % 533;
                        }
                    }
                    // Check if the mouse is over the exit button.
                    else if (sExitButton.getGlobalBounds().contains(e.mouseButton.x, e.mouseButton.y)){
                        app.close();// Close the application.
                    }

                    // Check if the mouse is over the guide button.
                    else if (sGuideButton.getGlobalBounds().contains(e.mouseButton.x, e.mouseButton.y)){
                        gameState = GUIDE;// Change the game state to GUIDE.
                    }
                }

                // Check if the game state is GAME_OVER.
                else if (gameState == GAME_OVER){

                    // Check if the mouse is over the restart button.
                    if (sRestartButton.getGlobalBounds().contains(e.mouseButton.x, e.mouseButton.y)){
                        // Change the game state to GAMEPLAY.
                        gameState = GAMEPLAY;
                        x = 100;// Reset the player's x position.
                        y = 100;// Reset the player's y position.
                        dx = 0;// Reset the player's x speed.
                        dy = 0;// Reset the player's y speed.
                        score = 0;// Reset the score.

                        // Reset the positions of the platforms.
                        for (int i = 0; i < 10; i++){
                            plat[i].x = rand() % 400;
                            plat[i].y = rand() % 533;
                        }
                    }

                    // Check if the mouse is over the exit button.
                    else if (sExitButton.getGlobalBounds().contains(e.mouseButton.x, e.mouseButton.y)){
                        // Close the application.
                        app.close();
                    }

                }
                // Check if the game state is GUIDE.
                else if (gameState == GUIDE){

                    // Check if the mouse is over the back to menu button.
                    if (sBackToMenuButton.getGlobalBounds().contains(e.mouseButton.x, e.mouseButton.y)){
                        // Change the game state to MENU.
                        gameState = MENU;
                    }
                }
            }
        }



        // Check if the game state is MENU.
        if (gameState == MENU){ 

            // Draw the start menu
            app.draw(sStartMenuBackground);
            app.draw(sStartButton);
            app.draw(sExitButton);
            app.draw(sGuideButton);
        }

        // Check if the game state is GUIDE.
        else if (gameState == GUIDE){

            // Draw the guide window and the back to menu button
            app.draw(sGuideWindowBackground);
            app.draw(sBackToMenuButton);

            // Draw the guidelines text
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

        // Check if the game state is GAMEPLAY.
        else if (gameState == GAMEPLAY){

            // Check if the right arrow key is pressed.
            if (Keyboard::isKeyPressed(Keyboard::Right)){
                x += 2;// Move the player to the right.
                if (x > 400)// Check if the player is out of the screen.
                    x = -sPers.getLocalBounds().width;// Move the player to the left side of the screen.
            }

            // Check if the left arrow key is pressed.
            if (Keyboard::isKeyPressed(Keyboard::Left)){
                x -= 2;// Move the player to the left.
                if (x < -sPers.getLocalBounds().width)// Check if the player is out of the screen.
                    x = 400;// Move the player to the right side of the screen.
            }

            dy += 0.2;// Increase the player's y speed.
            y += dy;// Move the player down(Gravity).


            // Check if the player is out of the screen.
            if (y > 533){
                // Change the game state to GAME_OVER.
                gameState = GAME_OVER;
            }

            // Check if the player is above the middle of the screen.
            if (y < h){

                // Loop through all the platforms.
                for (int i = 0; i < 10; i++){
                    y = h;  // Set the player's y position to the middle of the screen.
                    plat[i].y = plat[i].y - dy;  // Move the platforms down.

                    // Check if the platform is out of the screen.
                    if (plat[i].y > 533) { 
                        plat[i].y = 0; plat[i].x = rand() % 400; 
                    }

                }
            }

            // Loop through all the platforms.
            for (int i = 0; i < 10; i++){

                // Check if the player is on top of the platform.
                // Check if the player is falling.
                if ((x + 50 > plat[i].x) && (x + 20 < plat[i].x + 68) && (y + 70 > plat[i].y) && (y + 70 < plat[i].y + 14) && (dy > 0)){
                    dy = -10;// Make the player jump.
                    score += 1;// Increase the score.
                }
            }

            sPers.setPosition(x, y);// Set the player's position.
            app.draw(sBackground);// Draw the background.
            app.draw(sPers);// Draw the player.


            // Loop through all the platforms.
            for (int i = 0; i < 10; i++){
                sPlat.setPosition(plat[i].x, plat[i].y);// Set the platform's position.
                app.draw(sPlat);// Draw the platform.
            }

            // Draw the score
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

        // Check if the game state is GAME_OVER.
        else if (gameState == GAME_OVER){
            
            // Draw the end game screen
            app.draw(sEndGameScreen);
            app.draw(sRestartButton);
            app.draw(sExitButton);

            // Draw the final score
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

        app.display();// Display the window.
    }

    return 0;
}