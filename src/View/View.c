#include "View.h"

unsigned char AskUserChooseColor(){
  unsigned char ValidFlag = 0;
  unsigned int ReturnChoice;
  while (ValidFlag == 0){    
    printf("What color do you like?\n\t1.White\n\t2.Black\nYour choice: ");
    scanf("%d", &ReturnChoice);
    if (ReturnChoice < 1 || ReturnChoice > 2) 
      printf("Invalid choice\n");
    else
      ValidFlag = 1;
  }
  return ReturnChoice-1;
 
}

unsigned char AskUserAIChoice(){
  unsigned char ValidFlag = 0;
  unsigned int ReturnChoice;
  while (ValidFlag == 0){    
    printf("What game AI do you like?\n\t1.Human vs. Human\n\t2.Human vs. Computer\n\t3.Computer vs. Computer\nYour choice: ");
    scanf("%d", &ReturnChoice);
    if (ReturnChoice < 1 || ReturnChoice > 3) 
      printf("Invalid choice\n");
    else
      ValidFlag = 1;
  }
  return ReturnChoice-1;
  
}

void DisplayChessBoard(ChessBoard * CurrChessBoard){
 int i, j;
 for (i = CHESS_BOARD_MAX_ROW - 1; i >= 0 ; i--){
  printf("%d  |  ", i + 1);
  for (j = 0; j < CHESS_BOARD_MAX_COL; j++){    
    PrintChessCoordinate(CurrChessBoard->Board[i][j]);
    printf("  ");
  }
  printf("\n");
 }
}

void PrintChessCoordinate(ChessCoordinate CurrCoord){
  ChessPiece CurrPiece = CurrCoord.OccupyingPiece;
  unsigned char PieceLetter;
  switch(CurrPiece.Type){
    case Pawn:
      PieceLetter = 'P';
      break;
    case Rook: 
      PieceLetter = 'R';
      break;
    case Knight:
      PieceLetter = 'N';
      break;
    case Bishop:
      PieceLetter = 'B';
      break;
    case Queen:
      PieceLetter = 'Q';
      break;
    case King:
      PieceLetter = 'K';
      break;
    case None:
      break;
    default:
      assert(0);
      break;
  }
    
  if (CurrPiece.Type != None){
    if (CurrPiece.Player.PlayerColor == Black) PieceLetter += 'a' - 'A';
    printf("%c%d", PieceLetter, CurrPiece.Index);
  } else
    printf("- ");
  
}