#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#define CHESS_BOARD_MAX_ROW 8
#define CHESS_BOARD_MAX_COL 8

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#include "ChessStructures.h"
/*
#include "ChessCoordinate.h"
#include "ChessPlayer.h"
*/
typedef struct {
  ChessCoordinate * Board[CHESS_BOARD_MAX_ROW][CHESS_BOARD_MAX_COL];
  ChessPlayer * WhitePlayer, * BlackPlayer;
} ChessBoard;

ChessBoard * InitializeChessBoard(unsigned char AIChoice, unsigned char ColorChoice);

#endif