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
	return NewMove;
}

