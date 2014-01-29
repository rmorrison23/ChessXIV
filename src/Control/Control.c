#include "Control.h"


/*In main loop, make sure that player don't undo in first move*/
static Boolean CheckSelectOwnPiece(ChessCoordinate *, ChessPlayer *);
static Boolean CheckCoordinatesSamePlayer(ChessCoordinate *, ChessCoordinate *);

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
	Boolean GameOnFlag = True;
	ChessPlayer * CurrentPlayer;
	ChessCoordinate * Coordinate1, * Coordinate2;
	Coordinate1 = NULL; Coordinate2 = NULL;
	ChessCoordinateList * LegalChessCoordList; 
	ChessMove * LocalChessMove;
	Event * LocalEvent = malloc(sizeof(Event));
	Boolean ExitStateFlag = False, UndoMoveFlag = False;

	/*main loop*/
	CurrentPlayer = MainChessBoard->WhitePlayer;
	while (GameOnFlag){
	 	 UndoMoveFlag = False;
	 
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
						if (CheckSelectOwnPiece(Coordinate1, CurrentPlayer))	ExitStateFlag = True; 
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
				Model_UndoLastMove(MainChessBoard, MainMoveList);
				continue;
			} else if (!GameOnFlag) continue;
			
			/*state 2: One coordinate selected*/
			ExitStateFlag = False;
			while (!ExitStateFlag){
			 	/*highlight the legal coordinates of selected piece*/
				LegalChessCoordList = Model_GetLegalCoordinates(MainChessBoard, Coordinate1->Piece, CurrentPlayer);
				HighlightCoordinates(MainChessBoard, LegalChessCoordList);
				
				LocalEvent = View_GetEvent(MainChessBoard, LocalEvent);
				switch (LocalEvent->Type){
					case SelectCoordinate:
						Coordinate2 = LocalEvent->Coordinate;
						if (CheckCoordinatesSamePlayer(Coordinate1, Coordinate2)) Coordinate1 = Coordinate2;
						else if (ChessCoordinateList_CheckRedundancy(LegalChessCoordList, Coordinate2)) ExitStateFlag = True; 
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
				
				/*free the current legal coordinate list*/
				ChessCoordinateList_Free(LegalChessCoordList);
			}
			
			if (UndoMoveFlag){
				Model_UndoLastMove(MainChessBoard, MainMoveList);
				continue;
			} else if (!GameOnFlag) continue;
			
			/*construct chess move then perform it*/
			LocalChessMove = ChessMove_Initialize();
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

static Boolean CheckSelectOwnPiece(ChessCoordinate * Coord, ChessPlayer * PlayerToChoose){
	if (!Coord->Piece) return False;
	if (Coord->Piece->Player != PlayerToChoose) return False;
	else return True;
}

static Boolean CheckCoordinatesSamePlayer(ChessCoordinate * Coord1, ChessCoordinate * Coord2){
	if (!Coord1->Piece || !Coord2->Piece) return False;
	if (Coord1->Piece->Player != Coord2->Piece->Player) return False;
	return True;
}