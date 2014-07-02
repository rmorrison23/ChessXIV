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



void drawMainMenu(ViewHandle * MainHandle);
void drawOnePlayerMenu(ViewHandle * MainHandle);
void drawChessBoard(ViewHandle * MainHandle);
void drawTransformWindow(ViewHandle * MainHandle, PlayerColorEnum color);
void drawCheckBanner(ViewHandle *MainHandle, char *message);
void drawEndGameMessage(ViewHandle *MainHandle, char *message);

#endif