#include "../include/raylib.h"
#include <vector>
#include <random>
#include <iostream>
#include "snake.h"
#include <string>
#include <sstream>

// Define static members
int Snake::SCREEN_WIDTH = 0;
int Snake::SCREEN_HEIGHT = 0;
int Snake::PIXEL_SIZE = 0;

Snake::Snake(const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const int PIXEL_SIZE, int* frameNum){
    this->SCREEN_WIDTH = SCREEN_WIDTH;
    this->SCREEN_HEIGHT = SCREEN_HEIGHT;
    this->PIXEL_SIZE = PIXEL_SIZE;
    this->frameNum = frameNum;

    // Snake Stuff
    snakeBody = {{(float)5*PIXEL_SIZE, (float)SCREEN_HEIGHT/2}, 
                                      {(float)4*PIXEL_SIZE, (float)SCREEN_HEIGHT/2},
                                      {(float)3*PIXEL_SIZE, (float)SCREEN_HEIGHT/2}  
                                    };
    snakeDirection = 'r';
    directionBuffer = 'r';
    snakeHead = snakeBody.at(0);
    quitGame = false;

    // Apple Stuff 
    applePos = generateRandomAppleLocation(snakeBody);

    font = LoadFont("fonts/goodTiming.otf");
    score = 0;
    displayText = "Score: 0";
}

bool Snake::oppositeDirection(char dir1, char dir2) {
    return ( (dir1 == 'u' && dir2 == 'd') ||
             (dir1 == 'r' && dir2 == 'l') ||
             (dir1 == 'd' && dir2 == 'u') ||
             (dir1 == 'l' && dir2 == 'r') );
}

// check for key presses
void Snake::checkKeyPress(char* dir) {
    if      ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)))    *dir = 'u';
    else if ((IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)))  *dir = 'd';
    else if ((IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)))  *dir = 'l';
    else if ((IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT))) *dir = 'r';
}

// update the snake body positions
void Snake::moveSnake(std::vector<Vector2>* snakeBody, Vector2* snakeHead, char* snakeDirection, char directionBuffer, int* frameNum, Vector2* snakeTailBuffer) {
    // check if to update movement on given frame, to control speed of snake
    if ((*frameNum)++ % 10 != 0) return; 

    *snakeTailBuffer = snakeBody->at(snakeBody->size()-1);

    if (!oppositeDirection(*snakeDirection, directionBuffer)) {
        *snakeDirection = directionBuffer;
    }

    // Check if snake is more than just head
    if (snakeBody->size() > 1) {
        for (int i = snakeBody->size()-1; i > 0; i--) {
            snakeBody->at(i) = snakeBody->at(i-1);
        }
    }

    if (*snakeDirection == 'u') snakeBody->at(0).y -= PIXEL_SIZE;
    else if (*snakeDirection == 'd') snakeBody->at(0).y += PIXEL_SIZE;
    else if (*snakeDirection == 'r') snakeBody->at(0).x += PIXEL_SIZE;
    else if (*snakeDirection == 'l') snakeBody->at(0).x -= PIXEL_SIZE;
    *snakeHead = snakeBody->at(0);
}

// generates valid random apple location
Vector2 Snake::generateRandomAppleLocation(std::vector<Vector2> snakeBody) {
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
void Snake::checkEatApple(Vector2* snakeHead, Vector2* applePos, std::vector<Vector2>* snakeBody, Vector2 snakeTailBuffer) {
    if (snakeHead->x == applePos->x && snakeHead->y == applePos->y) {
        snakeBody->push_back(snakeTailBuffer);
        *applePos = generateRandomAppleLocation(*snakeBody);

        // put the score in the displayText string
        std::stringstream ss;
        ss << "Score: " << ++score;
        displayText= ss.str();
    }
}

// checks for collisions between both snake and boundry
bool Snake::checkCollision(std::vector<Vector2> snakeBody, Vector2 snakeHead) {
    // check for boundry collision
    if (snakeBody.at(0).x > SCREEN_WIDTH || snakeBody.at(0).x < 0 || snakeBody.at(0).y > SCREEN_HEIGHT || snakeBody.at(0).y < 0) {
        std::cout << "Hit Border" << std::endl;
        return true;
    }

    //check for snake body collision
    if (snakeBody.size()>1) {
        for (int i = 1; i < snakeBody.size(); i++) {
            if (snakeBody.at(i).x == snakeHead.x && snakeBody.at(i).y == snakeHead.y) {
                std::cout << "Hit Snake" << std::endl;
                return true;
            }
        }
    }
    return false;
}

// calls all the game logic for the snake game
bool Snake::update() {
    SetWindowTitle("Games | Snake");
    checkKeyPress(&directionBuffer);
    moveSnake(&snakeBody, &snakeHead, &snakeDirection, directionBuffer, frameNum, &snakeTailBuffer);
    checkEatApple(&snakeHead, &applePos, &snakeBody, snakeTailBuffer);
    if (checkCollision(snakeBody, snakeHead)) quitGame = true;
    return quitGame;
}

// Draws the snake game to screen
void Snake::draw() {
    ClearBackground({85,133,121,255});

    DrawText(displayText.c_str(), SCREEN_WIDTH/4, SCREEN_HEIGHT/4, 80, {0,0,0,200});

    // Draw Apple
    DrawRectangleV(applePos, {(float)PIXEL_SIZE, (float)PIXEL_SIZE}, RED);

    // Draw Snake
    for (int i = 0; i <snakeBody.size(); i++) {
        int g = 255 - (i);
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

}