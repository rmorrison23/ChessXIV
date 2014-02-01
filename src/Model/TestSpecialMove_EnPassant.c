#include <stdio.h>
#include <stdlib.h>

#include "Model.h"
#include "View.h"
#include "Control.h"

int main(void){
	char temp_char;
	
	/*initialize chess board emtpy*/
	ChessBoard * MainChessBoard = ChessBoard_InitializeEmpty();
	MainChessBoard->BlackPlayer->PlayerControl = Human;
	MainChessBoard->WhitePlayer->PlayerControl = Human;
	/*move list*/
	ChessMoveList * LocalMoveList = ChessMoveList_Initialize();
	
	ControlHandle * MainHandle = malloc(sizeof(ControlHandle));
	MainHandle->MainChessBoard = MainChessBoard;
	MainHandle->MainMoveList = LocalMoveList;
	
	/*set up king and 2 paws of white, we'll test on them*/
	ChessPiece * WKing = ChessPlayer_GetChessPiece(MainChessBoard->WhitePlayer, King, 0);
	WKing->AliveFlag = True;
	WKing->Coordinate = MainChessBoard->Board[0][4];
	MainChessBoard->Board[0][4]->Piece = WKing;
	ChessPiece * WPawn[2];
	WPawn[0] = ChessPlayer_GetChessPiece(MainChessBoard->WhitePlayer, Pawn, 0);
	WPawn[0]->AliveFlag = True;
	WPawn[0]->MoveFirstFlag = 0;
	WPawn[0]->Coordinate = MainChessBoard->Board[1][0];
	MainChessBoard->Board[1][0]->Piece = WPawn[0];	
	WPawn[1] = ChessPlayer_GetChessPiece(MainChessBoard->WhitePlayer, Pawn, 2);
	WPawn[1]->AliveFlag = True;
	WPawn[1]->MoveFirstFlag = 0;
	WPawn[1]->Coordinate = MainChessBoard->Board[1][2];
	MainChessBoard->Board[1][2]->Piece = WPawn[1];	
		
	/*set up some other pieces of black*/
	ChessPiece * BKing = ChessPlayer_GetChessPiece(MainChessBoard->BlackPlayer, King, 0);
	BKing->AliveFlag = True;
	BKing->Coordinate = MainChessBoard->Board[7][4];
	MainChessBoard->Board[7][4]->Piece = BKing;
	
	ChessPiece * BPawn[2];
	BPawn[0] = ChessPlayer_GetChessPiece(MainChessBoard->BlackPlayer, Pawn, 0);
	BPawn[0]->AliveFlag = True;
	BPawn[0]->MoveFirstFlag = 2;
	BPawn[0]->Coordinate = MainChessBoard->Board[3][1];
	MainChessBoard->Board[3][1]->Piece = BPawn[0];	
	BPawn[1] = ChessPlayer_GetChessPiece(MainChessBoard->BlackPlayer, Pawn, 2);
	BPawn[1]->AliveFlag = True;
	BPawn[1]->MoveFirstFlag = 2;
	BPawn[1]->Coordinate = MainChessBoard->Board[3][3];
	MainChessBoard->Board[3][3]->Piece = BPawn[1];	
	
	
	/*go into the main loop*/
	MainHandle = Control_MainLoop(MainHandle);

	/*clean up*/
	MainHandle = Control_CleanUp(MainHandle);
	
	return 0;
}
