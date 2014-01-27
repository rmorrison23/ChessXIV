#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include "render.h"
#include "display.h"
#include "constants.h"
#include "sdlUtilities.h"

void eventMain(){

    /* event loop */
    int done = 0;      /* 0 = false, 1 = true */
    SDL_Event event;

    while(!done){
      /* quit = events(); */
      while(SDL_PollEvent(&event)){

	switch(event.type){
	case SDL_QUIT:
	  done = 1;
	  break;
	case SDL_KEYUP:

	  switch(event.key.keysym.sym){
	  case SDLK_ESCAPE:
	    done = 1;
	    break;
	  case SDLK_RETURN:
	    /* do something here */
	    break;
	  default:
	    break;
	  }   
	  break;
	default:
	  break;
	}
      }
    }
}
