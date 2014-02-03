#include "View.h"

#ifndef GUI_ENABLE

/*define basic colors*/
#define KNRM  "\x1B[37;0m"
#define KGRN  "\x1B[32;0m"
#define KYEL  "\x1B[33;0m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35;0m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37;0m"

#define KGRN_BKG	"\x1B[0;31;42m"

/*define color of player*/
#define WHITE_PLAYER_COLOR 	KBLU
#define BLACK_PLAYER_COLOR 	KCYN
#define HIGHLIGHT_COLOR 	KGRN_BKG

Event * View_AskMoveTransform(ViewHandle * MainViewHandle, ChessPlayer * PlayerAsking){
	Boolean ValidFlag = False;
	int UserChoice;
	Event * ReturnEvent = malloc(sizeof(Event));
	ReturnEvent->Type = AskTransform;
	while (!ValidFlag){
		printf("Please select the type of piece to transform to:\n1. Rook\n2.Knight\n3. Bishop\n4. Queen\nYour choice: ");
		scanf("%d", &UserChoice);
		if (UserChoice < 1 || UserChoice > 4){
			printf("Invalid Choice\n"); 
		} else {
			switch (UserChoice){
				case 1:
					ReturnEvent->PieceType = Rook; 		
				case 2:
					ReturnEvent->PieceType = Knight;
				case 3:
					ReturnEvent->PieceType = Bishop;
				case 4:
					ReturnEvent->PieceType = Queen;
				default:
					ReturnEvent->PieceType = Queen;
			}
		}
	}
	return ReturnEvent;
}

static void PrintChessCoordinate(ChessPiece * CurrPiece){
	unsigned char PieceLetter;
	if (!CurrPiece){		/*No piece is here*/
		 printf("- ");
	} else {
		switch(CurrPiece->Type){
			case Pawn:
				PieceLetter = 'P';
				break;
			case Rook: 
				PieceLetter = 'R';
				break;
			case Knight:
				PieceLetter = 'N';
				break;
			case Bishop:
				PieceLetter = 'B';
				break;
			case Queen:
				PieceLetter = 'Q';
				break;
			case King:
				PieceLetter = 'K';
				break;
			default:
				assert(0);
				break;
		}
	  
		/*if (CurrPiece->Player->PlayerColor == Black) PieceLetter += 'a' - 'A';*/
		
		printf("%c ", PieceLetter);
	}
  
}



/*for settings*/
PlayerControlEnum AskPlayerControl(ChessPlayer * Player){
	unsigned char ValidFlag = 0;
	int ReturnChoice;
	if (Player->PlayerColor == White)
		printf("Please select control for white player:\n");
	else
		printf("Please select control for black player:\n");
	
	while (ValidFlag == 0){    
		printf("1.Human\n2.AI\nYour choice: ");
		scanf("%d", &ReturnChoice);
		if (ReturnChoice < 1 || ReturnChoice > 2) 
			printf("Invalid choice\n");
		else
			ValidFlag = 1;
	}
	
	switch (ReturnChoice){
		case 1:
			return Human;
		case 2:
			return AI;
		default:
			assert(0);
	}	
}

AIDifficultyLevel AskAIDifficultyLevel(void){
	unsigned char ValidFlag = 0;
	int ReturnChoice;
	
	printf("Please select the level of difficulty of AI:\n");
	
	while (ValidFlag == 0){    
		printf("1.Easy\n2.Medium\n3.Difficult\nYour choice: ");
		scanf("%d", &ReturnChoice);
		if (ReturnChoice < 1 || ReturnChoice > 3) 
			printf("Invalid choice\n");
		else
			ValidFlag = 1;
	}
	
	switch (ReturnChoice){
		case 1:
			return Easy;
		case 2:
			return Medium;
		case 3:
			return Difficult;
		default:
			assert(0);
	}	
}

Event * SetOptions(ViewHandle * MainViewHanlde, ChessBoard * MainBoard){
	MainBoard->WhitePlayer->PlayerControl = AskPlayerControl(MainBoard->WhitePlayer);
	if (MainBoard->WhitePlayer->PlayerControl == AI){
		MainBoard->WhitePlayer->AIDifficulty = AskAIDifficultyLevel();
	}
	
	MainBoard->BlackPlayer->PlayerControl = AskPlayerControl(MainBoard->BlackPlayer);
	if (MainBoard->BlackPlayer->PlayerControl == AI){
		MainBoard->BlackPlayer->AIDifficulty = AskAIDifficultyLevel();
	} 
	
	Event * LocalEvent = malloc(sizeof(Event));
	LocalEvent->Type = NoEvent;
	return LocalEvent;
}

/*get event from user*/
Event * View_GetEvent(ViewHandle * MainViewHandle, ChessBoard * CurrBoard, Event * EventHandle){
	char UserInput[10];
	char * OneLetter = UserInput;
	
	unsigned char ReturnRank, ReturnFile;	
	
	Boolean ValidOptionFlag = False;
	while (!ValidOptionFlag){
		/*ask user what to do: 3 options are select a coordinate, undo and exit*/
		printf("enter coordinate or 2 to undo or 3 to exit: ");
		scanf("%s", UserInput);
		
		/*get first non space character*/
		OneLetter = UserInput;
		while ((*OneLetter) == ' ' && (OneLetter - UserInput) < 10) OneLetter++;
		
		if (OneLetter - UserInput == 10){
			printf("Invalid choice\n");
			continue;
		}
		
		if (*OneLetter >= 'a' && *OneLetter <= 'h'){
			ReturnFile = *OneLetter - 'a';
		} else if (*OneLetter >= 'A' && *OneLetter <= 'H'){
			ReturnFile = *OneLetter - 'A';
		} else if (*OneLetter == '2'){
			EventHandle->Type = UndoMove;
			return EventHandle;
		} else if (*OneLetter == '3'){
			EventHandle->Type = Exit;
			return EventHandle;
		} else {
			printf("Invalid choice\n");
			continue;	
		}
	
		OneLetter++;
		if (*OneLetter >= '1' && *OneLetter <= '8'){
			ReturnRank = *OneLetter - '1';
			ValidOptionFlag = True;
		} else {
		 	printf("Invalid Coordinate");
			continue;
		}
		
		
	}
	EventHandle->Type = SelectCoordinate;
	EventHandle->Coordinate = CurrBoard->Board[ReturnRank][ReturnFile];
	return EventHandle;
	
}

void View_DisplayEvent(ViewHandle * MainViewHandle, ChessBoard * CurrBoard, Event * EventHandle){
	if (EventHandle->Type == Checkmate){
		switch (EventHandle->Player->PlayerColor){
			case White:
				printf("White player is check mate. Black Player wins.\n");
				break;
			case Black:
				printf("Black player is check mate. White Player wins.\n");
				break;
		}
	} else if (EventHandle->Type == Stalemate){
		printf("Game is in stalemate. Tie game.\n");
	}
}

void DisplayChessBoard(ViewHandle * MainViewHandle, ChessBoard * CurrChessBoard){
	int i, j;
	for (i = CHESS_BOARD_MAX_ROW - 1; i >= 0 ; i--){
		printf("%d  |  ", i + 1);
		for (j = 0; j < CHESS_BOARD_MAX_COL; j++){
		 	if (CurrChessBoard->Board[i][j]->Piece){
				switch(CurrChessBoard->Board[i][j]->Piece->Player->PlayerColor){
					case White:
						printf(WHITE_PLAYER_COLOR);
						break;
					case Black:
						printf(BLACK_PLAYER_COLOR);
						break;
				}
			}
			PrintChessCoordinate(CurrChessBoard->Board[i][j]->Piece);
			printf(KNRM);
			printf("  ");
		}
		printf("\n");
	}
	printf("   |  ");
	for (j = 0; j < CHESS_BOARD_MAX_COL; j++) printf("%c   ", 'A' + j);
	printf("\n");
}

void HighlightCoordinates(ViewHandle * MainViewHandle, ChessBoard * CurrChessBoard, ChessCoordinateList * CoordList){
	int i, j;
	ChessCoordinateNode * CoordListNode = CoordList->FirstNode;
	Boolean HighlightFlag;
	for (i = CHESS_BOARD_MAX_ROW - 1; i >= 0 ; i--){
		printf("%d  |  ", i + 1);
		for (j = 0; j < CHESS_BOARD_MAX_COL; j++){   
			if (ChessCoordinateList_CheckRedundancy(CoordList, CurrChessBoard->Board[i][j])){
				printf(HIGHLIGHT_COLOR);
			} else {
				if (CurrChessBoard->Board[i][j]->Piece){
				switch(CurrChessBoard->Board[i][j]->Piece->Player->PlayerColor){
					case White:
						printf(WHITE_PLAYER_COLOR);
						break;
					case Black:
						printf(BLACK_PLAYER_COLOR);
						break;
				}
				}
			}
		 	PrintChessCoordinate(CurrChessBoard->Board[i][j]->Piece);
			printf(KNRM);
			printf("  ");
		}
		printf("\n");
	}
	printf("   |  ");
	for (j = 0; j < CHESS_BOARD_MAX_COL; j++) printf("%c   ", 'A' + j);
	printf("\n");
}

/*initialize*/
ViewHandle * View_Initialize(void){
	ViewHandle * ReturnHandle = malloc(sizeof(ViewHandle));
	ReturnHandle->CurrentPlayer = NULL;
	ReturnHandle->ViewHandleEvent = malloc(sizeof(ViewHandle));
	assert(ReturnHandle->ViewHandleEvent);
	return ReturnHandle;
}

/*clean up*/
ViewHandle * View_CleanUp(ViewHandle * handle){
	free(handle);
	return NULL;
}

void View_ConcludeGame(ViewHandle * MainViewHandle, ChessPlayer * player){
	printf("Game concluded\n");
	printf("Goodbye. See you next time\n");
}
#else
/**********************************************************
 * Start defining GUI releated functions
 * ********************************************************/

/*initialize*/
ViewHandle * View_Initialize(void){
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
	
	ViewHandle * ReturnViewHandle = malloc(sizeof(ViewHandle));
	ReturnViewHandle->CurrentWindow = malloc(sizeof(WindowHandle));
	ReturnViewHandle->CurrentWindow->Window = window;
	ReturnViewHandle->CurrentWindow->WindowRenderer = renderer;
	ReturnViewHandle->CurrentWindow->ObjectList = ObjectHandleList_Initialize();
	
	ReturnViewHandle->ViewHandleEvent = malloc(sizeof(Event));
	assert(ReturnViewHandle->ViewHandleEvent);
	ReturnViewHandle->ViewHandleEvent->Type = NoEvent;
	
	return ReturnViewHandle;
}

/*clean up*/
ViewHandle * View_CleanUp(ViewHandle *MainHandle){	
	SDL_DestroyRenderer(MainHandle->CurrentWindow->WindowRenderer);
	SDL_DestroyWindow(MainHandle->CurrentWindow->Window);
	
	ObjectHandleList_ShallowFree(MainHandle->CurrentWindow->ObjectList);
	free(MainHandle->CurrentWindow);
	free(MainHandle->ViewHandleEvent);
	free(MainHandle);
	return NULL;
	
}

/*for settings*/
Event * SetOptions(ViewHandle *MainHandle, ChessBoard * MainBoard){
	int screenMode;

	drawMainMenu(MainHandle);
	Event LocalEvent = GetSDLEvent(MainHandle);	
	
	ObjectHandle * Object;
	PlayerColorEnum PlayerColorSelected;
	AIDifficultyLevel AISelected;
	assert(LocalEvent.Type == ButtonClicked || LocalEvent.Type == Exit);
	if (LocalEvent.Type == ButtonClicked){
		switch(LocalEvent.Object->Tag){
			case Option_OnePlayer:				ObjectHandleList_DeepFree(MainHandle->CurrentWindow->ObjectList);
				drawOnePlayerMenu(MainHandle);
				Boolean AISelectedFlag = False, PlayerSelectedFlag = False, OptionsDoneFlag = False;
				while (!AISelectedFlag || !PlayerSelectedFlag || !OptionsDoneFlag){			
					LocalEvent = GetSDLEvent(MainHandle);
					
					assert(LocalEvent.Type == ButtonClicked);
					switch(LocalEvent.Object->Tag){
						case Option_Black:
							Object = GetObjectByTag(MainHandle, Option_Black);
							Object->Color = SDL_COLOR_SELETED_BUTTON;
							Object = GetObjectByTag(MainHandle, Option_White);
							Object->Color = SDL_COLOR_NORMAL_BUTTON;		/*default color*/
							PlayerSelectedFlag = True;
							PlayerColorSelected = Black;
							break;
						case Option_White:
							Object = GetObjectByTag(MainHandle, Option_White);
							Object->Color = SDL_COLOR_SELETED_BUTTON;		/*selected color*/
							Object = GetObjectByTag(MainHandle, Option_Black);
							Object->Color = SDL_COLOR_NORMAL_BUTTON;		/*default color*/
							PlayerSelectedFlag = True;
							PlayerColorSelected = White;
							break;
						case Option_EasyAI:
							Object = GetObjectByTag(MainHandle, Option_EasyAI);
							Object->Color = SDL_COLOR_SELETED_BUTTON;		/*selected color*/
							Object = GetObjectByTag(MainHandle, Option_MediumAI);
							Object->Color = SDL_COLOR_NORMAL_BUTTON;		/*default color*/
							Object = GetObjectByTag(MainHandle, Option_DifficultAI);
							Object->Color = SDL_COLOR_NORMAL_BUTTON;		/*default color*/
							AISelectedFlag = True;
							AISelected = Easy;
							break;
						case Option_MediumAI:	
							Object = GetObjectByTag(MainHandle, Option_MediumAI);
							Object->Color = SDL_COLOR_SELETED_BUTTON;		/*selected color*/
							Object = GetObjectByTag(MainHandle, Option_EasyAI);
							Object->Color = SDL_COLOR_NORMAL_BUTTON;		/*default color*/
							Object = GetObjectByTag(MainHandle, Option_DifficultAI);
							Object->Color = SDL_COLOR_NORMAL_BUTTON;		/*default color*/
							AISelectedFlag = True;
							AISelected = Medium;
							break;
						case Option_DifficultAI:
							Object = GetObjectByTag(MainHandle, Option_DifficultAI);
							Object->Color = SDL_COLOR_SELETED_BUTTON;		/*selected color*/
							Object = GetObjectByTag(MainHandle,Option_MediumAI);
							Object->Color = SDL_COLOR_NORMAL_BUTTON;		/*default color*/
							Object = GetObjectByTag(MainHandle, Option_EasyAI);
							Object->Color = SDL_COLOR_NORMAL_BUTTON;		/*default color*/
							AISelectedFlag = True;
							AISelected = Difficult;
							break;
						case Option_PlayButton:
							if (AISelectedFlag && PlayerSelectedFlag)
							OptionsDoneFlag = True;
							break;
							
					}
				
					if (AISelectedFlag && PlayerSelectedFlag){
						Object = GetObjectByTag(MainHandle, Option_PlayButton);
						Object->Color = SDL_COLOR_NORMAL_BUTTON;		/*selected color*/
					}
					
					if (!OptionsDoneFlag) windowRender(MainHandle);
				}
				
				/*process input from user*/
				if (PlayerColorSelected == White){
					MainBoard->WhitePlayer->PlayerControl = Human;
					MainBoard->BlackPlayer->PlayerControl = AI;
					MainBoard->BlackPlayer->AIDifficulty = AISelected;
				} else {
					MainBoard->BlackPlayer->PlayerControl = Human;
					MainBoard->WhitePlayer->PlayerControl = AI;
					MainBoard->WhitePlayer->AIDifficulty = AISelected;
				}
				
				break;
				
			case Option_TwoPlayer:				
				MainBoard->WhitePlayer->PlayerControl = Human;
				MainBoard->BlackPlayer->PlayerControl = Human;
				break;
			case Option_AIvsAI:				
				MainBoard->WhitePlayer->PlayerControl = AI;
				MainBoard->WhitePlayer->AIDifficulty = Difficult;			
				MainBoard->BlackPlayer->PlayerControl = AI;
				MainBoard->BlackPlayer->AIDifficulty = Difficult;
				break;
		}
	}
	
	Event * ReturnEvent = malloc(sizeof(Event));
	*ReturnEvent = LocalEvent;
	return ReturnEvent;
}

void PopulateGUIChessBoard(ViewHandle * MainViewHandle, ChessBoard * MainBoard){
	int XMargin = 4, YMargin = 5;
	
	drawChessBoard(MainViewHandle);
	ObjectHandleList_KillAllPieces(MainViewHandle);
	
	/*set player label*/
	ObjectHandleList * PlayerLabelObjects = GetObjectListByTag(MainViewHandle->CurrentWindow->ObjectList, Player_Label);
	ObjectHandleNode * node = PlayerLabelObjects->FirstNode;
	while (node){
		if (node->Object->PlayerColor == White){
			switch (MainBoard->WhitePlayer->PlayerControl){
				case Human:
					strcpy(node->Object->String, "Player 1");
					break;
				case AI:
					strcpy(node->Object->String, "Computer");
					break;
			}			
		} else {
			switch (MainBoard->BlackPlayer->PlayerControl){
				case Human:
					strcpy(node->Object->String, "Player 2");
					break;
				case AI:
					strcpy(node->Object->String, "Computer");
					break;
			}
		}
		node = node->NextNode;
	}
	
	int rank, file;
	ObjectHandle * NewObject, * CoordObject;
	/*update pieces*/
	for (rank = 0; rank < 8; rank ++){
		for (file = 0; file < 8; file++){
			if (MainBoard->Board[rank][file]->Piece){
				CoordObject = GetGUICoordinate(MainViewHandle, rank, file);
				NewObject = ObjectHandle_Initialize(Piece, PieceObject, CoordObject->X + XMargin,CoordObject->Y + YMargin, CoordObject->Width - 2 * XMargin, CoordObject->Height - 2 * YMargin);
				NewObject->PieceType = MainBoard->Board[rank][file]->Piece->Type;
				NewObject->PlayerColor = MainBoard->Board[rank][file]->Piece->Player->PlayerColor;
				ObjectHandleList_AppendObject(MainViewHandle->CurrentWindow->ObjectList, NewObject);
			}
			
		}		
	}
	
	/*capture count*/
	ObjectHandleList * AllCaptureCount = GetObjectListByTag(MainViewHandle->CurrentWindow->ObjectList, CaptureCount);
	
	ObjectHandleNode * Node = AllCaptureCount->FirstNode;
	while (Node){
		sprintf(Node->Object->String, "%d", ChessBoard_CountCapturePiece(MainBoard, Node->Object->PlayerColor, Node->Object->PieceType)); 
		Node = Node->NextNode;
	}
	
	ObjectHandleList_ShallowFree(AllCaptureCount);
	
	/*event such as in check and stalemate*/
	ObjectHandle * StatusTextObj = GetObjectByTag(MainViewHandle, StatusText);
	assert(StatusTextObj);
	switch (MainViewHandle->ViewHandleEvent->Type){
		case Checkmate:
			switch (MainViewHandle->ViewHandleEvent->Player->PlayerColor){
				case White:
					strcpy(StatusTextObj->String, "White player is checked mated");
					break;
				case Black:
					strcpy(StatusTextObj->String, "Black player is checked mated");
					break;
			}
			break;
		case Stalemate:			
			strcpy(StatusTextObj->String, "Two player are in stalemate. Tie game.");			
			break;
		case InCheck:
			switch (MainViewHandle->ViewHandleEvent->Player->PlayerColor){
				case White:
					strcpy(StatusTextObj->String, "White player is in check");
					break;
				case Black:
					strcpy(StatusTextObj->String, "Black player is in check");
					break;
			}
			break;
			
	}
	
}
/*for displaying*/
void DisplayChessBoard(ViewHandle * MainViewHandle, ChessBoard * MainBoard)
{	
	
	PopulateGUIChessBoard(MainViewHandle, MainBoard);
	windowRender(MainViewHandle);
	
}

void HighlightCoordinates(ViewHandle * MainViewHandle, 
ChessBoard * MainBoard, ChessCoordinateList * CoordList){
	
	PopulateGUIChessBoard(MainViewHandle, MainBoard);
	int rank, file;
	ObjectHandle * CoordObject;
	for (rank = 0; rank < 8; rank ++){
		for (file = 0; file < 8; file++){
			CoordObject = GetGUICoordinate(MainViewHandle, rank, file);
			/*highlight the board if necessary*/
			if (ChessCoordinateList_CheckRedundancy(CoordList, MainBoard->Board[rank][file])){
				if ((rank + file) % 2){
					CoordObject->hexR = 0x30;
					CoordObject->hexG = 0xFF;
					CoordObject->hexB = 0x20;
					CoordObject->hexA = 0x20;
				} else {
					CoordObject->hexR = 0x14;
					CoordObject->hexG = 0x9c;
					CoordObject->hexB = 0x03;
					CoordObject->hexA = 0x03;
				}
			}
		}		
	}
	
	windowRender(MainViewHandle);
	
}

/*get event from user*/
Event * View_GetEvent(ViewHandle * MainViewHandle, ChessBoard * CurrBoard, Event * LocalEvent){	
	*LocalEvent = GetSDLEvent(MainViewHandle);	
	switch (LocalEvent->Type){
		case ButtonClicked:
			switch (LocalEvent->Object->Tag){
				case Option_Undo:
					LocalEvent->Type = UndoMove;
					break;
				case Option_Quit:
					LocalEvent->Type = Exit;
					break;
			}
			break;
		case SelectCoordinate:
			LocalEvent->Type = SelectCoordinate;
			ObjectHandle * CoordObject = LocalEvent->Object;
			LocalEvent->Coordinate = CurrBoard->Board[CoordObject->Rank][CoordObject->File];
			break;
	}
	return LocalEvent;
}

/*DisplayEvent*/
void View_DisplayEvent(ViewHandle * MainViewHandle, ChessBoard * CurrBoard, Event * Event_in){
		
}

void View_ConcludeGame(ViewHandle * MainViewHandle, ChessPlayer * PlayerCheckmated){	
	sleep(3);
}

/*for transformation: ask user which type to transform to*/
Event * View_AskMoveTransform(ViewHandle * MainViewHandle, ChessPlayer * PlayerAsking){
	drawTransformWindow(MainViewHandle, PlayerAsking->PlayerColor);
	
	Event * LocalEvent = malloc(sizeof(Event));
	* LocalEvent = GetSDLEvent(MainViewHandle);	
	switch (LocalEvent->Type){
		case PieceClicked:
			LocalEvent->Type = AskTransform;
			/*LocalEvent->PieceType = LocalEvent->Object->PieceType;			*/
			break;		
	}
	return LocalEvent;
}

#endif
