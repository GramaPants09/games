#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "../include/raylib.h"

class Snake {
    private:
        bool oppositeDirection(char dir1, char dir2);
        void checkKeyPress(char* dir);
        void moveSnake(std::vector<Vector2>* snakeBody, Vector2* snakeHead, char* snakeDirection, char directionBuffer, int* frameNum, Vector2* snakeTailBuffer);
        Vector2 generateRandomAppleLocation(std::vector<Vector2> snakeBody);
        void checkEatApple(Vector2* snakeHead, Vector2* applePos, std::vector<Vector2>* snakeBody, Vector2 snakeTailBuffer);
        void checkCollision(std::vector<Vector2> snakeBody, Vector2 snakeHead);
    public:
        Snake(const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const int PIXEL_SIZE, int* frameNum);
        void draw();
        void update();
        static int SCREEN_WIDTH;
        static int SCREEN_HEIGHT;
        static int PIXEL_SIZE;
        int* frameNum;
        char directionBuffer;
        char snakeDirection;
        Vector2 applePos;
        std::vector<Vector2> snakeBody;
        Vector2 snakeHead;
        Vector2 snakeTailBuffer;

};

#endif