#include "Model.h"

ChessBoard * Model_Initialize(void){
	return InitializeChessBoard();
}

/* move piece to next location */
ChessBoard * Model_PerformMove(ChessBoard * board, ChessMoveList * moveList, ChessMove * move)
{
	/* the place to move to has an enemy piece */
	if (move->End->Piece != NULL)
	{
		/* kill it */
		move->End->Piece->AliveFlag = False;
		/* set that dead piece coordinate to null */
		move->End->Piece->Coordinate = NULL;
		
		/* it is dead */
		move->CaptureFlag = True;
	}
	/* piece to move, moved to next coordinate */
	move->Start->Piece->Coordinate = move->End;
	
	/* delete piece pointer at previous location */
	move->Start->Piece = NULL;
	
	/* update move list */
	/* go to the end of the link-list */
	while (moveList->NextMove != NULL)
	{
		moveList = moveList->NextMove;
	}
	/* forward link */
	moveList->NextMove = move;
	
	/*backward link */
	moveList->NextMove->PrevMove = moveList;
	
	/*set the move of the next move */
	moveList->NextMove->Move = move;
	
	return board;
}

/* uses GetLegalCoordinates */
/* see if move is legal */
Boolean Model_CheckLegalMove(ChessBoard * board, ChessMove * moveTo)
{
	return True;
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
