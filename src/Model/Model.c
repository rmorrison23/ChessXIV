#include "Model.h"

ChessBoard * Model_Initialize(void){
	return InitializeChessBoard();
}

ChessBoard * Model_PerformMove(ChessBoard * board, ChessMoveList * moveList, ChessMove * moveTo)
{
	/* create a new moveList */
	ChessMoveListStruct * newMove = new ChessMoveListStruct;
	
	/*linking previous and next */
	newMove->PrevMove = moveList;
	newMove->NextMove = NULL;
	moveList->NextMove = newMov;
	
	/*storing current move */
	newMove->Move = moveTo;
	
	/*return the board */
	return board;
}

Boolean Model_CheckLegalMove(ChessBoard * board, ChessMove * moveTo)
{
	return true;
}

void Model_CleanUp(ChessBoard * CurrBoard, ChessMoveList * MoveListStart){
	ChessMoveList * MoveListNode1, * MoveListNode2;
	MoveListNode1 = MoveListStart;
	
	while (MoveListNode1){
		MoveListNode2 = MoveListNode1->NextMove;
		free(MoveListNode1);
		MoveListNode1 = MoveListNode2;
	}
	
	
	int i,j;
	for (i = 0; i < CHESS_BOARD_MAX_ROW ; i++){
		for (j = 0; j < CHESS_BOARD_MAX_COL; j++){
			/*free the pieces*/
			if (CurrBoard->Board[i][j]->Piece) free(CurrBoard->Board[i][j]->Piece);
			/*free coordinate*/
			free(CurrBoard->Board[i][j]);
		}
	}
	
	/*free the player*/
	free(CurrBoard->WhitePlayer);
	free(CurrBoard->BlackPlayer);
	
	/*free the board*/
	free(CurrBoard);
	
}
