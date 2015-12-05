#include <stdlib.h>
#include <stdio.h>
#include "view.h"
SDL_Rect pt = {.w = 2, .h = 2};
unsigned char red = 255, green = 0, blue = 0;
void paint(){
	SDL_RenderPresent(render);
}
void clearScreen(){
	SDL_SetRenderDrawColor(render, 0,0,0,255);
	SDL_RenderClear(render);
}
int initView(){
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	window = SDL_CreateWindow("Power Diagram", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
	if(window == NULL){
		SDL_Quit();
		return 1;
	}
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	clearScreen();
	paint();
	return 0;
}

void drawLine(int x1, int y1, int x2, int y2){
//	SDL_SetRenderDrawColor(render, 200, 0, 255, 255);
	SDL_RenderDrawLine(render, x1, y1, x2, y2);
}
void cycleHue(){
	if(red != 0 && blue == 0){
		red -= 1;
		green += 1;
	}else if(green != 0 && red ==0){
		green -= 1;
		blue += 1;
	}else if(blue != 0 && green == 0){
		blue -= 1;
		red += 1;
	}else puts("color cycle error");
	SDL_SetRenderDrawColor(render, red, green, blue, 255);
}
void drawPoint(int x, int y, int color){
	if(color == 0) SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
	if(color == 1) SDL_SetRenderDrawColor(render, 0, 0, 255, 255);
	pt.x = x;
	pt.y = y;
	SDL_RenderFillRect(render, &pt);
}
