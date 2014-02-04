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

/* QUAN_VERSION: function to display the main menu to the screen */
void drawMainMenu(ViewHandle * MainHandle){


	SDL_Window * window = MainHandle->CurrentWindow->Window;
	SDL_Renderer * renderer = MainHandle->CurrentWindow->WindowRenderer;
	
	SDL_Color greenText = {0x29, 0xEF, 0x48};

	/* rename window title */
	SDL_SetWindowTitle(window, "C h e s s  X I V");
	/* create main menu background image */
	ObjectHandle * backSplashObject = ObjectHandle_Initialize(Image, Background, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	printf("%d  %d\n", backSplashObject->Width, backSplashObject->Height);
	strcpy(backSplashObject->ImageFileName, "Assets/Menu_Backgrounds/Background_800_450.png");

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
		
 
}

void drawOnePlayerMenu(ViewHandle * MainHandle){

  ObjectHandleList_DeepFree(MainHandle->CurrentWindow->ObjectList);

  SDL_Window * window = MainHandle->CurrentWindow->Window;

  /* rename window title */
  SDL_SetWindowTitle(window, "One Player Options");

  /* create one player background image */
  ObjectHandle * backSplashObject = ObjectHandle_Initialize(Image, Background, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  printf("%d  %d\n", backSplashObject->Width, backSplashObject->Height);
  strcpy(backSplashObject->ImageFileName, "Assets/Menu_Backgrounds/Background_800_450.png");  
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

  SDL_SetWindowTitle(MainHandle->CurrentWindow->Window, "C h e s s  X I V");
	
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

  ObjectHandle *coordinateLabel;
  for(rank=0; rank<8; rank++){
    
    coordinateLabel = ObjectHandle_Initialize(Text, CoordLabel, 300 + (rank + 0.4)*75, 640, 0, 0);
    sprintf(coordinateLabel->String, "%c", 'A'+ rank);
    strcpy(coordinateLabel->FontName, "Assets/fonts/Calibri.ttf");
    coordinateLabel->Color = SDL_COLOR_NORMAL_BUTTON;
    coordinateLabel->TextSize = 22;
    ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, coordinateLabel);
  }

  for(file=1; file<=8; file++){
    
    coordinateLabel = ObjectHandle_Initialize(Text, CoordLabel, 280, 675-(file*75)-20, 0, 0);
    sprintf(coordinateLabel->String, "%d", 0 + file);
    strcpy(coordinateLabel->FontName, "Assets/fonts/Calibri.ttf");
    coordinateLabel->Color = SDL_COLOR_NORMAL_BUTTON;
    coordinateLabel->TextSize = 22;
    ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, coordinateLabel);
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
  blackPlayer->PlayerColor=Black;
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, blackPlayer);

  ObjectHandle *blackTimer = ObjectHandle_Initialize(Text, Timer, 115, 75, 0, 0);
  blackTimer->PlayerColor = Black;
  strcpy(blackTimer->String, "0:00");
  strcpy(blackTimer->FontName, "Assets/fonts/Calibri.ttf");
  blackTimer->Color = SDL_COLOR_BLACK;
  blackTimer->TextSize = 30;  
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, blackTimer);    

  ObjectHandle *quitButton = ObjectHandle_Initialize(Button, Option_Quit, 30, SCREEN_HEIGHT - 75, 0, 0);
  strcpy(quitButton->String, "Quit");
  strcpy(quitButton->FontName, "Assets/fonts/Calibri.ttf");
  quitButton->Color = SDL_COLOR_NORMAL_BUTTON;
  quitButton->TextSize = 30;  
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, quitButton);

  ObjectHandle *undoButton = ObjectHandle_Initialize(Button, Option_Undo, 950, 40, 0, 0);
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
  whitePlayer->PlayerColor = White;
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
  NewObject->PieceType = Rook;
  NewObject->PlayerColor = color;
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, NewObject);

  NewObject = ObjectHandle_Initialize(Piece, TransformPiece, 720, 285, 75, 75);
  NewObject->PieceType = Queen;
  NewObject->PlayerColor = color;
  ObjectHandleList_AppendObject(MainHandle->CurrentWindow->ObjectList, NewObject);

  windowRender(MainHandle);
}

