#include "ChessPlayer.h"

ChessPiece * ChessPlayer_GetChessPiece(ChessPlayer * Player, ChessPieceTypeEnum Type, int index){
	int i;
	for (i = 0; i < 16; i++){
		if (Player->Pieces[i]->Type == Type && Player->Pieces[i]->Index == index){
			return Player->Pieces[i];
		}
	}
	return 0;
}