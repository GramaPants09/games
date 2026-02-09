#include "../include/raylib.h"
#include <vector>
#include <random>
#include <iostream>
#include "snake.h"
#include <string>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int PIXEL_SIZE = 20;

// check for key presses
void checkKeyPress(char* dir) {}

int main() {

    // Window and Game setup
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "sneck");
    SetTargetFPS(60);
    int frameNum = 1;

    // set up random
    srand(time(NULL));

    // create snake object
    Snake snake(SCREEN_WIDTH, SCREEN_HEIGHT, PIXEL_SIZE, &frameNum);

    // game = snake for now
    std::string game = "snake";
    

    // main loop
    while (!WindowShouldClose()) {

        // ------------------------------------   Update Stuff here ------------------------------------
        if (game == "snake") snake.update();
        
        BeginDrawing();
        //------------------------------------   Drawing is done in here   ------------------------------------

        if (game == "snake") snake.draw();

        //------------------------------------   ------------------------   ------------------------------------
        EndDrawing();
    }
    CloseWindow();
    return 0;
}