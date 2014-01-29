#ifndef MODEL_H
#define MODEL_H
#include <stdio.h>
#include <stdlib.h>

/*include headers inside Model directory*/
#include "ChessStructures.h"
#include "ChessBoard.h"
#include "ChessPlayer.h"
#include "ChessCoordinateList.h"
#include "ChessMoveList.h"
#include "ChessMove.h"
#include "ChessCoordinate.h"
#include "ArtificialIntelligence.h"


ChessBoard * Model_Initialize(void);

Boolean Model_CheckLegalMove(ChessBoard *, ChessMove *);

ChessCoordinateList * Model_GetLegalCoordinates(ChessBoard *, ChessPiece *, ChessPlayer *);

ChessCoordinateList * Model_GetAllLegalCoordinate( ChessBoard * board, ChessPlayer * player, ChessPlayer * PlayerInTurn);

/* done, actually move the pieces to its destination */
ChessBoard * Model_PerformMove(ChessBoard *, ChessMoveList *, ChessMove *);

/*done,  undo a move */
ChessBoard * Model_UndoLastMove(ChessBoard *, ChessMoveList *);

/* almost done, If this chess player is checkmakte, return True*/
Boolean Model_CheckCheckmate(ChessBoard *, ChessPlayer *);

/* done, If this chess player is in checked position and must get out, return True*/
Boolean Model_CheckCheckedPosition(ChessBoard *, ChessPlayer *);

/* almost done */
Boolean Model_Stalemate(ChessBoard *, ChessPlayer *);

ChessMove * Model_GetBestMove(ChessBoard *, ChessPlayer *);

void Model_CleanUp(ChessBoard *, ChessMoveList *);

void ModelSpeak(void);

#endif
