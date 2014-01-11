#ifndef CHESSCOORDINATE_H
#define CHESSCOORDINATE_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "ChessPiece.h"



typedef struct {
  /*unsigned char Rank, File;*/
  ChessPiece OccupyingPiece;
} ChessCoordinate;

#endif