#include "ChessMove.h"

ChessMove * ChessMove_Initialize(void){
	ChessMove * NewMove = malloc(sizeof(ChessMove));
	assert(NewMove);
	NewMove->MovePiece = NULL;
	NewMove->StartPosition = NULL;
	NewMove-> NextPosition = NULL;
	NewMove->CapturePiece = NULL;
	NewMove->CaptureFlag = False;
	NewMove->MoveType = Normal;
	NewMove->Rating = 0;
	return NewMove;
}

Boolean ChessMove_IsTransformation(ChessMove * Move){
 	/*in this function you are given 3 pieces of information
	Move->MovePiece: The piece that moves in this turn
	Move->StartPosition and Move->NextPosition*/
	
	if (False) return True;		/*replace here with conditions of transforming*/ 
	else return False;
}

ChessMove * ChessMove_Free(ChessMove * Move){
	free(Move);
	return NULL;
}