#ifndef MODEL_H
#define MODEL_H
#include <stdio.h>
#include <stdlib.h>

/*include headers inside Model directory*/
#include "ChessStructures.h"
#include "ChessBoard.h"
#include "ArtificialIntelligence.h"


ChessBoard * Model_Initialize(void);

Boolean Model_CheckLegalMove(ChessBoard *, ChessMove *);

ChessCoordinateList * Model_GetLegalCoordinates(ChessBoard *, ChessPiece *);

ChessBoard * Model_PerformMove(ChessBoard *, ChessMoveList *, ChessMove *);

ChessBoard * Model_UndoLastMove(ChessBoard *, ChessMoveList *);

Boolean Model_CheckCheckmate(ChessBoard *, ChessPlayer *);

ChessMove * Model_GetBestMove(ChessBoard *, ChessPlayer *);

void Model_CleanUp(ChessBoard *, ChessMoveList *);

void ModelSpeak(void);

#endif
