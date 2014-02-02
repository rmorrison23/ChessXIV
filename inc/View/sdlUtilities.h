#ifndef SDLUTILITIES_H
#define SDLUTILITIES_H

#include <stdio.h>
/*#ifdef LINUX_OS
	#include "SDL.h"
	#include "SDL_image.h"
	#include "SDL_ttf.h"
#else
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
	#include <SDL2_ttf/SDL_ttf.h>
#endif*/
#include "View.h"
#include "render.h"
#include "display.h"
#include "constants.h"
/* main events handling function */
void eventMain();

/* main menu events handling */
void mainMenuEvents(SDL_Window *window, SDL_Renderer *renderer);

#endif
