
#include "ChessBoard.h"


ChessBoard * InitializeChessBoard(unsigned char AIChoice, unsigned char ColorChoice){
  ChessBoard * ChessBoardToReturn = (ChessBoard *) malloc(sizeof(ChessBoard));
  assert(ChessBoardToReturn);
  
  int i,j;
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
  
  return ChessBoardToReturn;
}