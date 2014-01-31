/******************************************************************************/
/* TestDrawingFuncs.c: main function for chess game                           */
/******************************************************************************/
/* Author: Ryan M. Morison                                                    */
/*                                                                            */
/* History:                                                                   */
/*          12/22/13 initial file creation; draw window with checkerboard     */
/*          12/26/13 generalize basic SDL operations into functions @ chess.h */
/*          01/??/14 split chess.h into display.c/h and render.c/h            */
/******************************************************************************/

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include "render.h"
#include "display.h"
#include "constants.h"
#include "sdlUtilities.h"


int main(int argc, char *argv[]){
    
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    
    if(SDL_Init(SDL_INIT_EVERYTHING) >= 0){
        window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, 0);
    }
    else{
        //error check here
    }
    if(TTF_Init() != 0){
        //error check here
    }
        
    // clear screen
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    
    int zeroCase = 0;
    int *screenMode;     /* 0 = main, 1 = one player, 2 = two players, 3 = game screen, 100 = esc */
    screenMode = &zeroCase;
    int playing = 0;
    int on = 1;

    *screenMode = drawMainMenu(window, renderer, screenMode);
  
      while(!playing){

	if(*screenMode == 0){
	  *screenMode = drawMainMenu(window, renderer, screenMode);
	}
	if(*screenMode == 1){
	  *screenMode = drawOnePlayerMenu(window, renderer, screenMode);
	}
	if(*screenMode == 2){
	  *screenMode = drawTwoPlayerMenu(window, renderer, screenMode);
	}
	if(*screenMode == 3){
	  drawGameplayScreen(window, renderer);
	  playing = 1;
	}
	if(*screenMode == 100){
	  break;
	}
      }    
   

    /* drawOnePlayerMenu(window, renderer); */

    /* drawTwoPlayerMenu(window, renderer); */
   
    /* drawAdvancedMenu(window, renderer); */

    /* drawGameplayScreen(window, renderer); */
 
    /* drawChessboard(renderer); */
    
    /* drawPieces(renderer); */
    
    /* mainMenuEvents(window, renderer); */

    eventMain();

    SDL_RenderPresent(renderer);
   
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    clean();
    
    return 0;
}
