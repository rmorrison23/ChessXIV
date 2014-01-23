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

#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_image/SDL_image.h>

/* function to load a texture */
SDL_Texture *loadTexture(const char *fileName, SDL_Renderer *renderer);

/* function to render a texture with specified(scaled) size */
void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, int w, int h);

/* function to render a texture with native(no scaling) size */
void renderTexture2(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y);

/* function to render text */
SDL_Texture *renderText(const char *message, const char *fontFile, SDL_Color color,
			int fontSize, SDL_Renderer *renderer);

#endif
