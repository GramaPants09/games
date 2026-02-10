#ifndef TETRIS_H
#define TETRIS_H
class Tetris {
    public:
        Tetris(const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const int PIXEL_SIZE, int* frameNum);
        void draw();
        bool update();

        
    private:
        void checkKeyPress(char* dir);
        static int SCREEN_WIDTH;
        static int SCREEN_HEIGHT;
        static int PIXEL_SIZE;
        int* frameNum;


};

#endif