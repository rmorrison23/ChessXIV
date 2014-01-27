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
    
    /* testing draw functions here; they are not yet linked with events handling/bools */
    /* so only one draw can be run at a time right now */
    /* drawMainMenu(window, renderer); */

    /* drawOnePlayerMenu(renderer); */

    /* drawTwoPlayerMenu(renderer); */
   
    /* drawAdvancedMenu(window, renderer); */

    drawGameplayScreen(window, renderer);
 
    /* drawChessboard(renderer); */
    
    /* drawPieces(renderer); */
    
    SDL_RenderPresent(renderer);
    
    /* /\* event loop *\/ */
    /* int done = 0;      /\* 0 = false, 1 = true *\/ */
    /* SDL_Event event; */

    /* while(!done){ */
    /*   /\* quit = events(); *\/ */
    /*   while(SDL_PollEvent(&event)){ */

    /* 	switch(event.type){ */
    /* 	case SDL_QUIT: */
    /* 	  done = 1; */
    /* 	  break; */
    /* 	case SDL_KEYUP: */

    /* 	  switch(event.key.keysym.sym){ */
    /* 	  case SDLK_ESCAPE: */
    /* 	    done = 1; */
    /* 	    break; */
    /* 	  case SDLK_RETURN: */
    /* 	    /\* do something here *\/ */
    /* 	    break; */
    /* 	  default: */
    /* 	    break; */
    /* 	  }    */
    /* 	  break; */
    /* 	default: */
    /* 	  break; */
    /* 	} */
    /*   } */
    /* } */
	
    eventMain();
   
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    clean();
    
    return 0;
}
