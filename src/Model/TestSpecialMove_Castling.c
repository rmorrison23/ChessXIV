#include <stdio.h>
#include <stdlib.h>

#include "Model.h"
#include "View.h"

int main(void){
	char temp_char;
	
	/*initialize chess board emtpy*/
	ChessBoard * MainChessBoard = ChessBoard_InitializeEmpty();
	/*move list*/
	ChessMoveList * LocalMoveList = ChessMoveList_Initialize();
	
	/*set up king and rook of white, we'll test on them*/
	ChessPiece * WKing = ChessPlayer_GetChessPiece(MainChessBoard->WhitePlayer, King, 0);
	WKing->AliveFlag = True;
	WKing->Coordinate = MainChessBoard->Board[0][4];
	MainChessBoard->Board[0][4]->Piece = WKing;
	ChessPiece * WRook = ChessPlayer_GetChessPiece(MainChessBoard->WhitePlayer, Rook, 0);
	WRook->AliveFlag = True;
	WRook->Coordinate = MainChessBoard->Board[0][0];
	MainChessBoard->Board[0][0]->Piece = WRook;	
	
	/*set up some other piece of whites*/
		
	/*set up some other pieces of black*/
	ChessPiece * BKing = ChessPlayer_GetChessPiece(MainChessBoard->BlackPlayer, King, 0);
	BKing->AliveFlag = True;
	BKing->Coordinate = MainChessBoard->Board[7][4];
	MainChessBoard->Board[7][4]->Piece = BKing;
	
	ChessPiece * BRook = ChessPlayer_GetChessPiece(MainChessBoard->BlackPlayer, Rook, 0);
	BRook->AliveFlag = True;
	BRook->Coordinate = MainChessBoard->Board[4][3];
	MainChessBoard->Board[4][3]->Piece = BRook;
	/*display the board*/
	DisplayChessBoard(MainChessBoard);
	scanf("%c", &temp_char);
	
	/*do the test twice*/
	int i = 0;
	ChessCoordinateList * LegalCoordList;
	ChessCoordinate * NextPos;
	ChessMove * CurrMove;
	for (i = 0; i < 2; i++){
		/*get legal coordinate by the W King, it should shows positions it can move to*/
		/*conditions must be followed to allow castling (from wiki)*/
		
		/* The king and the chosen rook are on the player's first rank.[3]
		Neither the king nor the chosen rook have previously moved.
		There are no pieces between the king and the chosen rook.
		The king is not currently in check.
		The king does not pass through a square that is attacked by an enemy piece.[4]
		The king does not end up in check. (True of any legal move.)*/
		
		LegalCoordList = Model_GetLegalCoordinates(MainChessBoard, WKing, MainChessBoard->WhitePlayer);		
		
		
		/*highlight the board*/
		HighlightCoordinates(MainChessBoard, LegalCoordList);		
		ChessCoordinateList_Free(LegalCoordList);
				
		/*get coordinate selection from user*/
		NextPos = View_GetOneCoordinate(MainChessBoard);
		
		/*construct a move*/
		CurrMove = ChessMove_Initialize();
		CurrMove->MovePiece = WKing;
		CurrMove->StartPosition = WKing->Coordinate;
		CurrMove->NextPosition = NextPos;
		
		/*perform move*/
		Model_PerformMove(MainChessBoard, LocalMoveList, CurrMove);
		
		/*display the board*/
		DisplayChessBoard(MainChessBoard);
		scanf("%c", &temp_char);
		
		/*do a random move from black*/
		CurrMove = ChessMove_Initialize();
		CurrMove->MovePiece = BKing;
		CurrMove->StartPosition = BKing->Coordinate;
		CurrMove->NextPosition = MainChessBoard->Board[6][4];
		Model_PerformMove(MainChessBoard, LocalMoveList, CurrMove);
		
		/*display the board*/
		DisplayChessBoard(MainChessBoard);
		scanf("%c", &temp_char);
		
		/*undo the move, suppose to reverse both black and and white move*/
		Model_UndoLastMove(MainChessBoard, LocalMoveList);
		
		/*display the board*/
		DisplayChessBoard(MainChessBoard);
		scanf("%c", &temp_char);
	}
	/*free the board*/
	ChessBoard_Free(MainChessBoard);
	
	/*free move list*/
	ChessMoveList_Free(LocalMoveList);
	
	return 0;
}