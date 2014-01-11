#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#define CHESS_BOARD_MAX_ROW 8
#define CHESS_BOARD_MAX_COL 8

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ChessCoordinate.h"

typedef struct {
  ChessCoordinate Board[CHESS_BOARD_MAX_ROW][CHESS_BOARD_MAX_COL];
} ChessBoard, * ChessBoard_pt;

ChessBoard * InitializeChessBoard(unsigned char AIChoice, unsigned char ColorChoice);

#endif