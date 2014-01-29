#ifndef CHESS_MOVE_LIST_H
#define CHESS_MOVE_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ChessStructures.h"



ChessMoveList * ChessMoveList_AppendMove(ChessMoveList *, ChessMove *);
void ChessMoveList_Free(ChessMoveList *);
ChessMoveList * ChessMoveList_Initialize(void);
ChessMoveList * ChessMoveList_PopLastMove(ChessMoveList *);
#endif