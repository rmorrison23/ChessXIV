#ifndef CHESS_COORDINATE_LIST_H
#define CHESS_COORDINATE_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ChessStructures.h"

ChessCoordinateList * ChessCoordinateList_AppendNoRedundancy(ChessCoordinateList *, ChessCoordinateList *);
Boolean ChessCoordinateList_CheckRedundancy(ChessCoordinateList *, ChessCoordinate *);
ChessCoordinateList * ChessCoordinateList_AppendNode(ChessCoordinateList *, ChessCoordinateNode *);

#endif