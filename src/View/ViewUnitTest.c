#include "View.h"
#include "Model.h"

#ifdef GUI_ENABLE
int main(void){
  ViewHandle * MainViewHandle = View_Intialize(void);
  ChessBoard * MainChessBoard = ChessBoard_Initialize();
  MainViewHandle = View_GetOptions(MainViewHandle, MainChessBoard);  
  View_DisplayChessBoard(MainViewHandle);
}

#endif