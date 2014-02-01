/************************************************************************/
/* render.c: source file for rendering/loading functions                */
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

#include "render.h"

/* function to load a texture */
SDL_Texture *loadTexture(const char *fileName, SDL_Renderer *renderer){
    
  SDL_Texture *texture = NULL;
  SDL_Surface *loadedImage = NULL;
  
  loadedImage = IMG_Load(fileName);

  if(loadedImage){

    texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
    SDL_FreeSurface(loadedImage);

    if(!loadedImage){
      //error
    }
  }
  //SDL_Texture *texture = IMG_LoadTexture(renderer, fileName);
   //error check
   return texture;
}

/* function to render a texture with specified(scaled) size */
void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, int w, int h){
    
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;   
    dest.w = w;
    dest.h = h;
    
    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

/* function to render a texture with native(no scaling) size */
void renderTexture2(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y){

  int width, height;
  SDL_QueryTexture(texture, NULL, NULL, &width, &height);
  renderTexture(texture, renderer, x, y, width, height);
}

SDL_Texture *renderText(char *String, char *imageFileName, SDL_Color Color, int TextSize, 
			MainHandle->CurrentWindow->WindowRenderer){

  TTF_Font *font = TTF_OpenFont(fontFile, TextSize);
  SDL_Surface *surface = TTF_RenderText_Blended(imageFileName, String, Color);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(MainHandle->CurrentWindow->WindowRenderer, surface);
  SDL_FreeSurface(surface); 
  TTF_CloseFont(font);
  return texture;
}

SDL_Texture *renderFilledBox(int hexR, int hexG, int hexB, int hexA, int X, int Y, int Width, int Height, 
			     MainHandle->CurrentWindow->WindowRenderer){

  SDL_Rect Box = {X, Y, Width, Height};
  SDL_SetRenderDrawColor(MainHandle->CurrentWindow->WindowRenderer, hexR, hexG, hexB, hexA);
  SDL_RenderFillRect(MainHandle->CurrentWindow->WindowRenderer, &Box);
  
  return no;
}

SDL_Texture *renderEmptyBox(int hexR, int hexG, int hexB, int hexA, int X, int Y, int Width, int Height, 
			     MainHandle->CurrentWindow->WindowRenderer){

  SDL_Rect Box = {X, Y, Width, Height};
  SDL_SetRenderDrawColor(MainHandle->CurrentWindow->WindowRenderer, hexR, hexG, hexB, hexA);
  SDL_RenderDrawRect(MainHandle->CurrentWindow->WindowRenderer, &Box);
  
  return no;

}

/* old function to render text */
/* SDL_Texture *renderText(const char *message, const char *fontFile, SDL_Color color, */
/* 			int fontSize, SDL_Renderer *renderer){ */

/*   //open desired font */
/*   TTF_Font *font = TTF_OpenFont(fontFile, fontSize); */

/*   /\* error check *\/ */

/*   //render to a surface and load surface into a texture */
/*   SDL_Surface *surface = TTF_RenderText_Blended(font, message, color); */

/*   /\* error check *\/ */

/*   SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface); */

/*   /\* error check *\/ */

/*   SDL_FreeSurface(surface); */
/*   TTF_CloseFont(font); */
/*   return texture; */
/* } */
