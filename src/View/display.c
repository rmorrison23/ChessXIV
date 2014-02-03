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

#ifdef QUAN_VERSION

/* QUAN_VERSION: function to display the main menu to the screen */
void drawMainMenu(ViewHandle * MainHandle){

  void ObjectHandleList_DeepFree(ObjectHandleList * List);
	
	SDL_Window * window = MainHandle->CurrentWindow->Window;
	SDL_Renderer * renderer = MainHandle->CurrentWindow->WindowRenderer;
	
	SDL_Color greenText = {0x29, 0xEF, 0x48};

	/* rename window title */
	SDL_SetWindowTitle(window, "quan's title");
	/* create main menu background image */
	ObjectHandle * backSplashObject = ObjectHandle_Initialize(Image, Background, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	printf("%d  %d\n", backSplashObject->Width, backSplashObject->Height);
	strcpy(backSplashObject->ImageFileName, "Assets/Menu_Backgrounds/Background_1600_900.jpg");

	ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, backSplashObject);


	/* create title */
	int titleSize = 200;
	SDL_Color titleColor = {0xA8, 0xC6, 0xDB};
	ObjectHandle * title = ObjectHandle_Initialize(Text, Title, (SCREEN_WIDTH - TITLE_WIDTH)/2, 0, 0, 0);

	strcpy(title->String, "C h e s s  X I V");

	strcpy(title->FontName, "Assets/fonts/Calibri.ttf");
	title->Color 	= titleColor;
	title->TextSize = titleSize;
	title->Tag = Title;

	ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, title);
 
	/* one player button */
	int onePlayerSize = 72;
	SDL_Color onePlayerColor = {255, 255, 255};
	ObjectHandle *onePlayerButton = ObjectHandle_Initialize(Button, Option_OnePlayer, SCREEN_WIDTH*0.6, SCREEN_HEIGHT/2.5, 0, 0);

	strcpy(onePlayerButton->String, "One Player");


	strcpy(onePlayerButton->FontName, "Assets/fonts/Calibri.ttf");
	onePlayerButton->Color = onePlayerColor;
	onePlayerButton->TextSize = onePlayerSize;

	ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, onePlayerButton);

	/* two player button */
	int twoPlayerSize = 72;
	SDL_Color twoPlayerColor = {255, 255, 255};
	ObjectHandle *twoPlayerButton = ObjectHandle_Initialize(Button, Option_TwoPlayer, SCREEN_WIDTH*0.6, (SCREEN_HEIGHT*0.666667 - 90), 0, 0);

	strcpy(twoPlayerButton->String, "Two Players");

	strcpy(twoPlayerButton->FontName, "Assets/fonts/Calibri.ttf");
	twoPlayerButton->Color = twoPlayerColor;
	twoPlayerButton->TextSize = twoPlayerSize;


	ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, twoPlayerButton);	

	/* AI versus AI button */
	int AIversusAISize = 72;
	SDL_Color AIversusAIColor = {255, 255, 255};
	ObjectHandle *AIversusAIButton = ObjectHandle_Initialize(Button, Option_AIvsAI, SCREEN_WIDTH*0.6, SCREEN_HEIGHT*0.666667, 0, 0);

	strcpy(AIversusAIButton->String, "AI and AI");
	strcpy(AIversusAIButton->FontName, "Assets/fonts/Calibri.ttf");
	AIversusAIButton->Color = AIversusAIColor;
	AIversusAIButton->TextSize = AIversusAISize;
	

	ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, AIversusAIButton);
  
	windowRender(MainHandle);
		
#if 0
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

#endif
  
}

void drawOnePlayerMenu(ViewHandle * MainHandle){

  void ObjectHandleList_DeepFree(ObjectHandleList * List);

  SDL_Window * window = MainHandle->CurrentWindow->Window;

  /* rename window title */
  SDL_SetWindowTitle(window, "One Player Options");

  /* create one player background image */
  ObjectHandle * backSplashObject = ObjectHandle_Initialize(Image, Background, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  printf("%d  %d\n", backSplashObject->Width, backSplashObject->Height);
  strcpy(backSplashObject->ImageFileName, "Assets/Menu_Backgrounds/Background_1600_900.jpg");  
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, backSplashObject);

  /* screen title */
  int onePlayOptionsSize = SDL_INT_TEXT_SIZE*2;
  SDL_Color onePlayOptionsColor = SDL_COLOR_SCREEN_TITLE;
  ObjectHandle *onePlayOptions = ObjectHandle_Initialize(Text, Title, 75, SCREEN_HEIGHT*0, 0, 0);
  strcpy(onePlayOptions->String, "ONE PLAYER OPTIONS");
  strcpy(onePlayOptions->FontName, "Assets/fonts/Calibri.ttf");
  onePlayOptions->Color = onePlayOptionsColor;
  onePlayOptions->TextSize = onePlayOptionsSize;  
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, onePlayOptions);

  /* color label */
  int colorLabelSize = SDL_INT_TEXT_SIZE;
  SDL_Color colorLabelColor = SDL_COLOR_NORMAL_BUTTON;
  ObjectHandle *colorLabel = ObjectHandle_Initialize(Text, Label_Color, 50, SCREEN_HEIGHT/5, 0, 0);
  strcpy(colorLabel->String, "Color: ");
  strcpy(colorLabel->FontName, "Assets/fonts/Calibri.ttf");
  colorLabel->Color = colorLabelColor;
  colorLabel->TextSize = colorLabelSize;  
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, colorLabel);

  /* black button */
  int blackButtonSize = SDL_INT_TEXT_SIZE;
  SDL_Color blackButtonColor = SDL_COLOR_NORMAL_BUTTON;
  ObjectHandle *blackButton = ObjectHandle_Initialize(Button, Option_Black, 200, SCREEN_HEIGHT/5, 0, 0);
  strcpy(blackButton->String, "Black");
  strcpy(blackButton->FontName, "Assets/fonts/Calibri.ttf");
  blackButton->Color = blackButtonColor;
  blackButton->TextSize = blackButtonSize;  
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, blackButton);

  /* white button */
  int whiteButtonSize = SDL_INT_TEXT_SIZE;
  SDL_Color whiteButtonColor = SDL_COLOR_NORMAL_BUTTON;
  ObjectHandle *whiteButton = ObjectHandle_Initialize(Button, Option_White, 200, SCREEN_HEIGHT/5 + 75, 0, 0);
  strcpy(whiteButton->String, "White");
  strcpy(whiteButton->FontName, "Assets/fonts/Calibri.ttf");
  whiteButton->Color = whiteButtonColor;
  whiteButton->TextSize = whiteButtonSize;  
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, whiteButton);

  /* difficulty label */
  int difficultyLabelSize = SDL_INT_TEXT_SIZE;
  SDL_Color difficultyLabelColor = SDL_COLOR_NORMAL_BUTTON;
  ObjectHandle *difficultyLabel = ObjectHandle_Initialize(Text, Label_Difficulty, 675, SCREEN_HEIGHT/5, 0, 0);
  strcpy(difficultyLabel->String, "Difficulty: ");
  strcpy(difficultyLabel->FontName, "Assets/fonts/Calibri.ttf");
  difficultyLabel->Color = difficultyLabelColor;
  difficultyLabel->TextSize = difficultyLabelSize;  
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, difficultyLabel);

  /* Easy */
  int easyButtonSize = SDL_INT_TEXT_SIZE;
  SDL_Color easyButtonColor = SDL_COLOR_NORMAL_BUTTON;
  ObjectHandle *easyButton = ObjectHandle_Initialize(Button, Option_EasyAI, 900, SCREEN_HEIGHT/5, 0, 0);
  strcpy(easyButton->String, "Easy");
  strcpy(easyButton->FontName, "Assets/fonts/Calibri.ttf");
  easyButton->Color = easyButtonColor;
  easyButton->TextSize = easyButtonSize;  
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, easyButton);

  /* Medium */
  int mediumButtonSize = SDL_INT_TEXT_SIZE;
  SDL_Color mediumButtonColor = SDL_COLOR_NORMAL_BUTTON;
  ObjectHandle *mediumButton = ObjectHandle_Initialize(Button, Option_MediumAI, 900, SCREEN_HEIGHT/5 + 75, 0, 0);
  strcpy(mediumButton->String, "Medium");
  strcpy(mediumButton->FontName, "Assets/fonts/Calibri.ttf");
  mediumButton->Color = mediumButtonColor;
  mediumButton->TextSize = mediumButtonSize;  
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, mediumButton);

  /* Difficult  */
  int difficultButtonSize = SDL_INT_TEXT_SIZE;
  SDL_Color difficultButtonColor = SDL_COLOR_NORMAL_BUTTON;
  ObjectHandle *difficultButton = ObjectHandle_Initialize(Button, Option_DifficultAI, 900, SCREEN_HEIGHT/5 + 150, 0, 0);
  strcpy(difficultButton->String, "Difficult");
  strcpy(difficultButton->FontName, "Assets/fonts/Calibri.ttf");
  difficultButton->Color = difficultButtonColor;
  difficultButton->TextSize = difficultButtonSize;  
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, difficultButton);

  /* Play  */
  int playButtonSize = SDL_INT_TEXT_SIZE;
  SDL_Color playButtonColor = SDL_COLOR_NORMAL_BUTTON;
  ObjectHandle *playButton = ObjectHandle_Initialize(Button, Option_PlayButton, 900, 550, 0, 0);
  strcpy(playButton->String, "Play");
  strcpy(playButton->FontName, "Assets/fonts/Calibri.ttf");
  playButton->Color = playButtonColor;
  playButton->TextSize = playButtonSize;  
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, playButton);
  
  windowRender(MainHandle);
}

void drawChessBoard(ViewHandle * MainHandle){

  SDL_SetRenderDrawColor(MainHandle->CurrentWindow->WindowRenderer, 0, 0, 0, 0);
  SDL_RenderClear(MainHandle->CurrentWindow->WindowRenderer);

  ObjectHandleList_DeepFree(MainHandle->CurrentWindow->ObjectList);

  SDL_Window * window = MainHandle->CurrentWindow->Window;
 /* SDL_Color Gray = {0x6D, 0x6D, 0x6D};
  SDL_Color White = {0xB3, 0xB3, 0xB3};*/

  int rank, file;
  int leftOffset = (SCREEN_WIDTH - BOARD_WIDTH)/2;;
  int topOffset = (SCREEN_HEIGHT - BOARD_HEIGHT)/2;

  for(rank=7; rank>=0; rank--){
    for(file=0; file<8; file++){

      ObjectHandle *Box = ObjectHandle_Initialize(Coordinate, Square, leftOffset + file*75, topOffset + (7-rank)*75, 75, 75);
      if((rank+file)%2 == 0){
	/*Box->Color = Gray;*/
	Box->hexR = 0x6d;
	Box->hexG = 0x6d;
	Box->hexB = 0x6d;
	Box->hexA = 0x6d;
	}else{
	/*Box->Color = White;*/
	Box->hexR = 0xb3;
	Box->hexG = 0xb3;
	Box->hexB = 0xb3;
	Box->hexA = 0xb3;
	}
      Box->Rank = rank;
      Box->File = file;
	ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, Box);
    }
  }

  ObjectHandle *playerBoxLeft = ObjectHandle_Initialize(Color, Box, 30, SCREEN_HEIGHT/2 - 300, 225, 75);
  playerBoxLeft->hexR = 0xA8;
  playerBoxLeft->hexG = 0xC6;
  playerBoxLeft->hexB = 0xDB;
  playerBoxLeft->hexA = 0xDB;
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, playerBoxLeft);

  ObjectHandle *graveyardBoxLeft = ObjectHandle_Initialize(Color, Box, 30, SCREEN_HEIGHT/2 - 225, 225, 150);
  graveyardBoxLeft->hexR = 0x7B;
  graveyardBoxLeft->hexG = 0xAD;
  graveyardBoxLeft->hexB = 0xDB;
  graveyardBoxLeft->hexA = 0xDB;
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, graveyardBoxLeft);

  ObjectHandle *blackPlayer = ObjectHandle_Initialize(Text, Player_Label, 70, 37, 0, 0);
  strcpy(blackPlayer->String, "");
  strcpy(blackPlayer->FontName, "Assets/fonts/Calibri.ttf");
  blackPlayer->Color = SDL_COLOR_BLACK;
  blackPlayer->TextSize = 30;  
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, blackPlayer);

  ObjectHandle *blackTimer = ObjectHandle_Initialize(Text, Timer, 115, 75, 0, 0);
  blackTimer->PlayerColor = Black;
  strcpy(blackTimer->String, "0:00");
  strcpy(blackTimer->FontName, "Assets/fonts/Calibri.ttf");
  blackTimer->Color = SDL_COLOR_BLACK;
  blackTimer->TextSize = 30;  
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, blackTimer);    

  ObjectHandle *quitButton = ObjectHandle_Initialize(Text, Button, 30, SCREEN_HEIGHT - 75, 0, 0);
  strcpy(quitButton->String, "Quit");
  strcpy(quitButton->FontName, "Assets/fonts/Calibri.ttf");
  quitButton->Color = SDL_COLOR_NORMAL_BUTTON;
  quitButton->TextSize = 30;  
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, quitButton);

  ObjectHandle *undoButton = ObjectHandle_Initialize(Text, Button, 950, 40, 0, 0);
  strcpy(undoButton->String, "Undo Move");
  strcpy(undoButton->FontName, "Assets/fonts/Calibri.ttf");
  undoButton->Color = SDL_COLOR_NORMAL_BUTTON;
  undoButton->TextSize = 30;  
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, undoButton);

  ObjectHandle *statusString = ObjectHandle_Initialize(Text, StatusText, 410, 0, 0, 0);
  strcpy(statusString->String, "");
  strcpy(statusString->FontName, "Assets/fonts/Calibri.ttf");
  statusString->Color = SDL_COLOR_RED;
  statusString->TextSize = 30;  
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, statusString);

  ObjectHandle *capturedPawnLeft = ObjectHandle_Initialize(Image, Box, 30, SCREEN_HEIGHT/2 - 225, 75, 75);
  strcpy(capturedPawnLeft->ImageFileName, "Assets/pieces/W_Pawn.png");
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, capturedPawnLeft);

  ObjectHandle *capturedPawnCountWhite = ObjectHandle_Initialize(Text, CaptureCount, 30, SCREEN_HEIGHT/2 - 225, 75, 75);
  capturedPawnCountWhite->TextSize = 30;
  capturedPawnCountWhite->Color = SDL_COLOR_BLACK;
  capturedPawnCountWhite->PieceType = Pawn;
  capturedPawnCountWhite->PlayerColor = White;
  strcpy(capturedPawnCountWhite->String, "0");
  strcpy(capturedPawnCountWhite->FontName, "Assets/fonts/Calibri.ttf");
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, capturedPawnCountWhite);

  ObjectHandle *capturedRookLeft = ObjectHandle_Initialize(Image, Box, 105, SCREEN_HEIGHT/2 - 225, 75, 75);
  strcpy(capturedRookLeft->ImageFileName, "Assets/pieces/W_Rook.png");
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, capturedRookLeft);

  ObjectHandle *capturedRookCountWhite = ObjectHandle_Initialize(Text, CaptureCount, 105, SCREEN_HEIGHT/2 - 225, 75, 75);
  capturedRookCountWhite->TextSize = 30;
  capturedRookCountWhite->Color = SDL_COLOR_BLACK;
  capturedRookCountWhite->PieceType = Rook;
  capturedRookCountWhite->PlayerColor = White;
  strcpy(capturedRookCountWhite->String, "0");
  strcpy(capturedRookCountWhite->FontName, "Assets/fonts/Calibri.ttf");
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, capturedRookCountWhite);

  ObjectHandle *capturedKnightLeft = ObjectHandle_Initialize(Image, Box, 180, SCREEN_HEIGHT/2 - 225, 75, 75);
  strcpy(capturedKnightLeft->ImageFileName, "Assets/pieces/W_Knight.png");
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, capturedKnightLeft);

 ObjectHandle *capturedKnightCountWhite = ObjectHandle_Initialize(Text, CaptureCount, 180, SCREEN_HEIGHT/2 - 225, 75, 75);
  capturedKnightCountWhite->TextSize = 30;
  capturedKnightCountWhite->Color = SDL_COLOR_BLACK;
  capturedKnightCountWhite->PieceType = Knight;
  capturedKnightCountWhite->PlayerColor = White;
  strcpy(capturedKnightCountWhite->String, "0");
  strcpy(capturedKnightCountWhite->FontName, "Assets/fonts/Calibri.ttf");
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, capturedKnightCountWhite);

  ObjectHandle *capturedBishopLeft = ObjectHandle_Initialize(Image, Box, 30, SCREEN_HEIGHT/2 - 150, 75, 75);
  strcpy(capturedBishopLeft->ImageFileName, "Assets/pieces/W_Bishop.png");
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, capturedBishopLeft);

  ObjectHandle *capturedBishopCountWhite = ObjectHandle_Initialize(Text, CaptureCount, 30, SCREEN_HEIGHT/2 - 150, 75, 75);
  capturedBishopCountWhite->TextSize = 30;
  capturedBishopCountWhite->Color = SDL_COLOR_BLACK;
  capturedBishopCountWhite->PieceType = Bishop;
  capturedBishopCountWhite->PlayerColor = White;
  strcpy(capturedBishopCountWhite->String, "0");
  strcpy(capturedBishopCountWhite->FontName, "Assets/fonts/Calibri.ttf");
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, capturedBishopCountWhite);

  ObjectHandle *capturedQueenLeft = ObjectHandle_Initialize(Image, Box, 105, SCREEN_HEIGHT/2 - 150, 75, 75);
  strcpy(capturedQueenLeft->ImageFileName, "Assets/pieces/W_Queen.png");
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, capturedQueenLeft);

  ObjectHandle *capturedQueenCountWhite = ObjectHandle_Initialize(Text, CaptureCount, 105, SCREEN_HEIGHT/2 - 150, 75, 75);
  capturedQueenCountWhite->TextSize = 30;
  capturedQueenCountWhite->Color = SDL_COLOR_BLACK;
  capturedQueenCountWhite->PieceType = Queen;
  capturedQueenCountWhite->PlayerColor = White;
  strcpy(capturedQueenCountWhite->String, "0");
  strcpy(capturedQueenCountWhite->FontName, "Assets/fonts/Calibri.ttf");
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, capturedQueenCountWhite);

  ObjectHandle *playerBoxRight = ObjectHandle_Initialize(Color, Box, 945, 413, 225, 75);
  playerBoxRight->hexR = 0xA8;
  playerBoxRight->hexG = 0xC6;
  playerBoxRight->hexB = 0xDB;
  playerBoxRight->hexA = 0xDB;
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, playerBoxRight);

  ObjectHandle *graveyardBoxRight = ObjectHandle_Initialize(Color, Box, 945, 488, 225, 150);
  graveyardBoxRight->hexR = 0x7B;
  graveyardBoxRight->hexG = 0xAD;
  graveyardBoxRight->hexB = 0xDB;
  graveyardBoxRight->hexA = 0xDB;
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, graveyardBoxRight);

  ObjectHandle *whitePlayer = ObjectHandle_Initialize(Text, Player_Label, 985, 413, 0, 0);
  strcpy(whitePlayer->String, "");
  strcpy(whitePlayer->FontName, "Assets/fonts/Calibri.ttf");
  whitePlayer->Color = SDL_COLOR_BLACK;
  whitePlayer->TextSize = 30;  
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, whitePlayer);

  ObjectHandle *whiteTimer = ObjectHandle_Initialize(Text, Timer, 1030, 451, 0, 0);
  whiteTimer->PlayerColor = White;
  strcpy(whiteTimer->String, "0:00");
  strcpy(whiteTimer->FontName, "Assets/fonts/Calibri.ttf");
  whiteTimer->Color = SDL_COLOR_BLACK;
  whiteTimer->TextSize = 30;  
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, whiteTimer);    

  ObjectHandle *capturedPawnRight = ObjectHandle_Initialize(Image, Box, 945, 488, 75, 75);
  strcpy(capturedPawnRight->ImageFileName, "Assets/pieces/B_Pawn.png");
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, capturedPawnRight);

  ObjectHandle *capturedPawnCountBlack = ObjectHandle_Initialize(Text, CaptureCount, 945, 488, 75, 75);
  capturedPawnCountBlack->TextSize = 30;
  capturedPawnCountBlack->Color = SDL_COLOR_BLACK;
  capturedPawnCountBlack->PieceType = Pawn;
  capturedPawnCountBlack->PlayerColor = Black;
  strcpy(capturedPawnCountBlack->String, "0");
  strcpy(capturedPawnCountBlack->FontName, "Assets/fonts/Calibri.ttf");
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, capturedPawnCountBlack);

  ObjectHandle *capturedRookRight = ObjectHandle_Initialize(Image, Box, 945+75, 488, 75, 75);
  strcpy(capturedRookRight->ImageFileName, "Assets/pieces/B_Rook.png");
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, capturedRookRight);

  ObjectHandle *capturedRookCountBlack = ObjectHandle_Initialize(Text, CaptureCount, 945+75, 488, 75, 75);
  capturedRookCountBlack->TextSize = 30;
  capturedRookCountBlack->Color = SDL_COLOR_BLACK;
  capturedRookCountBlack->PieceType = Rook;
  capturedRookCountBlack->PlayerColor = Black;
  strcpy(capturedRookCountBlack->String, "0");
  strcpy(capturedRookCountBlack->FontName, "Assets/fonts/Calibri.ttf");
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, capturedRookCountBlack);

  ObjectHandle *capturedKnightRight = ObjectHandle_Initialize(Image, Box, 945+150, 488, 75, 75);
  strcpy(capturedKnightRight->ImageFileName, "Assets/pieces/B_Knight.png");
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, capturedKnightRight);

  ObjectHandle *capturedKnightCountBlack = ObjectHandle_Initialize(Text, CaptureCount, 945+150, 488, 75, 75);
  capturedKnightCountBlack->TextSize = 30;
  capturedKnightCountBlack->Color = SDL_COLOR_BLACK;
  capturedKnightCountBlack->PieceType = Knight;
  capturedKnightCountBlack->PlayerColor = Black;
  strcpy(capturedKnightCountBlack->String, "0");
  strcpy(capturedKnightCountBlack->FontName, "Assets/fonts/Calibri.ttf");
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, capturedKnightCountBlack);

  ObjectHandle *capturedBishopRight = ObjectHandle_Initialize(Image, Box, 945, 488+75, 75, 75);
  strcpy(capturedBishopRight->ImageFileName, "Assets/pieces/B_Bishop.png");
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, capturedBishopRight);

  ObjectHandle *capturedBishopCountBlack = ObjectHandle_Initialize(Text, CaptureCount, 945, 488+75, 75, 75);
  capturedBishopCountBlack->TextSize = 30;
  capturedBishopCountBlack->Color = SDL_COLOR_BLACK;
  capturedBishopCountBlack->PieceType = Bishop;
  capturedBishopCountBlack->PlayerColor = Black;
  strcpy(capturedBishopCountBlack->String, "0");
  strcpy(capturedBishopCountBlack->FontName, "Assets/fonts/Calibri.ttf");
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, capturedBishopCountBlack);

  ObjectHandle *capturedQueenRight = ObjectHandle_Initialize(Image, Box, 945+75, 488+75, 75, 75);
  strcpy(capturedQueenRight->ImageFileName, "Assets/pieces/B_Queen.png");
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, capturedQueenRight);

  ObjectHandle *capturedQueenCountBlack = ObjectHandle_Initialize(Text, CaptureCount, 945+75, 488+75, 75, 75);
  capturedQueenCountBlack->TextSize = 30;
  capturedQueenCountBlack->Color = SDL_COLOR_BLACK;
  capturedQueenCountBlack->PieceType = Queen;
  capturedQueenCountBlack->PlayerColor = Black;
  strcpy(capturedQueenCountBlack->String, "0");
  strcpy(capturedQueenCountBlack->FontName, "Assets/fonts/Calibri.ttf");
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, capturedQueenCountBlack);

  windowRender(MainHandle);
}

void drawTransformWindow(ViewHandle * MainHandle, PlayerColorEnum color){

  SDL_SetRenderDrawColor(MainHandle->CurrentWindow->WindowRenderer, 0, 0, 0, 0);
  SDL_RenderClear(MainHandle->CurrentWindow->WindowRenderer);
  ObjectHandleList_DeepFree(MainHandle->CurrentWindow->ObjectList);

  ObjectHandle *transformBox = ObjectHandle_Initialize(Color, Box, 375, 225, 450, 165);
  transformBox->hexR = 0x32;
  transformBox->hexG = 0x00;
  transformBox->hexB = 0xE8;
  transformBox->hexA = 0xE8;
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, transformBox);

  ObjectHandle *NewObject;
  NewObject = ObjectHandle_Initialize(Piece, TransformPiece, 405, 285, 75, 75);
  NewObject->PieceType = Knight;
  NewObject->PlayerColor = color;
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, NewObject);

  NewObject = ObjectHandle_Initialize(Piece, TransformPiece, 510, 285, 75, 75);
  NewObject->PieceType = Bishop;
  NewObject->PlayerColor = color;
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, NewObject);

  NewObject = ObjectHandle_Initialize(Piece, TransformPiece, 615, 285, 75, 75);
  NewObject->PieceType = Knight;
  NewObject->PlayerColor = Rook;
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, NewObject);

  NewObject = ObjectHandle_Initialize(Piece, TransformPiece, 720, 285, 75, 75);
  NewObject->PieceType = Queen;
  NewObject->PlayerColor = color;
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, NewObject);

  windowRender(MainHandle);
}

#else
/* function to display the main menu to the screen */
int drawMainMenu(SDL_Window *window, SDL_Renderer *renderer, int *screenMode){

  SDL_Color greenText = {0x29, 0xEF, 0x48};

  /* rename window title */
  SDL_SetWindowTitle(window, TITLE);

  /* create main menu background image */
  SDL_Texture *backSplash = NULL;
  backSplash = loadTexture("Assets/Menu_Backgrounds/Background_1600_900.jpg", renderer);
  renderTexture(backSplash, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, backSplash);

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

}

#endif

#if 0
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
#endif
