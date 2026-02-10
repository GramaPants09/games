#ifndef HOME_H
#define HOME_H

#include <vector>
#include "../include/raylib.h"
#include <string>

class Home{
    public:
        Home(const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const int PIXEL_SIZE, int* frameNum);
        void draw();
        std::string update();
        Vector2 checkMouseClick();
        std::string checkBox(Vector2 mouseCoords);
        
    private:
        static int SCREEN_WIDTH;
        static int SCREEN_HEIGHT;
        static int PIXEL_SIZE;
        int* frameNum;
        char directionBuffer;
        char snakeDirection;
        Font font;
        Image smurgImg;
        Texture2D smurgTexture;
};

#endif