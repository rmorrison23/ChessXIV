/******************************************************************************/
/* display.h: header file for displaying chess game graphics                  */
/******************************************************************************/
/* Author: Ryan M. Morison                                                    */
/*                                                                            */
/* History:                                                                   */
/*          12/22/13 initial file creation; draw window with checkerboard     */
/*          12/28/13 draw pieces on board                                     */
/*          01/18/14 draw main menu                                           */
/******************************************************************************/

#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <stdlib.h>

#ifdef LINUX_OS
	#include "SDL.h"
	#include "SDL_image.h"
	#include "SDL_ttf.h"
#else
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
	#include <SDL2_ttf/SDL_ttf.h>
#endif

#include "View.h"
#include "render.h"
#include "constants.h"


#ifdef QUAN_VERSION
void drawMainMenu(ViewHandle * MainHandle);
void drawOnePlayerMenu(ViewHandle * MainHandle);
#else
/* function to display the main menu to the screen */
/* int drawMainMenu(SDL_Window *window, SDL_Renderer *renderer, int *screenMode); */

/* function to display the one player menu to the screen */
int drawOnePlayerMenu(SDL_Window *window, SDL_Renderer *renderer, int *screenMode);
#endif



/* function to display the one player menu to the screen */
int drawTwoPlayerMenu(SDL_Window *window, SDL_Renderer *renderer, int *screenMode);

/* function to display the advanced menu to the screen */
void drawAdvancedMenu(SDL_Window *window, SDL_Renderer *renderer);

/* function to display the gameplay window to the screen */
void drawGameplayScreen(SDL_Window *window, SDL_Renderer *renderer);

/* function to display the left player window */
void drawLeftPlayerWindow(SDL_Renderer *renderer, int tileSize, int playerMode);

/* function to display the right player window */
void drawRightPlayerWindow(SDL_Renderer *renderer, int tileSize, int playerMode);

/* function to display the left player window */
void drawRightPlayerWindow(SDL_Renderer *renderer, int tileSize, int playerMode);

/* function to display a blank chessboard to the screen */
void drawChessboard(SDL_Renderer *renderer);

/* function to display the pieces in beginning position on the chessboard */
void drawPieces(SDL_Renderer *renderer);

/* function to uninitialize SDL systems */
void clean();

#endif
