#include "../include/raylib.h"
#include <vector>
#include <random>
#include <iostream>
#include "snake.h"
#include <string>
#include "tetris.h"
#include "home.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
// const int PIXEL_SIZE = SCREEN_WIDTH*SCREEN_HEIGHT/24000;
const int PIXEL_SIZE = 20;

// check for key presses
void checkKeyPress(char* dir) {}

int main() {

    // Window and Game setup
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "GAMES");
    SetWindowIcon(LoadImage("images/super_smurg.png")); 
    SetTargetFPS(60);
    int frameNum = 1;

    // set up random
    srand(time(NULL));

    // create game objects
    Snake* snake = new Snake(SCREEN_WIDTH, SCREEN_HEIGHT, PIXEL_SIZE, &frameNum);
    // Tetris tetris(SCREEN_WIDTH, SCREEN_HEIGHT, PIXEL_SIZE, &frameNum);
    Home home(SCREEN_WIDTH, SCREEN_HEIGHT, PIXEL_SIZE, &frameNum);

    // game = snake for now
    std::string game = "home";
    

    // main loop
    while (!WindowShouldClose()) {

        // ------------------------------------   Update Stuff here ------------------------------------
        std::string newGame = game;
        
        if (game == "snake") {
            // If snake.update() returns true, game is over and it returns to home screen
            if(snake->update()) newGame = "home";
        }
        // else if (game == "tetris") {
        //     // If tetris.update() returns true, game is over and it returns to home screen
        //     if(tetris.update()) newGame = "home";
        // }
        else if (game == "home") {
            newGame = home.update();
        }
        
        // Reset snake if transitioning to snake
        if (newGame == "snake" && game != "snake") {
            delete snake;
            snake = new Snake(SCREEN_WIDTH, SCREEN_HEIGHT, PIXEL_SIZE, &frameNum);
        }
        
        game = newGame;
        
        BeginDrawing();
        //------------------------------------   Drawing is done in here   ------------------------------------

        if (game == "snake") snake->draw();
        // else if (game == "tetris") tetris.draw();
        else if (game == "home") home.draw();

        //------------------------------------   ------------------------   ------------------------------------
        EndDrawing();
    }
    delete snake;
    CloseWindow();
    return 0;
}