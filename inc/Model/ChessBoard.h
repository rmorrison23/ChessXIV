#ifndef CHESSBOARD_H
#define CHESSBOARD_H


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#include "ChessStructures.h"

ChessBoard * ChessBoard_InitializeEmpty(void);
ChessBoard * ChessBoard_Initialize(void);
void ChessBoard_Free(ChessBoard *);

#endif