#include "Control.h"

static ChessBoard * MainChessBoard;
static ChessMoveList * MainMoveList;

void Control_Initialize(void){
	/*initialize the board*/
	MainChessBoard = Model_Initialize();
	MainMoveList = NULL;
	
	/*initialize the view*/
	View_Initialize();
}


void Control_MainLoop(void){
	/*local variables*/
	Boolean GameOnFlag = True, LegalMoveFlag = False;
	ChessPlayer * CurrentPlayer;
	ChessCoordinate * Coordinate1, * Coordinate2;
	Coordinate1 = NULL; Coordinate2 = NULL;
	ChessCoordinateList * LegalChessCoordList, * LegalChessCoordListNode;
	ChessMove LocalChessMove;
	Event LocalEvent;
	
	/*ask user settings*/
	/*player control*/
	MainChessBoard->WhitePlayer->PlayerControl = AskPlayerControl(MainChessBoard->WhitePlayer);
	if (MainChessBoard->WhitePlayer->PlayerControl == AI)
		MainChessBoard->WhitePlayer->AIDifficulty = AskAIDifficultyLevel();
	
	MainChessBoard->BlackPlayer->PlayerControl = AskPlayerControl(MainChessBoard->BlackPlayer);
	if (MainChessBoard->BlackPlayer->PlayerControl == AI)
		MainChessBoard->BlackPlayer->AIDifficulty = AskAIDifficultyLevel();
	
#if 1
	
	ChessCoordinateList TestList[3];
	TestList[0].Coordinate = MainChessBoard->Board[0][2];
	TestList[1].Coordinate = MainChessBoard->Board[1][2];
	TestList[2].Coordinate = MainChessBoard->Board[2][2];
	TestList[0].NextNode = &TestList[1];
	TestList[1].NextNode = &TestList[2];
	TestList[2].NextNode = NULL;
	
	/*set this part to if 0 if you want to run normally*/
	printf("displaying the board\n");
	DisplayChessBoard(MainChessBoard);
	View_GetEvent(MainChessBoard, &LocalEvent);
	switch(LocalEvent.EventType){
		case SelectCoordinate:
			printf("Rank = %d, File = %d\n", LocalEvent.Coordinate->Rank, LocalEvent.Coordinate->File);
			break;
	}
	
	HighlightCoordinates(MainChessBoard, TestList);
#endif
	
	
#if 0
	/*main loop*/
	CurrentPlayer = MainChessBoard->WhitePlayer;
	while (GameOnFlag){
		if (CurrentPlayer->PlayerControlType == Human){
#if GUI_ENABLE
		
			
#else
			/*NEED TO TAKE CARE OF SITUATION OF NO POSSIBLE LEGAL MOVES FOR A PIECE*/
			/*let current user select 1 coordinate*/
			while (Coordinate1 == NULL){			
				Coordinate1 = View_GetOneCoordinate();
				if (Coordinate1->Piece == NULL){
					/*select an empty coordinate*/
					Coordinate1 = NULL;
				} else if (Coordinate1->Piece->Player->PlayerColor != CurrentPlayer->PlayerColor){
					/*select an piece of opponent*/
					Coordinate1 = NULL;
				}
			}
			
			while (!Coordinate2){
				/*highlight the legal moves*/
				LegalChessCoordList = Model_GetLegalCoordinate(MainChessBoard, Coordinate1->Piece);
				HighlightCoordinates(LegalChessCoordList);
				/*let user select the next coordinate*/
				Coordinate2 = View_GetOneCoordinate();
				if (Coordinate2->Piece){
					if (Coordinate2->Piece->Player->PlayerColor == CurrentPlayer->PlayerColor){
						/*select own piece, reset the coordinate 1 and set null to coordinate2*/
						Coordinate1 = Coordinate2;
						Coordinate2 = NULL;
					}
				} else {
					/*check if this coordinate is in the legal coordinate list we got*/
					LegalChessCoordListNode = LegalChessCoordList;
					LegalMoveFlag = False;
					while (LegalChessCoordListNode && !LegalMoveFlag){
						if (LegalChessCoordListNode->Coordinate == Coordinate2){
							LegalMoveFlag = True;
						} else {
							LegalChessCoordListNode = LegalChessCoordListNode->NextNode;
						}
					}
					
					if (!LegalMoveFlag){
						/*reselect coordinate2*/
						Coordinate2 = NULL;
					}
				}
			}
			
			/*construct chess move then perform it*/
			LocalChessMove = malloc(sizeof(ChessMove));
			assert(LocalChessMove);
			LocalChessMove->Piece = Coordinate1->Piece;
			LocalChessMove->Start = Coordinate1;
			LocalChessMove->End = Coordinate2;
			MainChessBoard = Model_PerformMove(MainChessBoard, MainMoveList, LocalChessMove);
			
		} else {
			Model_GetBestMove
		}
#endif
		/*check for checkmate*/
		if (Model_CheckCheckmate(MainChessBoard, CurrentPlayer)){
			GameOnFlag = False;
		} else {
			/*switch player*/
			if (CurrentPlayer->PlayerColor == White)
				CurrentPlayer = MainChessBoard->BlackPlayer;
			else
				CurrentPlayer = MainChessBoard->WhitePlayer;
		}
	}
	
	/*conclude the game*/
	View_ConcludeGame(MainChessBoard, CurrentPlayer);
#endif
}

void Control_CleanUp(void){
	Model_CleanUp(MainChessBoard, MainMoveList);
	View_CleanUp();
}
