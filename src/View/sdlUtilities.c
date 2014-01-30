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

/* main menu events handling */
void mainMenuEvents(SDL_Window *window, SDL_Renderer *renderer){

  int done =0;	     /* 0 = false, 1 = true */
  int buttonWidth = 0, buttonHeight = 0;
  SDL_Event event;
  SDL_Color white = {255, 255, 255};

  SDL_Texture *onePlayer_Button = renderText(ONE_PLAYER, CALIBRI_FONT, white, 72, renderer);
  SDL_QueryTexture(onePlayer_Button, NULL, NULL, &buttonWidth, NULL);
  SDL_QueryTexture(onePlayer_Button, NULL, NULL, NULL, &buttonHeight);

  while(!done){

    while(SDL_PollEvent(&event)){

      switch(event.type){

      case SDL_QUIT:
	done = 1;
	break;
      case SDL_KEYUP:
	if(event.key.keysym.sym == SDLK_ESCAPE)
	  done = 1;
	break;
      case SDL_MOUSEMOTION:
	/* if(event.motion.x > SCREEN_WIDTH*0.6 && event.motion.x < SCREEN_WIDTH*0.6 + buttonWidth */
	/*    && event.motion.y > SCREEN_HEIGHT/2.5 && event.motion.y < SCREEN_HEIGHT/2.5 + buttonHeight){ */
	/*   SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); */
	/*   SDL_RenderClear(renderer); */
	/*   drawOnePlayerMenu(window, renderer); */
	/*   done = 1; */
	/*   break; */
	/* } */
	/* else if(event.motion.x > SCREEN_WIDTH*0.6 && event.motion.x < SCREEN_WIDTH*0.6 + buttonWidth */
	/* 	&& event.motion.y > SCREEN_HEIGHT/2.5 + buttonHeight */
	/* 	&& event.motion.y < SCREEN_HEIGHT/2.5 + 2*buttonHeight){ */
	/*   SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); */
	/*   SDL_RenderClear(renderer); */
	/*   drawTwoPlayerMenu(window, renderer); */
	/*   done = 1; */
	/*   break; */
	/* } */
	/* else if(event.motion.x > SCREEN_WIDTH*0.6 && event.motion.x < SCREEN_WIDTH*0.6 + buttonWidth */
	/* 	&& event.motion.y > SCREEN_HEIGHT/2.5 + 2*buttonHeight */
	/* 	&& event.motion.y < SCREEN_HEIGHT/2.5 + 3*buttonHeight){ */
	/*   SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); */
	/*   SDL_RenderClear(renderer); */
	/*   drawGameplayScreen(window, renderer); */
	/*   done = 1; */
	/*   break; */
	/* } */
	/* else; */
	break;
	
      }
    }
  }
  
}
