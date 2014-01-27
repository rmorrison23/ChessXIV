#include "Control.h"


/*In main loop, make sure that player don't undo in first move*/

static ChessBoard * MainChessBoard;
static ChessMoveList * MainMoveList;

void Control_Initialize(void){
	/*initialize the board*/
	MainChessBoard = Model_Initialize();
	MainMoveList = malloc(sizeof(ChessMoveList));
	
	/*initialize the view*/
	View_Initialize();
}


void Control_MainLoop(void){
	/*local variables*/
	Boolean GameOnFlag = True, LegalMoveFlag = False;
	ChessPlayer * CurrentPlayer;
	ChessCoordinate * Coordinate1, * Coordinate2;
	Coordinate1 = NULL; Coordinate2 = NULL;
	ChessCoordinateList * LegalChessCoordList; ChessCoordinateNode * LegalChessCoordListNode;
	ChessMove * LocalChessMove;
/*Event LocalEvent;*/
	
	/*ask user settings*/
	/*player control*/
	MainChessBoard = SetOptions(MainChessBoard);
	
#if 0
	
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
	
	
#if 1
	/*main loop*/
	CurrentPlayer = MainChessBoard->WhitePlayer;
	while (GameOnFlag){
		if (CurrentPlayer->PlayerControl == Human){
			Coordinate1 = NULL;
			Coordinate2 = NULL;
#if GUI_ENABLE
		
			
#else
			/*NEED TO TAKE CARE OF SITUATION OF NO POSSIBLE LEGAL MOVES FOR A PIECE*/
			/*let current user select 1 coordinate*/
			DisplayChessBoard(MainChessBoard);
			while (Coordinate1 == NULL){			
				Coordinate1 = View_GetOneCoordinate(MainChessBoard);
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
				LegalChessCoordList = Model_GetLegalCoordinates(MainChessBoard, Coordinate1->Piece, CurrentPlayer);
				
#if 0
				printf("got here\n");
				ChessCoordinateNode * MyNode = LegalChessCoordList->FirstNode;
				printf("printing legal\n");
				while (MyNode){
						printf("%d %d\n", MyNode->Coordinate->Rank, MyNode->Coordinate->File);
						MyNode = MyNode->NextNode;
				}
				
#endif
				
				
				HighlightCoordinates(MainChessBoard, LegalChessCoordList);
				/*let user select the next coordinate*/
				Coordinate2 = View_GetOneCoordinate(MainChessBoard);
				if (Coordinate2->Piece){
					if (Coordinate2->Piece->Player == CurrentPlayer){
						/*select own piece, reset the coordinate 1 and set null to coordinate2*/
						Coordinate1 = Coordinate2;
						Coordinate2 = NULL;
					}
				} else {
					/*check if this coordinate is in the legal coordinate list we got*/
					LegalChessCoordListNode = LegalChessCoordList->FirstNode;
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
			DisplayChessBoard(MainChessBoard);
			/*construct chess move then perform it*/
			LocalChessMove = malloc(sizeof(ChessMove));
			assert(LocalChessMove);
			LocalChessMove->MovePiece = Coordinate1->Piece;
			LocalChessMove->StartPosition = Coordinate1;
			LocalChessMove->NextPosition = Coordinate2;
			MainChessBoard = Model_PerformMove(MainChessBoard, MainMoveList, LocalChessMove);
			
		} else {
			/*Model_GetBestMove*/
		}
#endif
		/*check for checkmate*/
		CurrentPlayer = CurrentPlayer->OtherPlayer;
		/*if (Model_CheckCheckmate(MainChessBoard, CurrentPlayer)){
			GameOnFlag = False;
		} */
	}
	
	/*conclude the game*/
	View_ConcludeGame(MainChessBoard, CurrentPlayer);
#endif
}

void Control_CleanUp(void){
	Model_CleanUp(MainChessBoard, MainMoveList);
	View_CleanUp();
}
