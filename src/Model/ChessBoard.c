#include "ChessBoard.h"


ChessBoard * InitializeChessBoard(void){
	
	/*malloc the board*/
	ChessBoard * ChessBoardToReturn = (ChessBoard *) malloc(sizeof(ChessBoard));
	assert(ChessBoardToReturn);
  
	/*malloc two players*/
	ChessBoardToReturn->WhitePlayer = (ChessPlayer *) malloc(sizeof(ChessPlayer));
	ChessBoardToReturn->BlackPlayer = (ChessPlayer *) malloc(sizeof(ChessPlayer));
	assert(ChessBoardToReturn->WhitePlayer && ChessBoardToReturn->BlackPlayer);
	ChessBoardToReturn->WhitePlayer->PlayerColor = White;
	ChessBoardToReturn->BlackPlayer->PlayerColor = Black;

#if 0	
	/*switch the AI choice*/
	switch(AIChoice){
		case 0:		/*human vs human*/
			ChessBoardToReturn->WhitePlayer->PlayerControl = Human;
			ChessBoardToReturn->BlackPlayer->PlayerControl = Human;
			break;
		case 1:		/*human vs computer*/
			switch (ColorChoice){
				case 0:		/*human is white*/
					ChessBoardToReturn->WhitePlayer->PlayerControl = Human;
					ChessBoardToReturn->BlackPlayer->PlayerControl = AI;
					break;
				case 1:
					ChessBoardToReturn->WhitePlayer->PlayerControl = AI;
					ChessBoardToReturn->BlackPlayer->PlayerControl = Human;
					break;
			}
			break;
		case 2:		/*computer vs computer*/
			ChessBoardToReturn->WhitePlayer->PlayerControl = Human;
			ChessBoardToReturn->BlackPlayer->PlayerControl = Human;
			break;
	}
#endif
	
	/*malloc all coordinate on the board*/
	int i,j;
	for (i = 0; i < CHESS_BOARD_MAX_ROW; i++){
		for (j = 0; j < CHESS_BOARD_MAX_COL; j++){
			ChessBoardToReturn->Board[i][j]	= (ChessCoordinate *) malloc(sizeof(ChessCoordinate));
			assert(ChessBoardToReturn->Board[i][j]);
			ChessBoardToReturn->Board[i][j]->Piece = NULL;
			ChessBoardToReturn->Board[i][j]->Rank = i;
			ChessBoardToReturn->Board[i][j]->File = j;
		}
	}
	
	/*malloc each piece and assign all double links*/
	/*White first*/
	/*Pawns x 8*/
	ChessPiece * CurrPiece;
	for (i = 0; i < 8; i++){
		CurrPiece = (ChessPiece *) malloc(sizeof(ChessPiece));
		assert(CurrPiece);
		CurrPiece->Type = Pawn;
		CurrPiece->Index = i;
		CurrPiece->Player = ChessBoardToReturn->WhitePlayer;
		CurrPiece->Coordinate = ChessBoardToReturn->Board[1][i];
		CurrPiece->AliveFlag = True;
		ChessBoardToReturn->WhitePlayer->Pawn[i] = CurrPiece;
		ChessBoardToReturn->Board[1][i]->Piece = CurrPiece;
	}
	
	/*Rook x 2*/
	for (i = 0; i < 2; i++){
		CurrPiece = (ChessPiece *) malloc(sizeof(ChessPiece));
		assert(CurrPiece);
		CurrPiece->Type = Rook;
		CurrPiece->Index = i;
		CurrPiece->Player = ChessBoardToReturn->WhitePlayer;
		CurrPiece->Coordinate = ChessBoardToReturn->Board[0][7*i];
		CurrPiece->AliveFlag = True;
		ChessBoardToReturn->WhitePlayer->Rook[i] = CurrPiece;
		ChessBoardToReturn->Board[0][7*i]->Piece = CurrPiece;
	}
	
	/*Knight x 2*/
	for (i = 0; i < 2; i++){
		CurrPiece = (ChessPiece *) malloc(sizeof(ChessPiece));
		assert(CurrPiece);
		CurrPiece->Type = Knight;
		CurrPiece->Index = i;
		CurrPiece->Player = ChessBoardToReturn->WhitePlayer;
		CurrPiece->Coordinate = ChessBoardToReturn->Board[0][1+5*i];
		CurrPiece->AliveFlag = True;
		ChessBoardToReturn->WhitePlayer->Knight[i] = CurrPiece;
		ChessBoardToReturn->Board[0][1+5*i]->Piece = CurrPiece;
	}
	
	/*Bishop x 2*/
	for (i = 0; i < 2; i++){
		CurrPiece = (ChessPiece *) malloc(sizeof(ChessPiece));
		assert(CurrPiece);
		CurrPiece->Type = Bishop;
		CurrPiece->Index = i;
		CurrPiece->Player = ChessBoardToReturn->WhitePlayer;
		CurrPiece->Coordinate = ChessBoardToReturn->Board[0][2+3*i];
		CurrPiece->AliveFlag = True;
		ChessBoardToReturn->WhitePlayer->Bishop[i] = CurrPiece;
		ChessBoardToReturn->Board[0][2+3*i]->Piece = CurrPiece;
	}
	
	/*Queen x 1*/
	CurrPiece = (ChessPiece *) malloc(sizeof(ChessPiece));
	assert(CurrPiece);
	CurrPiece->Type = Queen;
	CurrPiece->Index = 0;
	CurrPiece->Player = ChessBoardToReturn->WhitePlayer;
	CurrPiece->Coordinate = ChessBoardToReturn->Board[0][3];
	CurrPiece->AliveFlag = True;
	ChessBoardToReturn->WhitePlayer->Queen[0] = CurrPiece;
	ChessBoardToReturn->Board[0][3]->Piece = CurrPiece;
	
	/*King x 1*/
	CurrPiece = (ChessPiece *) malloc(sizeof(ChessPiece));
	assert(CurrPiece);
	CurrPiece->Type = King;
	CurrPiece->Index = 0;
	CurrPiece->Player = ChessBoardToReturn->WhitePlayer;
	CurrPiece->Coordinate = ChessBoardToReturn->Board[0][4];
	CurrPiece->AliveFlag = True;
	ChessBoardToReturn->WhitePlayer->King[0] = CurrPiece;
	ChessBoardToReturn->Board[0][4]->Piece = CurrPiece;
	
	
	/*Then black*/
	/*Pawns x 8*/
	for (i = 0; i < 8; i++){
		CurrPiece = (ChessPiece *) malloc(sizeof(ChessPiece));
		assert(CurrPiece);
		CurrPiece->Type = Pawn;
		CurrPiece->Index = i;
		CurrPiece->Player = ChessBoardToReturn->BlackPlayer;
		CurrPiece->Coordinate = ChessBoardToReturn->Board[6][i];
		CurrPiece->AliveFlag = True;
		ChessBoardToReturn->BlackPlayer->Pawn[i] = CurrPiece;
		ChessBoardToReturn->Board[6][i]->Piece = CurrPiece;
	}
	
	/*Rook x 2*/
	for (i = 0; i < 2; i++){
		CurrPiece = (ChessPiece *) malloc(sizeof(ChessPiece));
		assert(CurrPiece);
		CurrPiece->Type = Rook;
		CurrPiece->Index = i;
		CurrPiece->Player = ChessBoardToReturn->BlackPlayer;
		CurrPiece->Coordinate = ChessBoardToReturn->Board[7][7*i];
		CurrPiece->AliveFlag = True;
		ChessBoardToReturn->BlackPlayer->Rook[i] = CurrPiece;
		ChessBoardToReturn->Board[7][7*i]->Piece = CurrPiece;
	}
	
	/*Knight x 2*/
	for (i = 0; i < 2; i++){
		CurrPiece = (ChessPiece *) malloc(sizeof(ChessPiece));
		assert(CurrPiece);
		CurrPiece->Type = Knight;
		CurrPiece->Index = i;
		CurrPiece->Player = ChessBoardToReturn->BlackPlayer;
		CurrPiece->Coordinate = ChessBoardToReturn->Board[7][1+5*i];
		CurrPiece->AliveFlag = True;
		ChessBoardToReturn->BlackPlayer->Knight[i] = CurrPiece;
		ChessBoardToReturn->Board[7][1+5*i]->Piece = CurrPiece;
	}
	
	/*Bishop x 2*/
	for (i = 0; i < 2; i++){
		CurrPiece = (ChessPiece *) malloc(sizeof(ChessPiece));
		assert(CurrPiece);
		CurrPiece->Type = Bishop;
		CurrPiece->Index = i;
		CurrPiece->Player = ChessBoardToReturn->BlackPlayer;
		CurrPiece->Coordinate = ChessBoardToReturn->Board[7][2+3*i];
		CurrPiece->AliveFlag = True;
		ChessBoardToReturn->BlackPlayer->Bishop[i] = CurrPiece;
		ChessBoardToReturn->Board[7][2+3*i]->Piece = CurrPiece;
	}
	
	/*Queen x 1*/
	CurrPiece = (ChessPiece *) malloc(sizeof(ChessPiece));
	assert(CurrPiece);
	CurrPiece->Type = Queen;
	CurrPiece->Index = 0;
	CurrPiece->Player = ChessBoardToReturn->BlackPlayer;
	CurrPiece->Coordinate = ChessBoardToReturn->Board[7][3];
	CurrPiece->AliveFlag = True;
	ChessBoardToReturn->BlackPlayer->Queen[0] = CurrPiece;
	ChessBoardToReturn->Board[7][3]->Piece = CurrPiece;
	
	/*King x 1*/
	CurrPiece = (ChessPiece *) malloc(sizeof(ChessPiece));
	assert(CurrPiece);
	CurrPiece->Type = King;
	CurrPiece->Index = 0;
	CurrPiece->Player = ChessBoardToReturn->BlackPlayer;
	CurrPiece->Coordinate = ChessBoardToReturn->Board[7][4];
	CurrPiece->AliveFlag = True;
	ChessBoardToReturn->BlackPlayer->King[0] = CurrPiece;
	ChessBoardToReturn->Board[7][4]->Piece = CurrPiece;
  return ChessBoardToReturn;
}
