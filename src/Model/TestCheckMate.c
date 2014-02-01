#include <stdio.h>
#include <stdlib.h>

#include "Model.h"
#include "View.h"
#include "Control.h"

int main(void){
	
	/*initialize chess board emtpy*/
	ChessBoard * MainChessBoard = ChessBoard_InitializeEmpty();
	/*move list*/
	ChessMoveList * LocalMoveList = ChessMoveList_Initialize();
	
	ControlHandle * MainHandle = malloc(sizeof(ControlHandle));
	MainHandle->MainChessBoard = MainChessBoard;
	MainHandle->MainMoveList = LocalMoveList;
	
	/*set up king and rook of white, we'll test on them*/
	ChessPiece * WKing = ChessPlayer_GetChessPiece(MainChessBoard->WhitePlayer, King, 0);
	WKing->AliveFlag = True;
	WKing->Coordinate = MainChessBoard->Board[0][4];
	MainChessBoard->Board[0][4]->Piece = WKing;
	ChessPiece * WRook = ChessPlayer_GetChessPiece(MainChessBoard->WhitePlayer, Rook, 0);
	WRook->AliveFlag = True;
	WRook->Coordinate = MainChessBoard->Board[0][2];
	MainChessBoard->Board[0][2]->Piece = WRook;
	WRook = ChessPlayer_GetChessPiece(MainChessBoard->WhitePlayer, Rook, 1);
	WRook->AliveFlag = True;
	WRook->Coordinate = MainChessBoard->Board[1][1];
	MainChessBoard->Board[1][1]->Piece = WRook;	
	
	/*set up some other piece of whites*/
		
	/*set up some other pieces of black*/
	ChessPiece * BKing = ChessPlayer_GetChessPiece(MainChessBoard->BlackPlayer, King, 0);
	BKing->AliveFlag = True;
	BKing->Coordinate = MainChessBoard->Board[7][0];
	MainChessBoard->Board[7][0]->Piece = BKing;
	
	ChessPiece * BRook = ChessPlayer_GetChessPiece(MainChessBoard->BlackPlayer, Rook, 0);
	BRook->AliveFlag = True;
	BRook->Coordinate = MainChessBoard->Board[4][3];
	MainChessBoard->Board[4][3]->Piece = BRook;	
	
	/*go into the main loop*/
	MainHandle = Control_MainLoop(MainHandle);

	/*clean up*/
	MainHandle = Control_CleanUp(MainHandle);
	
	return 0;
}