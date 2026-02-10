#include "tetris.h"
#include "../include/raylib.h"
// Define static members
int Tetris::SCREEN_WIDTH = 0;
int Tetris::SCREEN_HEIGHT = 0;
int Tetris::PIXEL_SIZE = 0;

Tetris::Tetris(const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const int PIXEL_SIZE, int* frameNum) {
    this->SCREEN_WIDTH = SCREEN_WIDTH;
    this->SCREEN_HEIGHT = SCREEN_HEIGHT;
    this->PIXEL_SIZE = PIXEL_SIZE;
    this->frameNum = frameNum;
}
void Tetris::checkKeyPress(char* dir) {
    if      ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)))    *dir = 'u';
    else if ((IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)))  *dir = 'd';
    else if ((IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)))  *dir = 'l';
    else if ((IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT))) *dir = 'r';
    else if (IsKeyPressed(KEY_Q)) *dir = 'q';
    else if (IsKeyPressed(KEY_E)) *dir = 'e';
}


bool Tetris::update(){
    return false;

}

void Tetris::draw() {
    ClearBackground({255,229,99,245});

    // DrawText("This is a game with no name", SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 20, BLACK);
    
}