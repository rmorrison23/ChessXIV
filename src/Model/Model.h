#ifndef MODEL_H
#define MODEL_H
#include <stdio.h>
#include <stdlib.h>

/*include headers inside Model directory*/
#include "ChessStructures.h"
#include "ChessBoard.h"

ChessBoard * Model_Initialize(void);

ChessBoard * Model_CheckLegalMove(ChessBoard *, ChessMove *);

ChessCoordinateList * Model_GetLegalCoordinate(ChessBoard *, ChessPiece *);

ChessBoard * Model_Move(ChessBoard *, ChessMoveList *, ChessMove *);

ChessBoard * Model_UndoLastMove(ChessBoard *, ChessMoveList *);

Boolean Model_CheckCheckmate(ChessBoard *, ChessPlayer *);



void ModelSpeak(void);
#endif
