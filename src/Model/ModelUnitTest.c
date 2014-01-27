#include "Model.h"

#define TEST_COORDINATE_LIST  

int main(void){
#ifdef TEST_COORDINATE_LIST  
	ChessCoordinateList * MainList = ChessCoordinateList_Initialize();
	ChessCoordinateList * SupportList = ChessCoordinateList_Initialize();
	ChessBoard * MainBoard = ChessBoard_Initialize();
	
	int i;
	for (i = 0; i < 8; i++){
		MainList = ChessCoordinateList_AppendCoord(MainList, MainBoard->Board[i][7-i]);
	}
	
	for (i = 0; i < 8; i++){
		SupportList = ChessCoordinateList_AppendCoord(SupportList, MainBoard->Board[i][i]);
	}
	
	MainList = ChessCoordinateList_AppendNoRedundancy(MainList, SupportList);
	
	ChessCoordinateList_Free(MainList);
	ChessBoard_Free(MainBoard);
#endif
  return 0;
}