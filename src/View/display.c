/******************************************************************************/
/* display.c: source file for drawing chess game graphics                     */
/******************************************************************************/
/* Author: Ryan M. Morison                                                    */
/*                                                                            */
/* History:                                                                   */
/*          12/22/13 initial file creation; draw window with checkerboard     */
/*          12/28/13 draw pieces on board                                     */
/*          01/18/14 draw main menu                                           */
/*          01/25/14 draw one player menu, draw two player,                   */
/*                   draw advanced menu, draw gameplay screen (incomplete)    */
/*          01/26/14 draw player status windows, */
/******************************************************************************/

#include <stdio.h>

#include "display.h"


/* function to display the main menu to the screen */
int drawMainMenu(SDL_Window *window, SDL_Renderer *renderer, int *screenMode){

  SDL_Color greenText = {0x29, 0xEF, 0x48};

  /* rename window title */
  SDL_SetWindowTitle(window, TITLE);

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
  SDL_Texture *advanced_Button = renderText("AI Versus AI", CALIBRI_FONT, buttonColor, 72, renderer);
  renderTexture2(advanced_Button, renderer, SCREEN_WIDTH*0.6, SCREEN_HEIGHT*0.666667);

  SDL_RenderPresent(renderer);


  int done = 0;

  int buttonWidth = 0, buttonHeight = 0;
  int x_pos = 0, y_pos = 0;

  SDL_Event event;
  SDL_QueryTexture(onePlayer_Button, NULL, NULL, &buttonWidth, NULL);
  SDL_QueryTexture(onePlayer_Button, NULL, NULL, NULL, &buttonHeight);

  while(!done){

    while(SDL_PollEvent(&event)){
     
      switch(event.type){

      case SDL_QUIT:
	*screenMode = 100;
	done = 1;
	break;

      case SDL_KEYUP:
	if(event.key.keysym.sym == SDLK_ESCAPE){
	  *screenMode = 100;
	  done = 1;
	}
	break;
	
      case SDL_MOUSEMOTION:
	/* highlight when mouse over one player button */
	if(event.motion.x > SCREEN_WIDTH*0.6 && event.motion.x < SCREEN_WIDTH*0.6 + buttonWidth
	   && event.motion.y > SCREEN_HEIGHT/2.5 && event.motion.y < SCREEN_HEIGHT/2.5 + buttonHeight - 20){
	  onePlayer_Button = renderText(ONE_PLAYER, CALIBRI_FONT, greenText, 72, renderer);
	  renderTexture2(onePlayer_Button, renderer, SCREEN_WIDTH*0.6, SCREEN_HEIGHT/2.5);
	  SDL_RenderPresent(renderer);
	   break; 
	}
	/* highlight when mouse over two player button */
	else if(event.motion.x > SCREEN_WIDTH*0.6 && event.motion.x < SCREEN_WIDTH*0.6 + buttonWidth + 40
	   && event.motion.y > SCREEN_HEIGHT/2.5 + buttonHeight + 25 && event.motion.y < SCREEN_HEIGHT/2.5 + 2*buttonHeight - 10){
	  twoPlayer_Button = renderText(TWO_PLAYERS, CALIBRI_FONT, greenText, 72, renderer);
	  renderTexture2(twoPlayer_Button, renderer, SCREEN_WIDTH*0.6, SCREEN_HEIGHT/2.5 + buttonHeight);
	  SDL_RenderPresent(renderer);	 
	  break;
	}
	/* highlight when mouse over AI versus AI button */
	else if(event.motion.x > SCREEN_WIDTH*0.6 && event.motion.x < SCREEN_WIDTH*0.6 + buttonWidth + 40
	   && event.motion.y > SCREEN_HEIGHT/2.5 + 2*buttonHeight + 35 && event.motion.y < SCREEN_HEIGHT/2.5 + 3*buttonHeight){
	  twoPlayer_Button = renderText("AI Versus AI", CALIBRI_FONT, greenText, 72, renderer);
	  renderTexture2(twoPlayer_Button, renderer, SCREEN_WIDTH*0.6, SCREEN_HEIGHT*0.666667);
	  SDL_RenderPresent(renderer);	 
	  break;
	}
	/* default view */
	else{
	  *screenMode = 0;
	  done = 1;
	  break;
	}

      case SDL_MOUSEBUTTONDOWN:
      	if(event.button.button == SDL_BUTTON_LEFT){
      	  x_pos = event.button.x;
	  y_pos = event.button.y;

	  /* one player options */
	  if(x_pos > SCREEN_WIDTH*0.6 && x_pos < SCREEN_WIDTH*0.6 + buttonWidth
	     && y_pos > SCREEN_HEIGHT/2.5 && y_pos < SCREEN_HEIGHT/2.5 + buttonHeight){
	    *screenMode = 1;
	    done = 1;
	    break;
	  }

	  /* two player options */
	  if(x_pos > SCREEN_WIDTH*0.6 && x_pos < SCREEN_WIDTH*0.6 + buttonWidth + 40
	     && y_pos > SCREEN_HEIGHT/2.5 + buttonHeight && y_pos < SCREEN_HEIGHT/2.5 + 2*buttonHeight){
	    *screenMode = 2;
	    done = 1;
	    break;
	  }

	  /* AI versus AI */
	  if(x_pos > SCREEN_WIDTH*0.6 && x_pos < SCREEN_WIDTH*0.6 + buttonWidth
	     && y_pos > SCREEN_HEIGHT/2.5 + 2*buttonHeight && y_pos < SCREEN_HEIGHT/2.5 + 3*buttonHeight){
	    *screenMode = 3;
	    done = 1;
	    break;
	  }
      	}
	else{break;}
      }      
    }    
  }
  return *screenMode;
}


/* function to display the one player menu to the screen */
int drawOnePlayerMenu(SDL_Window *window, SDL_Renderer *renderer, int *screenMode){

  int leftMargin   = 50;
  int rightMargin  = 675;
  int stringWidth  = 0;
  int stringHeight = 0;

  SDL_Color titleColor = {0xA8, 0xC6, 0xDB}; /* this color is static */
  SDL_Color optionColor = {255, 255, 255};/* this color is static */
  SDL_Color buttonColor = {255, 255, 255}; /* this color is dynamic; default white */

  /* rename window title */
  SDL_SetWindowTitle(window, "One Player Options");

  /* create one player background image */
  SDL_Texture *backSplash = NULL;
  backSplash = loadTexture("Assets/Menu_Backgrounds/Background_1600_900.jpg", renderer);
  renderTexture(backSplash, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

  /* create title */
  SDL_Texture *title = renderText(ONE_PLAYER_OPTIONS, CALIBRI_FONT, titleColor, 100, renderer);
  SDL_QueryTexture(title, NULL, NULL, &stringWidth, NULL);
  renderTexture2(title, renderer, (SCREEN_WIDTH - stringWidth)/2, SCREEN_HEIGHT*0);
  
  /* create timer option with buttons */
  /* SDL_Texture *timeOption = renderText("Timer:", CALIBRI_FONT, optionColor, 50, renderer); */
  /* SDL_QueryTexture(timeOption, NULL, NULL, &stringWidth, NULL); */
  /* renderTexture2(timeOption, renderer, leftMargin, SCREEN_HEIGHT/5); */

  /* SDL_Texture *fiveMin_Button = renderText("5 Minutes", CALIBRI_FONT, optionColor, 50, renderer); */
  /* SDL_QueryTexture(fiveMin_Button, NULL, NULL, NULL, &stringHeight); */
  /* renderTexture2(fiveMin_Button, renderer, leftMargin + stringWidth + 25, SCREEN_HEIGHT/5); */
  /* SDL_Texture *fifteenMin_Button = renderText("15 Minutes", CALIBRI_FONT, optionColor, 50, renderer); */
  /* renderTexture2(fifteenMin_Button, renderer, leftMargin + stringWidth + 25, SCREEN_HEIGHT/5 + stringHeight); */
  /* SDL_Texture *sixtyMin_Button = renderText("60 Minutes", CALIBRI_FONT, optionColor, 50, renderer); */
  /* renderTexture2(sixtyMin_Button, renderer, leftMargin + stringWidth + 25, SCREEN_HEIGHT/5 + 2*stringHeight); */
  /* SDL_Texture *off_Button = renderText("Off", CALIBRI_FONT, optionColor, 50, renderer); */
  /* renderTexture2(off_Button, renderer, leftMargin + stringWidth + 25, SCREEN_HEIGHT/5 + 3*stringHeight); */
    
  /* create color options */
  SDL_Texture *colorOption = renderText("Color:", CALIBRI_FONT, optionColor, 50, renderer);
  SDL_QueryTexture(colorOption, NULL, NULL, &stringWidth, NULL);
  SDL_QueryTexture(colorOption, NULL, NULL, NULL, &stringHeight);
  renderTexture2(colorOption, renderer, leftMargin, SCREEN_HEIGHT/5);

  SDL_Texture *black_Button = renderText("Black", CALIBRI_FONT, optionColor, 50, renderer);
  renderTexture2(black_Button, renderer, leftMargin + stringWidth + 25, SCREEN_HEIGHT/5);
  SDL_Texture *white_Button = renderText("White", CALIBRI_FONT, optionColor, 50, renderer);
  renderTexture2(white_Button, renderer, leftMargin + stringWidth + 25, SCREEN_HEIGHT/5 + stringHeight);
  
  /* create difficulty options */
  SDL_Texture *diffOption = renderText("Difficulty:", CALIBRI_FONT, optionColor, 50, renderer);
  SDL_QueryTexture(diffOption, NULL, NULL, &stringWidth, NULL);
  renderTexture2(diffOption, renderer, rightMargin, SCREEN_HEIGHT/5);

  SDL_Texture *easy_Button = renderText("Easy", CALIBRI_FONT, optionColor, 50, renderer);
  renderTexture2(easy_Button, renderer, rightMargin + stringWidth + 25, SCREEN_HEIGHT/5);
  SDL_Texture *moderate_Button = renderText("Moderate", CALIBRI_FONT, optionColor, 50, renderer);
  renderTexture2(moderate_Button, renderer, rightMargin + stringWidth + 25, SCREEN_HEIGHT/5 + stringHeight);
  SDL_Texture *hard_Button = renderText("Challenging", CALIBRI_FONT, optionColor, 50, renderer);
  SDL_QueryTexture(diffOption, NULL, NULL, &stringWidth, NULL);
  renderTexture2(hard_Button, renderer, rightMargin + stringWidth + 25, SCREEN_HEIGHT/5 + 2*stringHeight);

  /* create input options */
  /* SDL_Texture *inputOption = renderText("Input:", CALIBRI_FONT, optionColor, 50, renderer); */
  /* renderTexture2(inputOption, renderer, rightMargin + 75, SCREEN_HEIGHT/5 + 4*stringHeight); */

  /* SDL_Texture *kbd_Button = renderText("Keyboard", CALIBRI_FONT, optionColor, 50, renderer); */
  /* renderTexture2(kbd_Button, renderer, rightMargin + stringWidth + 25, SCREEN_HEIGHT/5 + 4*stringHeight); */
  /* SDL_Texture *mouse_Button = renderText("Mouse", CALIBRI_FONT, optionColor, 50, renderer); */
  /* renderTexture2(mouse_Button, renderer, rightMargin + stringWidth + 25, SCREEN_HEIGHT/5 + 5*stringHeight); */

  /* create main menu button */
  SDL_Texture *mainMenu_Button = renderText("Main Menu", CALIBRI_FONT, buttonColor, 50, renderer);
  renderTexture2(mainMenu_Button, renderer, leftMargin, SCREEN_HEIGHT/5 + 7*stringHeight);

  /* create play button */
  SDL_Texture *play_Button = renderText("Play", CALIBRI_FONT, buttonColor, 50, renderer);
  renderTexture2(play_Button, renderer, SCREEN_WIDTH - leftMargin - stringWidth, SCREEN_HEIGHT/5 + 7*stringHeight);

  SDL_RenderPresent(renderer);

  int done = 0;
  int x_pos = 0, y_pos = 0;

  SDL_Event event;

  while(!done){

    while(SDL_PollEvent(&event)){

      switch(event.type){

      case SDL_QUIT:
	*screenMode = 100;
	done = 1;
	break;
      case SDL_KEYUP:
	if(event.key.keysym.sym == SDLK_ESCAPE){
	  *screenMode = 100;
	  done = 1;
	}
	break;
 
      case SDL_MOUSEBUTTONDOWN:
      	if(event.button.button == SDL_BUTTON_LEFT){
      	  x_pos = event.button.x;
	  y_pos = event.button.y;
	  
	  /* go back to main menu */
	  if(x_pos > leftMargin && x_pos < leftMargin + stringWidth + 50
	     && y_pos > SCREEN_HEIGHT/5 + 7*stringHeight && y_pos < SCREEN_HEIGHT/5 + 8*stringHeight){	   
	    *screenMode = 0;
	    done = 1;
	    break;
	  }

	  /* go to gameplay screen */
	  if(x_pos > SCREEN_WIDTH - leftMargin - stringWidth && x_pos < SCREEN_WIDTH - 3*leftMargin
	     && y_pos > SCREEN_HEIGHT/5 + 7*stringHeight && y_pos < SCREEN_HEIGHT/5 + 8*stringHeight){	   
	    *screenMode = 3;
	    done = 1;
	    break;
	  }

	  /* color choices */    /* working: interface with data structure (color choice) here */
	  /* black */
	  /* if(x_pos > leftMargin + stringWidth - 50  && x_pos < leftMargin + 2*stringWidth - 130 */
	  /*    && y_pos > SCREEN_HEIGHT/5 && y_pos < SCREEN_HEIGHT/5 + stringHeight){ */
	   
	  /*   done = 1; */
	  /*   break; */
	  /* } */

	  /* white */
	  /* if(x_pos > leftMargin + stringWidth - 50  && x_pos < leftMargin + 2*stringWidth - 115 */
	  /*    && y_pos > SCREEN_HEIGHT/5 + stringHeight && y_pos < SCREEN_HEIGHT/5 + 2*stringHeight){ */
	 
	  /*   done = 1; */
	  /*   break; */
	  /* } */

	  /* difficulty choices*/  /* working: interface with data structure (color choice) here */
	  /* easy */
	  /* if(x_pos > rightMargin + stringWidth + 25 && x_pos < rightMargin + 2*stringWidth - 70 */
	  /*    && y_pos > SCREEN_HEIGHT/5 && y_pos < SCREEN_HEIGHT/5 + stringHeight){ */
	   
	  /*   done = 1; */
	  /*   break; */
	  /* } */

	  /* moderate */
	  /* if(x_pos > rightMargin + stringWidth + 25 && x_pos < rightMargin + 2*stringWidth + 40 */
	  /*    && y_pos > SCREEN_HEIGHT/5 + stringHeight && y_pos < SCREEN_HEIGHT/5 + 2*stringHeight){ */
	   
	  /*   done = 1; */
	  /*   break; */
	  /* } */

	  /* challenging */
	  /* if(x_pos > rightMargin + stringWidth + 25 && x_pos < rightMargin + 2*stringWidth + 75 */
	  /*    && y_pos > SCREEN_HEIGHT/5 + 2*stringHeight && y_pos < SCREEN_HEIGHT/5 + 3*stringHeight){ */
	   
	  /*   done = 1; */
	  /*   break; */
	  /* } */

	}
	else{break;}
      }    
    }
  }
  return *screenMode;
}
/* function to display the two player menu to the screen */
int drawTwoPlayerMenu(SDL_Window *window, SDL_Renderer *renderer, int *screenMode){

  int leftMargin   = 50;
  int rightMargin  = 675;
  int stringWidth  = 0;
  int stringHeight = 0;

  SDL_Color titleColor = {0xA8, 0xC6, 0xDB}; /* this color is static */
  SDL_Color optionColor = {255, 255, 255};/* this color is static */
  SDL_Color buttonColor = {255, 255, 255}; /* this color is dynamic; default white */

  /* rename window title */
  SDL_SetWindowTitle(window, "Two Player Options");

  /* create two player background image */
  SDL_Texture *backSplash = NULL;
  backSplash = loadTexture("Assets/Menu_Backgrounds/Background_1600_900.jpg", renderer);
  renderTexture(backSplash, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

  /* create title */
  SDL_Texture *title = renderText("Two Player Options", CALIBRI_FONT, titleColor, 100, renderer);
  SDL_QueryTexture(title, NULL, NULL, &stringWidth, NULL);
  renderTexture2(title, renderer, (SCREEN_WIDTH - stringWidth)/2, SCREEN_HEIGHT*0);

  /* create timer option with buttons */
  SDL_Texture *timeOption = renderText("Timer:", CALIBRI_FONT, optionColor, 50, renderer);
  SDL_QueryTexture(timeOption, NULL, NULL, &stringWidth, NULL);
  renderTexture2(timeOption, renderer, leftMargin, SCREEN_HEIGHT/5);

  SDL_Texture *fiveMin_Button = renderText("5 Minutes", CALIBRI_FONT, optionColor, 50, renderer);
  SDL_QueryTexture(fiveMin_Button, NULL, NULL, NULL, &stringHeight);
  renderTexture2(fiveMin_Button, renderer, leftMargin + stringWidth + 25, SCREEN_HEIGHT/5);
  SDL_Texture *fifteenMin_Button = renderText("15 Minutes", CALIBRI_FONT, optionColor, 50, renderer);
  renderTexture2(fifteenMin_Button, renderer, leftMargin + stringWidth + 25, SCREEN_HEIGHT/5 + stringHeight);
  SDL_Texture *sixtyMin_Button = renderText("60 Minutes", CALIBRI_FONT, optionColor, 50, renderer);
  renderTexture2(sixtyMin_Button, renderer, leftMargin + stringWidth + 25, SCREEN_HEIGHT/5 + 2*stringHeight);
  SDL_Texture *off_Button = renderText("Off", CALIBRI_FONT, optionColor, 50, renderer);
  renderTexture2(off_Button, renderer, leftMargin + stringWidth + 25, SCREEN_HEIGHT/5 + 3*stringHeight);

  /* create input options */
  SDL_Texture *inputOption = renderText("Input:", CALIBRI_FONT, optionColor, 50, renderer);
  SDL_QueryTexture(inputOption, NULL, NULL, &stringWidth, NULL);
  renderTexture2(inputOption, renderer, rightMargin, SCREEN_HEIGHT/5);

  SDL_Texture *kbd_Button = renderText("Keyboard", CALIBRI_FONT, optionColor, 50, renderer);
  renderTexture2(kbd_Button, renderer, rightMargin + stringWidth + 25, SCREEN_HEIGHT/5);
  SDL_Texture *mouse_Button = renderText("Mouse", CALIBRI_FONT, optionColor, 50, renderer);
  renderTexture2(mouse_Button, renderer, rightMargin + stringWidth + 25, SCREEN_HEIGHT/5 + stringHeight);

  /* create main menu button */
  SDL_Texture *mainMenu_Button = renderText("Main Menu", CALIBRI_FONT, buttonColor, 50, renderer);
  renderTexture2(mainMenu_Button, renderer, leftMargin, SCREEN_HEIGHT/5 + 7*stringHeight);

  /* create play button */
  SDL_Texture *play_Button = renderText("Play", CALIBRI_FONT, buttonColor, 50, renderer);
  renderTexture2(play_Button, renderer, SCREEN_WIDTH - leftMargin - stringWidth, SCREEN_HEIGHT/5 + 7*stringHeight);

  SDL_RenderPresent(renderer);

  int done = 0;
  int x_pos = 0, y_pos = 0;

  SDL_Event event;

  while(!done){

    while(SDL_PollEvent(&event)){

      switch(event.type){

      case SDL_QUIT:
	*screenMode = 100;
	done = 1;
	break;
      case SDL_KEYUP:
	if(event.key.keysym.sym == SDLK_ESCAPE){
	  *screenMode = 100;
	  done = 1;
	}
	break;
 
      case SDL_MOUSEBUTTONDOWN:
      	if(event.button.button == SDL_BUTTON_LEFT){
	  /* get position of mouse click */
      	  x_pos = event.button.x;
	  y_pos = event.button.y;

	  /* go to gameplay screen */
	  if(x_pos > SCREEN_WIDTH - leftMargin - stringWidth && x_pos < SCREEN_WIDTH - leftMargin
	     && y_pos > SCREEN_HEIGHT/5 + 7*stringHeight && y_pos < SCREEN_HEIGHT/5 + 8*stringHeight){
	    *screenMode = 3;
	    done = 1;
	    break;
	  }
	  /* go back to main menu */
	  if(x_pos > leftMargin && x_pos < leftMargin + stringWidth + 125
	     && y_pos > SCREEN_HEIGHT/5 + 7*stringHeight && y_pos < SCREEN_HEIGHT/5 + 8*stringHeight){	   
	    *screenMode = 0;
	    done = 1;
	    break;
	  }	 
	 
      	}
	else{break;}
      }      
    }    
  }
  return *screenMode;
}

/* function to display the advanced menu to the screen */
void drawAdvancedMenu(SDL_Window *window, SDL_Renderer *renderer){

  int margin         = 0;
  int titleWidth     = 0;
  int buttonWidth    = 0;
  int buttonHeight   = 0;

  SDL_Color titleColor = {0xA8, 0xC6, 0xDB}; /* this color is static */
  SDL_Color buttonColor = {255, 255, 255}; /* this color is dynamic; default white */

  margin = SCREEN_WIDTH/2 + 25;

  /* rename window title */
  SDL_SetWindowTitle(window, "Advanced Options");

  /* create two player background image */
  SDL_Texture *backSplash = NULL;
  backSplash = loadTexture("Assets/Menu_Backgrounds/Background_1600_900.jpg", renderer);
  renderTexture(backSplash, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

  /* create title */
  SDL_Texture *title = renderText("Advanced Options", CALIBRI_FONT, titleColor, 100, renderer);
  SDL_QueryTexture(title, NULL, NULL, &titleWidth, NULL);
  renderTexture2(title, renderer, (SCREEN_WIDTH - titleWidth)/2, SCREEN_HEIGHT*0);

  /* create board setup button */
  SDL_Texture *boardSetup_Button = renderText("Interactive Board Setup", CALIBRI_FONT, buttonColor, 50, renderer);
  SDL_QueryTexture(boardSetup_Button, NULL, NULL, &buttonWidth, NULL);
  SDL_QueryTexture(boardSetup_Button, NULL, NULL, NULL, &buttonHeight);
  renderTexture2(boardSetup_Button, renderer, margin, SCREEN_HEIGHT/4);

  /* create demo button */
  SDL_Texture *demo_Button = renderText("Demo", CALIBRI_FONT, buttonColor, 50, renderer);
  renderTexture2(demo_Button, renderer, margin + 150, SCREEN_HEIGHT/4 + 2*buttonHeight);
  
  /* create main menu button */
  SDL_Texture *mainMenu_Button = renderText("Main Menu", CALIBRI_FONT, buttonColor, 50, renderer);
  renderTexture2(mainMenu_Button, renderer, margin + 100, SCREEN_HEIGHT/4 + 4*buttonHeight);

  SDL_RenderPresent(renderer);
}

/* function to display the gameplay window to the screen */
void drawGameplayScreen(SDL_Window *window, SDL_Renderer *renderer){

  int tileSize = BOARD_WIDTH / 8;
  int leftMargin = 30;
  int buttonWidth = 0, buttonHeight =0;
  SDL_Color buttonColor = {255, 255, 255};   /* this color is dynamic */

  /* rename window title */
  SDL_SetWindowTitle(window, TITLE);

  /* reset background color */
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderClear(renderer);

  /* display board with pieces at starting position */
  drawChessboard(renderer);
  drawPieces(renderer);

  /* display game log button */
  SDL_Texture *gameLog_Button = renderText("Game Log", CALIBRI_FONT, buttonColor, 30, renderer);
  SDL_QueryTexture(gameLog_Button, NULL, NULL, &buttonWidth, NULL);
  SDL_QueryTexture(gameLog_Button, NULL, NULL, NULL, &buttonHeight);
  renderTexture2(gameLog_Button, renderer, SCREEN_WIDTH - buttonWidth*2, SCREEN_HEIGHT/2 - 4*tileSize);

  /* display move hints button */
  /* SDL_Texture *moveHints_Button = renderText("Move Hints", CALIBRI_FONT, buttonColor, 30, renderer); */
  /* renderTexture2(moveHints_Button, renderer, SCREEN_WIDTH - buttonWidth*2, SCREEN_HEIGHT/2 - 3*tileSize); */

  /* display undo move button */
  /* SDL_Texture *undoMove_Button = renderText("Undo Move", CALIBRI_FONT, buttonColor, 30, renderer); */
  /* renderTexture2(undoMove_Button, renderer, SCREEN_WIDTH - buttonWidth*2, SCREEN_HEIGHT/2 - 2*tileSize); */

  /* display pause button */
  SDL_Texture *pause_Button = renderText("Pause", CALIBRI_FONT, buttonColor, 30, renderer);
  renderTexture2(pause_Button, renderer, leftMargin, SCREEN_HEIGHT - 175);

  /* display quit button */
  SDL_Texture *quit_Button = renderText("Quit", CALIBRI_FONT, buttonColor, 30, renderer);
  renderTexture2(quit_Button, renderer, leftMargin, SCREEN_HEIGHT - 175 + 2*buttonHeight);

  /* display piece input header */
  /* SDL_Texture *pieceHeader = renderText("Piece", CALIBRI_FONT, buttonColor, 30, renderer); */
  /* SDL_QueryTexture(pieceHeader, NULL, NULL, &buttonWidth, NULL); */
  /* renderTexture2(pieceHeader, renderer, leftMargin, SCREEN_HEIGHT/2); */

  /* display piece input window */

  /* display move to input header */
  /* SDL_Texture *moveToHeader = renderText("Move To", CALIBRI_FONT, buttonColor, 30, renderer); */
  /* renderTexture2(moveToHeader, renderer, leftMargin + buttonWidth + 25, SCREEN_HEIGHT/2); */

  /* display move to input window */

  /* display left side player window */
  drawLeftPlayerWindow(renderer, tileSize, 1);

  /* display right side player window */
  drawRightPlayerWindow(renderer, tileSize, 1);

  SDL_RenderPresent(renderer);
}

void drawLeftPlayerWindow(SDL_Renderer *renderer, int tileSize, int playerMode){

  int margin = 30;
  int headerWidth = 0, headerHeight = 0;
  SDL_Rect headerWinL, pieceWinL;
  SDL_Color headerColor = {0, 0, 0};
  SDL_Texture *piece = NULL;

  /* using int playerMode for: 1=one player, 2=two players, 3=AIvAI */

  headerWinL.x = margin; 
  headerWinL.y = SCREEN_HEIGHT/2 - 4*tileSize;
  headerWinL.w = 3*tileSize;
  headerWinL.h = tileSize;

  SDL_SetRenderDrawColor(renderer, 0xA8, 0xC6, 0xDB, 0xDB);
  SDL_RenderFillRect(renderer, &headerWinL);

  pieceWinL.x = margin;
  pieceWinL.y = SCREEN_HEIGHT/2 - 3*tileSize; 
  pieceWinL.w = 3*tileSize;
  pieceWinL.h = 2*tileSize;

  SDL_SetRenderDrawColor(renderer, 0x7B, 0xAD, 0xDB, 0xDB);
  SDL_RenderFillRect(renderer, &pieceWinL);

  /* draw grid */
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderDrawLine(renderer, margin, SCREEN_HEIGHT/2 - 3*tileSize, margin + 3*tileSize, SCREEN_HEIGHT/2 - 3*tileSize);
  SDL_RenderDrawLine(renderer, margin, SCREEN_HEIGHT/2 - 2*tileSize, margin + 3*tileSize, SCREEN_HEIGHT/2 - 2*tileSize);  
  SDL_RenderDrawLine(renderer, margin + tileSize, SCREEN_HEIGHT/2 - 3*tileSize, margin + tileSize, SCREEN_HEIGHT/2 - tileSize);
  SDL_RenderDrawLine(renderer, margin + 2*tileSize, SCREEN_HEIGHT/2 - 3*tileSize, margin + 2*tileSize, SCREEN_HEIGHT/2 - tileSize);

  /* display player 2 header */
  SDL_Texture *playerTwoHeader = renderText("P l a y e r  2", CALIBRI_FONT, headerColor, 30, renderer);
  SDL_QueryTexture(playerTwoHeader, NULL, NULL, &headerWidth, NULL);
  SDL_QueryTexture(playerTwoHeader, NULL, NULL, NULL, &headerHeight);
  renderTexture2(playerTwoHeader, renderer, margin + 40, SCREEN_HEIGHT/2 - 4*tileSize);

  /* display timer */
  SDL_Texture *playerTwoTimer = renderText("5:00", CALIBRI_FONT, headerColor, 30, renderer);
  renderTexture2(playerTwoTimer, renderer, margin + 80, SCREEN_HEIGHT/2 - 3.5*tileSize);  

  /* display captured pieces */
  piece = loadTexture("Assets/pieces/W_Pawn.png", renderer);
  renderTexture(piece, renderer, margin, SCREEN_HEIGHT/2 - 3*tileSize, tileSize, tileSize);
  piece = loadTexture("Assets/pieces/W_Rook.png", renderer);
  renderTexture(piece, renderer, margin + tileSize, SCREEN_HEIGHT/2 - 3*tileSize, tileSize, tileSize);
  piece = loadTexture("Assets/pieces/W_Knight.png", renderer);
  renderTexture(piece, renderer, margin + 2*tileSize, SCREEN_HEIGHT/2 - 3*tileSize, tileSize, tileSize);
  piece = loadTexture("Assets/pieces/W_Bishop.png", renderer);
  renderTexture(piece, renderer, margin, SCREEN_HEIGHT/2 - 2*tileSize, tileSize, tileSize);
  piece = loadTexture("Assets/pieces/W_Queen.png", renderer);
  renderTexture(piece, renderer, margin + tileSize, SCREEN_HEIGHT/2 - 2*tileSize, tileSize, tileSize);

  /* display capture counts */
  SDL_Texture *pawnCaptureCount = renderText("0", CALIBRI_FONT, headerColor, 20, renderer);
  renderTexture2(pawnCaptureCount, renderer, margin + 5, SCREEN_HEIGHT/2 - 3*tileSize);
  SDL_Texture *rookCaptureCount = renderText("0", CALIBRI_FONT, headerColor, 20, renderer);
  renderTexture2(rookCaptureCount, renderer, margin + 5 + tileSize, SCREEN_HEIGHT/2 - 3*tileSize);
  SDL_Texture *knightCaptureCount = renderText("0", CALIBRI_FONT, headerColor, 20, renderer);
  renderTexture2(knightCaptureCount, renderer, margin + 5 + 2*tileSize, SCREEN_HEIGHT/2 - 3*tileSize);
  SDL_Texture *bishopCaptureCount = renderText("0", CALIBRI_FONT, headerColor, 20, renderer);
  renderTexture2(bishopCaptureCount, renderer, margin + 5, SCREEN_HEIGHT/2 - 2*tileSize);
  SDL_Texture *queenCaptureCount = renderText("0", CALIBRI_FONT, headerColor, 20, renderer);
  renderTexture2(rookCaptureCount, renderer, margin + 5 + tileSize, SCREEN_HEIGHT/2 - 2*tileSize);    
}

void drawRightPlayerWindow(SDL_Renderer *renderer, int tileSize, int playerMode){

  int xMargin = SCREEN_WIDTH - 3*tileSize - 30;
  int yMargin = SCREEN_HEIGHT/2 + tileSize;
  int headerWidth = 0, headerHeight = 0;
  SDL_Rect headerWinR, pieceWinR;
  SDL_Color headerColor = {0, 0, 0};
  SDL_Texture *piece = NULL;

  /* using int playerMode for: 1=one player, 2=two players, 3=AIvAI */

  headerWinR.x = xMargin; 
  headerWinR.y = yMargin;
  headerWinR.w = 3*tileSize;
  headerWinR.h = tileSize;

  SDL_SetRenderDrawColor(renderer, 0xA8, 0xC6, 0xDB, 0xDB);
  SDL_RenderFillRect(renderer, &headerWinR);

  pieceWinR.x = xMargin;
  pieceWinR.y = yMargin + tileSize;
  pieceWinR.w = 3*tileSize;
  pieceWinR.h = 2*tileSize;

  SDL_SetRenderDrawColor(renderer, 0x7B, 0xAD, 0xDB, 0xDB);
  SDL_RenderFillRect(renderer, &pieceWinR);

  /* draw grid */
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderDrawLine(renderer, xMargin, yMargin + tileSize, xMargin + 3*tileSize, yMargin + tileSize);
  SDL_RenderDrawLine(renderer, xMargin, yMargin + 2*tileSize, xMargin + 3*tileSize, yMargin + 2*tileSize);
  SDL_RenderDrawLine(renderer, xMargin + tileSize, yMargin + tileSize, xMargin + tileSize, yMargin +3*tileSize);
  SDL_RenderDrawLine(renderer, xMargin + 2*tileSize, yMargin + tileSize, xMargin + 2*tileSize, yMargin + 3*tileSize);

  /* display player 1 header */
  SDL_Texture *playerOneHeader = renderText("P l a y e r  1", CALIBRI_FONT, headerColor, 30, renderer);
  SDL_QueryTexture(playerOneHeader, NULL, NULL, &headerWidth, NULL);
  SDL_QueryTexture(playerOneHeader, NULL, NULL, NULL, &headerHeight);
  renderTexture2(playerOneHeader, renderer, xMargin + 40, yMargin);

  /* display timer */
  SDL_Texture *playerOneTimer = renderText("5:00", CALIBRI_FONT, headerColor, 30, renderer);
  renderTexture2(playerOneTimer, renderer, xMargin + 80, yMargin + 0.5*tileSize);

  /* display captured pieces */
  piece = loadTexture("Assets/pieces/B_Pawn.png", renderer);
  renderTexture(piece, renderer, xMargin, yMargin + tileSize, tileSize, tileSize);
  piece = loadTexture("Assets/pieces/B_Rook.png", renderer);
  renderTexture(piece, renderer, xMargin + tileSize, yMargin + tileSize, tileSize, tileSize);
  piece = loadTexture("Assets/pieces/B_Knight.png", renderer);
  renderTexture(piece, renderer, xMargin + 2*tileSize, yMargin + tileSize, tileSize, tileSize);
  piece = loadTexture("Assets/pieces/B_Bishop.png", renderer);
  renderTexture(piece, renderer, xMargin, yMargin + 2*tileSize, tileSize, tileSize);
  piece = loadTexture("Assets/pieces/B_Queen.png", renderer);
  renderTexture(piece, renderer, xMargin + tileSize, yMargin +  2*tileSize, tileSize, tileSize);

  /* display capture counts */
  SDL_Texture *pawnCaptureCount = renderText("0", CALIBRI_FONT, headerColor, 20, renderer);
  renderTexture2(pawnCaptureCount, renderer, xMargin + 5, yMargin + tileSize);
  SDL_Texture *rookCaptureCount = renderText("0", CALIBRI_FONT, headerColor, 20, renderer);
  renderTexture2(rookCaptureCount, renderer, xMargin + 5 + tileSize, yMargin + tileSize);
  SDL_Texture *knightCaptureCount = renderText("0", CALIBRI_FONT, headerColor, 20, renderer);
  renderTexture2(knightCaptureCount, renderer, xMargin + 5 + 2*tileSize, yMargin + tileSize);
  SDL_Texture *bishopCaptureCount = renderText("0", CALIBRI_FONT, headerColor, 20, renderer);
  renderTexture2(bishopCaptureCount, renderer, xMargin + 5, yMargin + 2*tileSize);
  SDL_Texture *queenCaptureCount = renderText("0", CALIBRI_FONT, headerColor, 20, renderer);
  renderTexture2(queenCaptureCount, renderer, xMargin + 5 + tileSize, yMargin + 2*tileSize); 
}

/* function to display a blank chessboard to the screen */
void drawChessboard(SDL_Renderer *renderer){

  SDL_Color positionColor = {255, 255, 255}; /* this color is static */

  SDL_Rect whiteTile, blackTile;
  whiteTile.w = BOARD_WIDTH / 8;
  whiteTile.h = BOARD_HEIGHT / 8;
  blackTile.w = BOARD_WIDTH / 8;
  blackTile.h = BOARD_HEIGHT / 8;
  int tileSize = whiteTile.w;
  int i,j;  
  
  for(i = 0; i < 8; i++){
    
    for(j = 0; j < 8; j++){
      whiteTile.x = j * tileSize + SCREEN_WIDTH/2 - 4*tileSize;
      whiteTile.y = i * tileSize + SCREEN_HEIGHT/2 - 4*tileSize;
      blackTile.x = j * tileSize + SCREEN_WIDTH/2 - 4*tileSize;
      blackTile.y = i * tileSize + SCREEN_HEIGHT/2 - 4*tileSize;
      
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

  /* display chessboard horizontal coordinates */
    SDL_Texture *num = renderText("1", CALIBRI_FONT, positionColor, 22, renderer);
    renderTexture2(num, renderer, 280, SCREEN_HEIGHT - tileSize - 20);     
    num = renderText("2", CALIBRI_FONT, positionColor, 22, renderer);
    renderTexture2(num, renderer, 280, SCREEN_HEIGHT - 2*tileSize - 20);     
    num = renderText("3", CALIBRI_FONT, positionColor, 22, renderer);
    renderTexture2(num, renderer, 280, SCREEN_HEIGHT - 3*tileSize - 20);
    num = renderText("4", CALIBRI_FONT, positionColor, 22, renderer);
    renderTexture2(num, renderer, 280, SCREEN_HEIGHT - 4*tileSize - 20);
    num = renderText("5", CALIBRI_FONT, positionColor, 22, renderer);
    renderTexture2(num, renderer, 280, SCREEN_HEIGHT - 5*tileSize - 20);
    num = renderText("6", CALIBRI_FONT, positionColor, 22, renderer);
    renderTexture2(num, renderer, 280, SCREEN_HEIGHT - 6*tileSize - 20);
    num = renderText("7", CALIBRI_FONT, positionColor, 22, renderer);
    renderTexture2(num, renderer, 280, SCREEN_HEIGHT - 7*tileSize - 20);
    num = renderText("8", CALIBRI_FONT, positionColor, 22, renderer);
    renderTexture2(num, renderer, 280, SCREEN_HEIGHT - 8*tileSize - 20);

    /* display chessboard vertical coordinates */
    SDL_Texture *alpha = renderText("A", CALIBRI_FONT, positionColor, 22, renderer);
    renderTexture2(alpha, renderer, (SCREEN_WIDTH - BOARD_WIDTH)/2 + 0.4*tileSize, SCREEN_HEIGHT - 35);     
    alpha = renderText("B", CALIBRI_FONT, positionColor, 22, renderer);
    renderTexture2(alpha, renderer, (SCREEN_WIDTH - BOARD_WIDTH)/2 + 1.4*tileSize, SCREEN_HEIGHT - 35);     
    alpha = renderText("C", CALIBRI_FONT, positionColor, 22, renderer);
    renderTexture2(alpha, renderer, (SCREEN_WIDTH - BOARD_WIDTH)/2 + 2.4*tileSize, SCREEN_HEIGHT - 35);     
    alpha = renderText("D", CALIBRI_FONT, positionColor, 22, renderer);
    renderTexture2(alpha, renderer, (SCREEN_WIDTH - BOARD_WIDTH)/2 + 3.4*tileSize, SCREEN_HEIGHT - 35);     
    alpha = renderText("E", CALIBRI_FONT, positionColor, 22, renderer);
    renderTexture2(alpha, renderer, (SCREEN_WIDTH - BOARD_WIDTH)/2 + 4.4*tileSize, SCREEN_HEIGHT - 35);     
    alpha = renderText("F", CALIBRI_FONT, positionColor, 22, renderer);
    renderTexture2(alpha, renderer, (SCREEN_WIDTH - BOARD_WIDTH)/2 + 5.4*tileSize, SCREEN_HEIGHT - 35);     
    alpha = renderText("G", CALIBRI_FONT, positionColor, 22, renderer);
    renderTexture2(alpha, renderer, (SCREEN_WIDTH - BOARD_WIDTH)/2 + 6.4*tileSize, SCREEN_HEIGHT - 35);     
    alpha = renderText("H", CALIBRI_FONT, positionColor, 22, renderer);
    renderTexture2(alpha, renderer, (SCREEN_WIDTH - BOARD_WIDTH)/2 + 7.4*tileSize, SCREEN_HEIGHT - 35);     
}

/* function to display the pieces in beginning position on the chessboard */
void drawPieces(SDL_Renderer *renderer){
    
  int i=0;
  int x_Offset = 0, y_Offset = 0;
  int pieceSize = 0;
  SDL_Texture *piece = NULL;

  pieceSize = BOARD_WIDTH/8;
  x_Offset = SCREEN_WIDTH/2 - 4*pieceSize;
  y_Offset  = SCREEN_HEIGHT/2 - 4*pieceSize;

  // black pawns
  piece = loadTexture("Assets/pieces/B_Pawn.png", renderer);
  for(i=0; i<8; i++){
    renderTexture(piece, renderer, pieceSize*i + x_Offset, pieceSize + y_Offset, pieceSize, pieceSize);
  }
  
  // black rooks
  piece = loadTexture("Assets/pieces/B_Rook.png", renderer);
  renderTexture(piece, renderer, x_Offset, y_Offset, pieceSize, pieceSize);
  renderTexture(piece, renderer, pieceSize*7 + x_Offset, y_Offset, pieceSize, pieceSize);
  
  // black knights
  piece = loadTexture("Assets/pieces/B_Knight.png", renderer);
  renderTexture(piece, renderer, pieceSize + x_Offset, y_Offset, pieceSize, pieceSize);
  renderTexture(piece, renderer, pieceSize*6 + x_Offset, y_Offset, pieceSize, pieceSize);
  
  // black bishops
  piece = loadTexture("Assets/pieces/B_Bishop.png", renderer);
  renderTexture(piece, renderer, pieceSize*2 + x_Offset, y_Offset, pieceSize, pieceSize);
  renderTexture(piece, renderer, pieceSize*5 + x_Offset, y_Offset, pieceSize, pieceSize);
  
  // black king
  piece = loadTexture("Assets/pieces/B_King.png", renderer);
  renderTexture(piece, renderer, pieceSize*4 + x_Offset, y_Offset, pieceSize, pieceSize);
  
  // black queen
  piece = loadTexture("Assets/pieces/B_Queen.png", renderer);
  renderTexture(piece, renderer, pieceSize*3 + x_Offset, y_Offset, pieceSize, pieceSize);
  
  // white pawns
  piece = loadTexture("Assets/pieces/W_Pawn.png", renderer);
  for(i=0; i<8; i++){
    renderTexture(piece, renderer, pieceSize*i + x_Offset, pieceSize*6 + y_Offset, pieceSize, pieceSize);
  }
    
  // white rooks
  piece = loadTexture("Assets/pieces/W_Rook.png", renderer);
  renderTexture(piece, renderer, x_Offset, pieceSize*7 + y_Offset, pieceSize, pieceSize);
  renderTexture(piece, renderer, pieceSize*7 + x_Offset, pieceSize*7 + y_Offset, pieceSize, pieceSize);
  
  // white knights
  piece = loadTexture("Assets/pieces/W_Knight.png", renderer);
  renderTexture(piece, renderer, pieceSize + x_Offset, pieceSize*7 + y_Offset, pieceSize, pieceSize);
  renderTexture(piece, renderer, pieceSize*6 + x_Offset, pieceSize*7 + y_Offset, pieceSize, pieceSize);
  
  // white bishops
  piece = loadTexture("Assets/pieces/W_Bishop.png", renderer);
  renderTexture(piece, renderer, pieceSize*2 + x_Offset, pieceSize*7 + y_Offset, pieceSize, pieceSize);
  renderTexture(piece, renderer, pieceSize*5 + x_Offset, pieceSize*7 + y_Offset, pieceSize, pieceSize);
  
  // white king
  piece = loadTexture("Assets/pieces/W_King.png", renderer);
  renderTexture(piece, renderer, pieceSize*4 + x_Offset, pieceSize*7 + y_Offset, pieceSize, pieceSize);
  
  // white queen
  piece = loadTexture("Assets/pieces/W_Queen.png", renderer);
  renderTexture(piece, renderer, pieceSize*3 + x_Offset, pieceSize*7 + y_Offset, pieceSize, pieceSize);
}


/* function to uninitialize SDL systems */
void clean(){
   
  TTF_Quit();
  SDL_Quit();
}
