#include "../include/raylib.h"
#include "home.h"
#include <iostream>

int Home::SCREEN_HEIGHT = 0;
int Home::SCREEN_WIDTH = 0;
int Home::PIXEL_SIZE = 0;

 Home::Home(const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const int PIXEL_SIZE, int* frameNum) {
    this->SCREEN_WIDTH = SCREEN_WIDTH;
    this->SCREEN_HEIGHT = SCREEN_HEIGHT;
    this->PIXEL_SIZE = PIXEL_SIZE;
    font = LoadFont("fonts/goodTiming.otf");
    smurgImg = LoadImage("images/super_smurg.png");
    smurgTexture = LoadTextureFromImage(smurgImg);

}

std::string Home::update() {
    SetWindowTitle("Games | Home");
    return checkBox(checkMouseClick());
}

void Home::draw() {
    ClearBackground(SKYBLUE);
    DrawTexture(smurgTexture, 0, 0, WHITE);
    
    
    DrawRectangleRounded({100, 100, 200, 40}, 0.5f, 10, WHITE);
    DrawText("Snake", 140, 107, 30, BLACK);
}

Vector2 Home::checkMouseClick() {
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        std::cout <<  GetMousePosition().x << ", " << GetMousePosition().y << std::endl;
        return GetMousePosition();
    }
    else return {-1,-1};
}

std::string Home::checkBox(Vector2 mouseCoords) {

    // first check if mouse was even clicked
    if (mouseCoords.x < 0) return "home";

    Vector2 boxes[1][2] = {{{100, 100}, {300, 140}}};

                          // TODO: Work on a generalized version
    // for (int i = 0; i < sizeof(boxes) / sizeof(boxes[0]); i++) {
    //     for (int j = 0; j < sizeof(boxes[0]) / sizeof(boxes[0][0]); j++) {
    //         // see if cursor is in bounds of given box
    //         if (mouseCoords.x >= boxes[i][j].x && mouseCoords.x <= boxes[i][j+1].x && 
    //             mouseCoords.y >= boxes[i][j].y && mouseCoords.y <= boxes[i][j+1].y) return true;
    //     }
    // }
    // return false;
    if (mouseCoords.x >= boxes[0][0].x && mouseCoords.x <= boxes[0][1].x && 
        mouseCoords.y >= boxes[0][0].y && mouseCoords.y <= boxes[0][1].y) return "snake";
    
    return "home";
}