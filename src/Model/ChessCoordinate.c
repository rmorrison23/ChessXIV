#include "ChessCoordinate.h"

ChessCoordinate * ChessCoordinate_Offset(ChessCoordinate * Source, int RankOffset, int FileOffset){
	int DestRank = (int)(Source->Rank) + RankOffset, DestFile = (int)(Source->File) + FileOffset;
	
	if (DestRank < 0 || DestRank >= CHESS_BOARD_MAX_ROW || DestFile < 0 || DestFile >= CHESS_BOARD_MAX_COL){
		return NULL;
	} else {
		return Source->MainBoard->Board[DestRank][DestFile];
	}
  
}