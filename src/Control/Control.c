#include "Control.h"


/*In main loop, make sure that player don't undo in first move*/
static Boolean CheckSelectValidCoordinate(ChessCoordinate *, ChessPlayer *);

ControlHandle * Control_Initialize(void){
	/*Initialize handle*/
	ControlHandle * ReturnHandle = malloc(sizeof(ControlHandle));
 
	/*initialize the board*/
	ReturnHandle->MainChessBoard = Model_Initialize();
	
	ReturnHandle->MainChessBoard = SetOptions(ReturnHandle->MainChessBoard);
	
	/*intialize move list*/
	ReturnHandle->MainMoveList = ChessMoveList_Initialize();
	
	/*initialize the view*/
	View_Initialize();
	
	return ReturnHandle;
}


ControlHandle * Control_MainLoop(ControlHandle * Handle){
	ChessBoard * MainChessBoard = Handle->MainChessBoard;
	ChessMoveList * MainMoveList = Handle->MainMoveList;
	
	/*local variables*/
	Boolean GameOnFlag = True, LegalMoveFlag = False;
	ChessPlayer * CurrentPlayer;
	ChessCoordinate * Coordinate1, * Coordinate2;
	Coordinate1 = NULL; Coordinate2 = NULL;
	ChessCoordinateList * LegalChessCoordList; ChessCoordinateNode * LegalChessCoordListNode;
	ChessMove * LocalChessMove;
	Event * LocalEvent = malloc(sizeof(Event));
	Boolean ExitStateFlag = False;

	/*main loop*/
	CurrentPlayer = MainChessBoard->WhitePlayer;
	while (GameOnFlag){
		if (CurrentPlayer->PlayerControl == Human){
			Coordinate1 = NULL;
			Coordinate2 = NULL;

			/*NEED TO TAKE CARE OF SITUATION OF NO POSSIBLE LEGAL MOVES FOR A PIECE*/
			/*let current user select 1 coordinate*/
			DisplayChessBoard(MainChessBoard);
			
			/*state 1: No coordinates selected*/
			ExitStateFlag = False;
			while (!ExitStateFlag){
				LocalEvent = View_GetEvent(MainChessBoard, LocalEvent);
				switch (LocalEvent->Type){
					case SelectCoordinate:
						Coordinate1 = LocalEvent->Coordinate;
						if (CheckSelectValidCoordinate(Coordinate1, CurrentPlayer))	ExitStateFlag = True; 
						break;
					case UndoMove:
						UndoMoveFlag = True;
						ExitStateFlag = True;
						break;
					case Exit:
						GameOnFlag = False;
						ExitStateFlag = True;
						break;
					default:  
						assert(False);
						break;
						
				}
			}
			
			if (UndoMoveFlag){
				
				continue;
			}
			
			GameOnFlag = False;
			
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
			LocalChessMove = Model_GetBestMove(MainChessBoard, CurrentPlayer);
		}
		/*change player*/
		CurrentPlayer = CurrentPlayer->OtherPlayer;
		
		/*delete the current legal coord list*/
		ChessCoordinateList_Free(LegalChessCoordList);
		
		/*check for checkmate*/
		/*if (Model_CheckCheckmate(MainChessBoard, CurrentPlayer)){
			GameOnFlag = False;
		} */
	}
	
	/*conclude the game*/
	View_ConcludeGame(MainChessBoard, CurrentPlayer);
	free(LocalEvent);
	
	return Handle;
}

ControlHandle * Control_CleanUp(ControlHandle * Handle){
	Model_CleanUp(Handle->MainChessBoard, Handle->MainMoveList);
	View_CleanUp();
	free(Handle);
	return NULL;
}

static Boolean CheckSelectValidCoordinate(ChessCoordinate * Coord, ChessPlayer * PlayerToChoose){
	if (!Coord->Piece) return False;
	if (Coord->Piece->Player != PlayerToChoose) return False;
	else return True;
}
