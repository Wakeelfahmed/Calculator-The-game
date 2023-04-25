
//#ifndef COMMON_H_
//#define COMMON_H_
//
//#ifdef __cplusplus
//extern "C" {
//#endif 

#include "C:\SDL2-devel-2.26.1-VC\include\SDL.h"		//for SDL GUI
#include "C:\SDL2-devel-2.26.1-VC\include\SDL_ttf.h"	//for SDL GUI Font
#include "C:\SDL2-devel-2.26.1-VC\include\SDL2_gfxPrimitives.h"	//for Advanced SDL GUI

#define Screen_Width 405
#define Screen_Height 571
extern TTF_Font* font; //= TTF_OpenFont("arial.ttf", 100);;
extern SDL_Window* window;// = SDL_CreateWindow("Calculator: The Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Screen_Width/*width*/, Screen_Height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
extern SDL_Renderer* renderer;// = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
extern int Transparency;

//#ifdef __cplusplus
//}
//#endif
//#endif





//
////static SDL_Window* window;
////static SDL_Renderer* renderer;
////static TTF_Font* font;