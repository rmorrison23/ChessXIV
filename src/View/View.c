#include "View.h"

#ifndef GUI_ENABLE

/*define basic colors*/
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define KGRN_BKG	"\x1B[0;31;42m"

/*define color of player*/
#define WHITE_PLAYER_COLOR 	KBLU
#define BLACK_PLAYER_COLOR 	KCYN
#define HIGHLIGHT_COLOR 	KGRN_BKG

ChessPieceTypeEnum View_AskMoveTransform(void){
	Boolean ValidFlag = False;
	int UserChoice;
	while (!ValidFlag){
		printf("Please select the type of piece to transform to:\n1. Rook\n2.Knight\n3. Bishop\n4. Queen\nYour choice: ");
		scanf("%d", &UserChoice);
		if (UserChoice < 1 || UserChoice > 4){
			printf("Invalid Choice\n"); 
		} else {
			switch (UserChoice){
				case 1:
			 		return Rook;
				case 2:
					return Knight;
				case 3:
					return Bishop;
				case 4:
					return Queen;
				default:
					return Queen;
			}
		}
	}
	return Queen;
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

ChessBoard * SetOptions(ChessBoard * MainBoard){
	AskPlayerControl(MainBoard->WhitePlayer);
	if (MainBoard->WhitePlayer->PlayerControl == AI){
		MainBoard->WhitePlayer->AIDifficulty = AskAIDifficultyLevel();
	}
	
	AskPlayerControl(MainBoard->BlackPlayer);
	if (MainBoard->BlackPlayer->PlayerControl == AI){
		MainBoard->BlackPlayer->AIDifficulty = AskAIDifficultyLevel();
	} 
	
	return MainBoard;
}


/*for displaying*/
ChessCoordinate * View_GetOneCoordinate(ChessBoard * MainBoard){
	Event MyEvent;
	View_GetEvent(MainBoard, &MyEvent);
	return MyEvent.Coordinate;
}

/*get event from user*/
Event * View_GetEvent(ChessBoard * CurrBoard, Event * EventHandle){
	char UserInput[10];
	char * OneLetter = UserInput;
	
	unsigned char ReturnRank, ReturnFile;
	
	
	
	Boolean ValidOptionFlag = False;
	while (!ValidOptionFlag){
		/*ask user what to do: 3 options are select a coordinate, undo and exit*/
		printf("enter coordinate or 2 to undo or 3 to exit: ");
		scanf("%s", UserInput);
		
		/*get first non space character*/
		while ((*OneLetter) == ' ') OneLetter++;
		
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

void View_DisplayEvent(ChessBoard * CurrBoard, Event * EventHandle){
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

void DisplayChessBoard(ChessBoard * CurrChessBoard){
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

void HighlightCoordinates(ChessBoard * CurrChessBoard, ChessCoordinateList * CoordList){
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
void View_Initialize(void){
	printf("Welcome to chess game in command line\n");
}

/*clean up*/
void View_CleanUp(void){
	
}

void View_ConcludeGame(ChessBoard * MainBoard){
	printf("Game concluded\n");
	printf("Goodbye. See you next time\n");
}
#else
/*RYAN PUT YOUR CODE HERE. TO COMPILE USE make GUI_ENABLE=y*/
/*for settings*/
PlayerControlEnum AskPlayerControl(ChessPlayer *);
AIDifficultyLevel AskAIDifficultyLevel(void);

/*for displaying*/
void DisplayChessBoard(ChessBoard *);
void HighlightCoordinates(ChessCoordinateList *);

/*get event from user*/
Event * View_GetEvent(void);

/*initialize*/
void View_Initialize(void);

/*clean up*/
void View_CleanUp(void);

#endif