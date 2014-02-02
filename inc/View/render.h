/************************************************************************/
/* render.h: header file for SDL rendering/loading operations           */
/************************************************************************/
/* Author: Ryan M. Morrison                                             */
/*                                                                      */
/* History:                                                             */
/*          12/26/13 initial file creation                              */
/*          12/27/13 added text rendering function                      */
/*          12/30/13 added texture loading and rendering functions      */
/*          01/19/14 added second texture function to preserve surface  */
/*                   dimensions                                         */
/************************************************************************/

#ifndef RENDER_H
#define RENDER_H

#include "View.h"

/*#ifdef LINUX_OS
	#include "SDL.h"
	#include "SDL_image.h"
	#include "SDL_ttf.h"
#else
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
	#include <SDL2_ttf/SDL_ttf.h>
#endif*/

/* function to load a texture */
SDL_Texture *loadTexture(const char *fileName, SDL_Renderer *renderer);

/* function to render a texture with specified(scaled) size */
void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, int w, int h);

/* function to render a texture with native(no scaling) size */
void renderTexture2(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y);

SDL_Texture *renderText(char *String, char *imageFileName, SDL_Color Color, int TextSize, 
			SDL_Renderer *renderer);

SDL_Texture *renderFilledBox(int hexR, int hexG, int hexB, int hexA, int X, int Y, int Width, int Height, 
			     SDL_Renderer *renderer);

SDL_Texture *renderEmptyBox(int hexR, int hexG, int hexB, int hexA, int X, int Y, int Width, int Height, 
			    SDL_Renderer *renderer);

/* old function to render text */
/* SDL_Texture *renderText(const char *message, const char *fontFile, SDL_Color color, */
/* 			int fontSize, SDL_Renderer *renderer);*/



#endif
