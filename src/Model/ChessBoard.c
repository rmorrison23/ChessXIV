
#include "ChessBoard.h"


ChessBoard * InitializeChessBoard(unsigned char AIChoice, unsigned char ColorChoice){
	
	/*malloc the board*/
	ChessBoard * ChessBoardToReturn = (ChessBoard *) malloc(sizeof(ChessBoard));
	assert(ChessBoardToReturn);
  
	/*malloc two players*/
	ChessBoardToReturn->WhitePlayer = (ChessPlayer *) malloc(sizeof(ChessPlayer));
	ChessBoardToReturn->BlackPlayer = (ChessPlayer *) malloc(sizeof(ChessPlayer));
	assert(ChessBoardToReturn->WhitePlayer && ChessBoardToReturn->BlackPlayer);
	ChessBoardToReturn->WhitePlayer->PlayerColor = White;
	ChessBoardToReturn->BlackPlayer->PlayerColor = Black;
	
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
	ChessBoardToReturn->WhitePlayer->Queen[0] = CurrPiece;
	ChessBoardToReturn->Board[0][3]->Piece = CurrPiece;
	
	/*King x 1*/
	CurrPiece = (ChessPiece *) malloc(sizeof(ChessPiece));
	assert(CurrPiece);
	CurrPiece->Type = King;
	CurrPiece->Index = 0;
	CurrPiece->Player = ChessBoardToReturn->WhitePlayer;
	CurrPiece->Coordinate = ChessBoardToReturn->Board[0][4];
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
	ChessBoardToReturn->BlackPlayer->Queen[0] = CurrPiece;
	ChessBoardToReturn->Board[7][3]->Piece = CurrPiece;
	
	/*King x 1*/
	CurrPiece = (ChessPiece *) malloc(sizeof(ChessPiece));
	assert(CurrPiece);
	CurrPiece->Type = King;
	CurrPiece->Index = 0;
	CurrPiece->Player = ChessBoardToReturn->BlackPlayer;
	CurrPiece->Coordinate = ChessBoardToReturn->Board[7][4];
	ChessBoardToReturn->BlackPlayer->King[0] = CurrPiece;
	ChessBoardToReturn->Board[7][4]->Piece = CurrPiece;
#if 0	
	PlayerControlEnum WhitePlayerControl, BlackPlayerControl;
  /*switch the AI choice*/
  switch(AIChoice){
    case 0:		/*human vs human*/
      WhitePlayerControl = Human;
      BlackPlayerControl = Human;
      break;
    case 1:		/*human vs computer*/
      switch (ColorChoice){
	case 0:		/*human is white*/
	  WhitePlayerControl = Human;
	  BlackPlayerControl = AI;
	  break;
	case 1:
	  WhitePlayerControl = AI;
	  BlackPlayerControl = Human;
	  break;
      }
      break;
    case 2:		/*computer vs computer*/
      WhitePlayerControl = Human;
      BlackPlayerControl = Human;
      break;
  }
  
  /*get the white one first*/
  
  ChessBoardToReturn->Board[0][0].OccupyingPiece.Type = Rook;
  ChessBoardToReturn->Board[0][0].OccupyingPiece.Index = 0;
  ChessBoardToReturn->Board[0][0].OccupyingPiece.Player.PlayerColor = White;
  ChessBoardToReturn->Board[0][0].OccupyingPiece.Player.PlayerControl = WhitePlayerControl;
  
  ChessBoardToReturn->Board[0][1].OccupyingPiece.Type = Knight;
  ChessBoardToReturn->Board[0][1].OccupyingPiece.Index = 0;
  ChessBoardToReturn->Board[0][1].OccupyingPiece.Player.PlayerColor = White;
  ChessBoardToReturn->Board[0][1].OccupyingPiece.Player.PlayerControl = WhitePlayerControl;
  
  ChessBoardToReturn->Board[0][2].OccupyingPiece.Type = Bishop;
  ChessBoardToReturn->Board[0][2].OccupyingPiece.Index = 0;
  ChessBoardToReturn->Board[0][2].OccupyingPiece.Player.PlayerColor = White;
  ChessBoardToReturn->Board[0][2].OccupyingPiece.Player.PlayerControl = WhitePlayerControl;
  
  ChessBoardToReturn->Board[0][3].OccupyingPiece.Type = Queen;
  ChessBoardToReturn->Board[0][3].OccupyingPiece.Index = 0;
  ChessBoardToReturn->Board[0][3].OccupyingPiece.Player.PlayerColor = White;
  ChessBoardToReturn->Board[0][3].OccupyingPiece.Player.PlayerControl = WhitePlayerControl;
  
  ChessBoardToReturn->Board[0][4].OccupyingPiece.Type = King;
  ChessBoardToReturn->Board[0][4].OccupyingPiece.Index = 0;
  ChessBoardToReturn->Board[0][4].OccupyingPiece.Player.PlayerColor = White;
  ChessBoardToReturn->Board[0][4].OccupyingPiece.Player.PlayerControl = WhitePlayerControl;
  
  ChessBoardToReturn->Board[0][5].OccupyingPiece.Type = Bishop;
  ChessBoardToReturn->Board[0][5].OccupyingPiece.Index = 1;
  ChessBoardToReturn->Board[0][5].OccupyingPiece.Player.PlayerColor = White;
  ChessBoardToReturn->Board[0][5].OccupyingPiece.Player.PlayerControl = WhitePlayerControl;
  
  ChessBoardToReturn->Board[0][6].OccupyingPiece.Type = Knight;
  ChessBoardToReturn->Board[0][6].OccupyingPiece.Index = 1;
  ChessBoardToReturn->Board[0][6].OccupyingPiece.Player.PlayerColor = White;
  ChessBoardToReturn->Board[0][6].OccupyingPiece.Player.PlayerControl = WhitePlayerControl;
  
  ChessBoardToReturn->Board[0][7].OccupyingPiece.Type = Rook;
  ChessBoardToReturn->Board[0][7].OccupyingPiece.Index = 1;
  ChessBoardToReturn->Board[0][7].OccupyingPiece.Player.PlayerColor = White;
  ChessBoardToReturn->Board[0][7].OccupyingPiece.Player.PlayerControl = WhitePlayerControl;
  
  for (i = 0; i < CHESS_BOARD_MAX_COL; i++){
    ChessBoardToReturn->Board[1][i].OccupyingPiece.Type = Pawn;
    ChessBoardToReturn->Board[1][i].OccupyingPiece.Index = i;
    ChessBoardToReturn->Board[1][i].OccupyingPiece.Player.PlayerColor = White;
    ChessBoardToReturn->Board[1][i].OccupyingPiece.Player.PlayerControl = WhitePlayerControl;
  }
  
  /*black pieces*/
  ChessBoardToReturn->Board[7][0].OccupyingPiece.Type = Rook;
  ChessBoardToReturn->Board[7][0].OccupyingPiece.Index = 0;
  ChessBoardToReturn->Board[7][0].OccupyingPiece.Player.PlayerColor = Black;
  ChessBoardToReturn->Board[7][0].OccupyingPiece.Player.PlayerControl = BlackPlayerControl;
  
  ChessBoardToReturn->Board[7][1].OccupyingPiece.Type = Knight;
  ChessBoardToReturn->Board[7][1].OccupyingPiece.Index = 0;
  ChessBoardToReturn->Board[7][1].OccupyingPiece.Player.PlayerColor = Black;
  ChessBoardToReturn->Board[7][1].OccupyingPiece.Player.PlayerControl = BlackPlayerControl;
  
  ChessBoardToReturn->Board[7][2].OccupyingPiece.Type = Bishop;
  ChessBoardToReturn->Board[7][2].OccupyingPiece.Index = 0;
  ChessBoardToReturn->Board[7][2].OccupyingPiece.Player.PlayerColor = Black;
  ChessBoardToReturn->Board[7][2].OccupyingPiece.Player.PlayerControl = BlackPlayerControl;
  
  ChessBoardToReturn->Board[7][3].OccupyingPiece.Type = Queen;
  ChessBoardToReturn->Board[7][3].OccupyingPiece.Index = 0;
  ChessBoardToReturn->Board[7][3].OccupyingPiece.Player.PlayerColor = Black;
  ChessBoardToReturn->Board[7][3].OccupyingPiece.Player.PlayerControl = BlackPlayerControl;
  
  ChessBoardToReturn->Board[7][4].OccupyingPiece.Type = King;
  ChessBoardToReturn->Board[7][4].OccupyingPiece.Index = 0;
  ChessBoardToReturn->Board[7][4].OccupyingPiece.Player.PlayerColor = Black;
  ChessBoardToReturn->Board[7][4].OccupyingPiece.Player.PlayerControl = BlackPlayerControl;
  
  ChessBoardToReturn->Board[7][5].OccupyingPiece.Type = Bishop;
  ChessBoardToReturn->Board[7][5].OccupyingPiece.Index = 1;
  ChessBoardToReturn->Board[7][5].OccupyingPiece.Player.PlayerColor = Black;
  ChessBoardToReturn->Board[7][5].OccupyingPiece.Player.PlayerControl = BlackPlayerControl;
  
  ChessBoardToReturn->Board[7][6].OccupyingPiece.Type = Knight;
  ChessBoardToReturn->Board[7][6].OccupyingPiece.Index = 1;
  ChessBoardToReturn->Board[7][6].OccupyingPiece.Player.PlayerColor = Black;
  ChessBoardToReturn->Board[7][6].OccupyingPiece.Player.PlayerControl = BlackPlayerControl;
  
  ChessBoardToReturn->Board[7][7].OccupyingPiece.Type = Rook;
  ChessBoardToReturn->Board[7][7].OccupyingPiece.Index = 1;
  ChessBoardToReturn->Board[7][7].OccupyingPiece.Player.PlayerColor = Black;
  ChessBoardToReturn->Board[7][7].OccupyingPiece.Player.PlayerControl = BlackPlayerControl;
  
  for (i = 0 ; i < CHESS_BOARD_MAX_COL; i++){
    ChessBoardToReturn->Board[6][i].OccupyingPiece.Type = Pawn;
    ChessBoardToReturn->Board[6][i].OccupyingPiece.Index = i;
    ChessBoardToReturn->Board[6][i].OccupyingPiece.Player.PlayerColor = Black;
    ChessBoardToReturn->Board[6][i].OccupyingPiece.Player.PlayerControl = BlackPlayerControl;
  }
  
  /*get the empty coordinate*/
  for (i = 2 ; i < 6; i++){
    for (j = 0; j < CHESS_BOARD_MAX_COL; j++){
      ChessBoardToReturn->Board[i][j].OccupyingPiece.Type = None;
    }
  }
#endif  
  return ChessBoardToReturn;
}