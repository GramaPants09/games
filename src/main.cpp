#include "../include/raylib.h"
#include <vector>
#include <random>
#include <iostream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int PIXEL_SIZE = 20;

// check for key presses
void checkKeyPress(char* dir) {
    if      (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))    *dir = 'u';
    else if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN))  *dir = 'd';
    else if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT))  *dir = 'l';
    else if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) *dir = 'r';
}

// update the snake body positions
void moveSnake(std::vector<Vector2>* snakeBody, Vector2* snakeHead, char snakeDirection, int* frameNum, Vector2* snakeTailBuffer) {
    // check if to update movement on given frame, to control speed of snake
    if ((*frameNum)++ % 10 != 0) return; 

    *snakeTailBuffer = snakeBody->at(snakeBody->size()-1);

    // Check if snake is more than just head
    if (snakeBody->size() > 1) {
        for (int i = snakeBody->size()-1; i > 0; i--) {
            snakeBody->at(i) = snakeBody->at(i-1);
        }
    }

    if (snakeDirection == 'u') snakeBody->at(0).y -= PIXEL_SIZE;
    else if (snakeDirection == 'd') snakeBody->at(0).y += PIXEL_SIZE;
    else if (snakeDirection == 'r') snakeBody->at(0).x += PIXEL_SIZE;
    else if (snakeDirection == 'l') snakeBody->at(0).x -= PIXEL_SIZE;
    *snakeHead = snakeBody->at(0);
}

// generates valid random apple location
Vector2 generateRandomAppleLocation(std::vector<Vector2> snakeBody) {
    // generate random number using current time as the seed for the random generator
    
    int x,y;
    bool valid = false;
    Vector2 applePos;

    do {
        // picks two random numbers between 0 and respective width and height values, rounded to the nearest pixel
        x = (rand() % (800/PIXEL_SIZE)) * PIXEL_SIZE;
        y = (rand() % (600/PIXEL_SIZE)) * PIXEL_SIZE;

        // puts the x,y into 2d Vector
        applePos = {(float) x, (float)y};
        // checks for matching coordinates, if none are found, found
        for (int i= 0; i < snakeBody.size(); i++) {
            if (applePos.x == snakeBody.at(i).x && applePos.y == snakeBody.at(i).y){
                valid = false;
                break;
            }
            valid = true;
        }

    } while(!valid);

    return applePos;
}

// checks if the Snake ate the apple
void checkEatApple(Vector2* snakeHead, Vector2* applePos, std::vector<Vector2>* snakeBody, Vector2 snakeTailBuffer) {
    if (snakeHead->x == applePos->x && snakeHead->y == applePos->y) {
        snakeBody->push_back(snakeTailBuffer);
        *applePos = generateRandomAppleLocation(*snakeBody);
    }
}

// checks for collisions between both snake and boundry
void checkCollision(std::vector<Vector2> snakeBody, Vector2 snakeHead) {
    // check for boundry collision
    if (snakeBody.at(0).x > SCREEN_WIDTH || snakeBody.at(0).x < 0 || snakeBody.at(0).y > SCREEN_HEIGHT || snakeBody.at(0).y < 0) {
        CloseWindow();
        return;
    }

    //check for snake body collision
    if (snakeBody.size()>1) {
        for (int i = 1; i < snakeBody.size(); i++) {
            if (snakeBody.at(i).x == snakeHead.x && snakeBody.at(i).y == snakeHead.y) {
                CloseWindow();
                return;
            }
        }
    }
}

int main() {

    // Window and Game setup
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "sneck");
    SetTargetFPS(60);
    int frameNum = 0;

    // set up random
    srand(time(NULL));

    // Snake Stuff
    std::vector<Vector2> snakeBody;
    char snakeDirection = 'o';
    Vector2 snakeHead;
    Vector2 snakeTailBuffer;

    snakeBody.push_back({(float)3*PIXEL_SIZE, (float)SCREEN_HEIGHT/2});
    snakeHead = snakeBody.front();

    // Apple Stuff 
    Vector2 applePos = generateRandomAppleLocation(snakeBody);

    // main loop
    while (!WindowShouldClose()) {

        // ------------------------------------   Update Stuff here ------------------------------------
        checkKeyPress(&snakeDirection);
        moveSnake(&snakeBody, &snakeHead, snakeDirection, &frameNum, &snakeTailBuffer);
        checkEatApple(&snakeHead, &applePos, &snakeBody, snakeTailBuffer);
        checkCollision(snakeBody, snakeHead);

        BeginDrawing();
        //------------------------------------   Drawing is done in here   ------------------------------------

        ClearBackground({255,229,99,245});
        // DrawText("This is a game with no name", SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 20, BLACK);

        // Draw Apple
        DrawRectangleV(applePos, {PIXEL_SIZE, PIXEL_SIZE}, RED);

        // Draw Snake
        for (int i = 0; i <snakeBody.size(); i++) {
            int g = 255 - (i*5);
            if (g < 0) g *= -1;

            DrawRectangle(snakeBody.at(i).x, snakeBody.at(i).y, PIXEL_SIZE, PIXEL_SIZE, {0, (unsigned char)g, 0, 255});
        }

        // draw grid
        for (int x = 0; x <= SCREEN_WIDTH; x+= PIXEL_SIZE) {
            DrawLine(x, 0, x, SCREEN_HEIGHT, BLACK);
        }
        for (int y = 0; y <= SCREEN_HEIGHT; y+= PIXEL_SIZE) {
            DrawLine(0, y, SCREEN_WIDTH, y, BLACK);
        }

        //------------------------------------   ------------------------   ------------------------------------
        EndDrawing();
    }
    CloseWindow();
    return 0;
}