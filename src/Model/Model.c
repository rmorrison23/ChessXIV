#include "Model.h"

ChessBoard * Model_Initialize(void){
	return InitializeChessBoard();
}

/* move piece to next location */
ChessBoard * Model_PerformMove(ChessBoard * board, ChessMoveList * moveList, ChessMove * move)
{
	/* the place to move to has an enemy piece */
	if (move->NextPosition->Piece != NULL)
	{
		/* kill it */
		move->NextPosition->Piece->AliveFlag = False;
		/* set that dead piece coordinate to null */
		move->NextPosition->Piece->Coordinate = NULL;
		
		/* it is dead */
		move->CaptureFlag = True;
	}
	/* piece to move, moved to next coordinate */
	move->StartPosition->Piece->Coordinate = move->NextPosition;
	
	/* delete piece pointer at previous location */
	move->StartPosition->Piece = NULL;

/*Need review to match new ChessMoveList*/
#if 0
	/* update move list */
	/* forward link */
	while (moveList->NextMove != NULL)
	{
		moveList = moveList->NextMove;
	}
	moveList->NextMove = move;
	
	/*backward link */
	moveList->NextMove->PrevMove = moveList;
	
	/*set the move of the next move */
	moveList->NextMove->Move = move;
#endif
	return board;
}

/* uses GetLegalCoordinates */
/* see if move is legal */
Boolean Model_CheckLegalMove(ChessBoard * board, ChessMove * moveTo)
{
	return True;
}

void Model_CleanUp(ChessBoard * CurrBoard, ChessMoveList * MoveList){
	ChessMoveNode * MoveNode1, * MoveNode2;
	MoveNode1 = MoveList->FirstMove;
	
	while (MoveNode1){
		MoveNode2 = MoveNode1->NextNode;
		free(MoveNode1->Move);
		free(MoveNode1);
		MoveNode1 = MoveNode2;
	}
		
	free(MoveList);
	
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
