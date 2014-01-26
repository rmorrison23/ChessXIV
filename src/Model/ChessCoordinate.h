#ifndef CHESSCOORDINATE_H
#define CHESSCOORDINATE_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "ChessStructures.h"

/*horizontal movement between coordinates*/
ChessCoordinate * ChessCoordinate_Offset(ChessCoordinate *, char, char);
#endif