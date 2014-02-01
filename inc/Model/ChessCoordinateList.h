#ifndef CHESS_COORDINATE_LIST_H
#define CHESS_COORDINATE_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ChessStructures.h"

ChessCoordinateList * ChessCoordinateList_AppendNoRedundancy(ChessCoordinateList *, ChessCoordinateList *);
Boolean ChessCoordinateList_CheckRedundancy(ChessCoordinateList *, ChessCoordinate *);
ChessCoordinateList * ChessCoordinateList_AppendCoord(ChessCoordinateList *, ChessCoordinate *);
void ChessCoordinateList_Free(ChessCoordinateList *);
ChessCoordinateList * ChessCoordinateList_Initialize(void);
ChessCoordinateList * ChessCoordinateList_RemoveAtNode( ChessCoordinateList *, ChessCoordinateNode *);
#endif