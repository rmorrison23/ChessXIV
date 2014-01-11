#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include "Player.h"

typedef enum {Pawn, Rook, Knight, Bishop, Queen, King, None}  ChessPieceTypeEnum;

typedef struct {
 ChessPieceTypeEnum 	Type;
 unsigned char		Index;
 PlayerType		Player;
} ChessPiece;

#endif