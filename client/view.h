#include <SDL2/SDL.h>
#define WIDTH 640
#define HEIGHT 480
extern SDL_Window* window;
extern SDL_Renderer* render;
extern int running;
extern void drawLine(int x1, int y1, int x2, int y2);
extern void drawPoint(int x, int y, int color);
extern int initView();
extern void clearScreen();
extern void paint();
