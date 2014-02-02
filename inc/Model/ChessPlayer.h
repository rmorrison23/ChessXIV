#ifndef PLAYER_H
#define PLAYER_H

#include "ChessStructures.h"
#include <time.h>
#include "Model.h"

/*#include "ChessPiece.h"*/


ChessPiece * ChessPlayer_GetChessPiece(ChessPlayer * Player, ChessPieceTypeEnum Type, int index);
ChessMoveList * ChessPlayer_GetAllLegalMoves(ChessBoard * board, ChessPlayer * player, ChessMoveList * history);
void ChessPlayer_UpdateTime(ChessPlayer * Player);

#endif
