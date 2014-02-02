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

void ChessPlayer_UpdateTime(ChessPlayer * Player) {
  time_t current;
  
  time(&current);
  if(Player->OtherPlayer->StartTime != NULL) {
    Player->OtherPlayer->ElapsedTime += difftime(current, Player->OtherPlayer->StartTime);
}
  time(&(Player->StartTime)); 
  
}

ChessMoveList * ChessPlayer_GetAllLegalMoves(ChessBoard * board, ChessPlayer * player, ChessMoveList * history){
	
	/*ChessCoordinateList * coordlist = Model_GetAllLegalCoordinate(board, player, player, history);	*/
	ChessCoordinateList * coordlist;
	ChessMoveList * list = ChessMoveList_Initialize();
	int i;
	
	for ( i = 0; i < 16; i++ )
	{
		if (player->Pieces[i]->AliveFlag)
		{
			coordlist = Model_GetLegalCoordinates(board, player->Pieces[i], player, history);
			ChessCoordinateNode * CurrNode = coordlist->FirstNode;
			
			while (CurrNode){
				ChessMove * NewMove = ChessMove_Initialize();
				NewMove->MovePiece = player->Pieces[i];
				NewMove->StartPosition = player->Pieces[i]->Coordinate;
				NewMove->NextPosition = CurrNode->Coordinate;
				NewMove->MoveType = Model_GetMoveType(board, NewMove);
				NewMove->CapturePiece = NewMove->NextPosition->Piece;
				ChessMoveList_AppendMove(list, NewMove);
				CurrNode = CurrNode->NextNode;
			}
			ChessCoordinateList_Free(coordlist);
		}
	}
	
	return list;
	
}
