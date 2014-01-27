#include "Model.h"

#define TEST_COORDINATE_LIST  

int main(void){
#ifdef TEST_COORDINATE_LIST  
	ChessCoordinateList * MainList = malloc(sizeof(ChesscoordinateList));
	
	ChessCoordinateList_Free(MainList);
#endif
  return 0;
}