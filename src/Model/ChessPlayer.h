#ifndef PLAYER_H
#define PLAYER_H

#include "ChessStructures.h"
#if 0
/*#include "ChessPiece.h"*/


typedef enum {Human, AI} 	PlayerControlEnum;
typedef enum {White, Black} 	PlayerColorEnum;

typedef struct ChessPieceStruct ChessPiece;

typedef struct {
	PlayerColorEnum 	PlayerColor;
	PlayerControlEnum	PlayerControl;

	/*list all the pieces that could belong to a player*/
	ChessPiece * Pawn[8];
	ChessPiece * Rook[2];
	ChessPiece * Knight[2];
	ChessPiece * Bishop[2];
	ChessPiece * Queen[1];
	ChessPiece * King[1];
} ChessPlayer;
#endif
#endif