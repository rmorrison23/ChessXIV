/******************************************************************************/
/* display.c: source file for drawing chess game graphics                     */
/******************************************************************************/
/* Author: Ryan M. Morison                                                    */
/*                                                                            */
/* History:                                                                   */
/*          12/22/13 initial file creation; draw window with checkerboard     */
/*          12/28/13 draw pieces on board                                     */
/*          01/18/14 draw main menu                                           */
/******************************************************************************/

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include "render.h"
#include "constants.h"
#include "display.h"

/* BUG: title is not centered */
/* function to display the main menu to the screen */
void drawMainMenu(SDL_Renderer *renderer){

  /* create main menu background image */
  SDL_Texture *backSplash = NULL;
  backSplash = loadTexture("Assets/Menu_Backgrounds/Background_1600_900.jpg", renderer);
  renderTexture(backSplash, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

  /* create title */
  SDL_Color titleColor = {0xA8, 0xC6, 0xDB};
  SDL_Texture *title = renderText(TITLE, CALIBRI_FONT, titleColor, 200, renderer);
  renderTexture2(title, renderer, (SCREEN_WIDTH - TITLE_WIDTH)/2, SCREEN_HEIGHT*0);

  /* create main menu buttons */
  SDL_Color buttonColor = {255, 255, 255}; /* default white */
  SDL_Texture *onePlayer_Button = renderText(ONE_PLAYER, CALIBRI_FONT, buttonColor, 72, renderer);
  renderTexture2(onePlayer_Button, renderer, SCREEN_WIDTH*0.6, SCREEN_HEIGHT/2.5);
  SDL_Texture *twoPlayer_Button = renderText(TWO_PLAYERS, CALIBRI_FONT, buttonColor, 72, renderer);
  renderTexture2(twoPlayer_Button, renderer, SCREEN_WIDTH*0.6, (SCREEN_HEIGHT*0.666667 - 90));
  SDL_Texture *advanced_Button = renderText(ADVANCED, CALIBRI_FONT, buttonColor, 72, renderer);
  renderTexture2(advanced_Button, renderer, SCREEN_WIDTH*0.6, SCREEN_HEIGHT*0.666667);
}

/* function to display the one player menu to the screen */
void drawOnePlayerMenu(SDL_Renderer *renderer){
}

/* function to display the one player menu to the screen */
void drawTwoPlayerMenu(SDL_Renderer *renderer){
}

/* function to display the advanced menu to the screen */
void drawAdvancedMenu(SDL_Renderer *renderer){
}

/* function to display the gameplay window to the screen */
void drawGameplayScreen(SDL_Renderer *renderer){
}

/* function to display a blank chessboard to the screen */
void drawChessboard(SDL_Renderer *renderer){
        
  SDL_Rect whiteTile, blackTile;
  whiteTile.w = BOARD_WIDTH / 8;
  whiteTile.h = BOARD_HEIGHT / 8;
  blackTile.w = BOARD_WIDTH / 8;
  blackTile.h = BOARD_HEIGHT / 8;
  int tileSize = whiteTile.w;
    
  for(int i = 0; i < 8; i++){
    
    for(int j = 0; j < 8; j++){
      whiteTile.x = j * tileSize;
      whiteTile.y = i * tileSize;
      blackTile.x = j * tileSize;
      blackTile.y = i * tileSize;
      
      if(i % 2 == 0){
	if(j % 2 == 0){
	  SDL_SetRenderDrawColor(renderer, 0xB3, 0xB3, 0xB3, 0xB3);
	  SDL_RenderFillRect(renderer, &whiteTile);
	}
	else{
	  SDL_SetRenderDrawColor(renderer, 0x6D, 0x6D, 0x6D, 0x6D);
	  SDL_RenderFillRect(renderer, &blackTile);
	}
      }
      else{
	if(j % 2 != 0){
	  SDL_SetRenderDrawColor(renderer, 0xB3, 0xB3, 0xB3, 0xB3);
	  SDL_RenderFillRect(renderer, &whiteTile);
	}
	else{
	  SDL_SetRenderDrawColor(renderer, 0x6D, 0x6D, 0x6D, 0x6D);
	  SDL_RenderFillRect(renderer, &blackTile);
	}
      }
    }
  }
}

/* function to display the pieces in beginning position on the chessboard */
void drawPieces(SDL_Renderer *renderer){
    
  int i=0;
  SDL_Texture *piece = NULL;
    
  // black pawns
  piece = loadTexture("Assets/B_Pawn.png", renderer);
  for(i=0; i<8; i++){
    renderTexture(piece, renderer, BOARD_WIDTH/8*i, BOARD_HEIGHT/8 , BOARD_WIDTH/8, BOARD_HEIGHT/8);
  }
  
  // black rooks
  piece = loadTexture("Assets/B_Rook.png", renderer);
  renderTexture(piece, renderer, 0, 0, BOARD_WIDTH/8, BOARD_HEIGHT/8);
  renderTexture(piece, renderer, BOARD_WIDTH/8*7, 0, BOARD_WIDTH/8, BOARD_HEIGHT/8);
  
  // black knights
  piece = loadTexture("Assets/B_Knight.png", renderer);
  renderTexture(piece, renderer, BOARD_WIDTH/8, 0, BOARD_WIDTH/8, BOARD_HEIGHT/8);
  renderTexture(piece, renderer, BOARD_WIDTH/8*6, 0, BOARD_WIDTH/8, BOARD_HEIGHT/8);
  
  // black bishops
  piece = loadTexture("Assets/B_Bishop.png", renderer);
  renderTexture(piece, renderer, BOARD_WIDTH/8*2, 0, BOARD_WIDTH/8, BOARD_HEIGHT/8);
  renderTexture(piece, renderer, BOARD_WIDTH/8*5, 0, BOARD_WIDTH/8, BOARD_HEIGHT/8);
  
  // black king
  piece = loadTexture("Assets/B_King.png", renderer);
  renderTexture(piece, renderer, BOARD_WIDTH/8*4, 0, BOARD_WIDTH/8, BOARD_HEIGHT/8);
  
  // black queen
  piece = loadTexture("Assets/B_Queen.png", renderer);
  renderTexture(piece, renderer, BOARD_WIDTH/8*3, 0, BOARD_WIDTH/8, BOARD_HEIGHT/8);
  
  // white pawns
  piece = loadTexture("Assets/W_Pawn.png", renderer);
  for(i=0; i<8; i++){
    renderTexture(piece, renderer, BOARD_WIDTH/8*i, BOARD_HEIGHT/8*6 , BOARD_WIDTH/8, BOARD_HEIGHT/8);
  }
    
  // white rooks
  piece = loadTexture("Assets/W_Rook.png", renderer);
  renderTexture(piece, renderer, 0, BOARD_HEIGHT/8*7, BOARD_WIDTH/8, BOARD_HEIGHT/8);
  renderTexture(piece, renderer, BOARD_WIDTH/8*7, BOARD_HEIGHT/8*7, BOARD_WIDTH/8, BOARD_HEIGHT/8);
  
  // white knights
  piece = loadTexture("Assets/W_Knight.png", renderer);
  renderTexture(piece, renderer, BOARD_WIDTH/8, BOARD_HEIGHT/8*7, BOARD_WIDTH/8, BOARD_HEIGHT/8);
  renderTexture(piece, renderer, BOARD_WIDTH/8*6, BOARD_HEIGHT/8*7, BOARD_WIDTH/8, BOARD_HEIGHT/8);
  
  // white bishops
  piece = loadTexture("Assets/W_Bishop.png", renderer);
  renderTexture(piece, renderer, BOARD_WIDTH/8*2, BOARD_HEIGHT/8*7, BOARD_WIDTH/8, BOARD_HEIGHT/8);
  renderTexture(piece, renderer, BOARD_WIDTH/8*5, BOARD_HEIGHT/8*7, BOARD_WIDTH/8, BOARD_HEIGHT/8);
  
  // white king
  piece = loadTexture("Assets/W_King.png", renderer);
  renderTexture(piece, renderer, BOARD_WIDTH/8*4, BOARD_HEIGHT/8*7, BOARD_WIDTH/8, BOARD_HEIGHT/8);
  
  // white queen
  piece = loadTexture("Assets/W_Queen.png", renderer);
  renderTexture(piece, renderer, BOARD_WIDTH/8*3, BOARD_HEIGHT/8*7, BOARD_WIDTH/8, BOARD_HEIGHT/8);
}

/* TEMPORARY: events handling function to allow testing of rendering/drawing functions */
int events(){
  SDL_Event event;
  int status = 0;
  if(SDL_PollEvent(&event)){
    switch(event.type){
    case SDL_QUIT:
      status = 1;
      break;
    default:
      break;
    }
  }
  return status;
}

/* function to uninitialize SDL systems */
void clean(){
   
  TTF_Quit();
  SDL_Quit();
}
