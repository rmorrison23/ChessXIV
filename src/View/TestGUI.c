#include "View.h"
#include "Model.h"

#ifdef GUI_ENABLE
int main(void){
	ViewHandle * MainViewHandle = View_Initialize();
	ChessBoard * MainChessBoard = ChessBoard_Initialize();
	/*Event * LocalEvent = SetOptions(MainViewHandle, MainChessBoard);  */
	/*drawChessBoard(MainViewHandle);
	getchar();*/

	DisplayChessBoard(MainViewHandle, MainChessBoard);
		Event * LocalEvent = View_GetEvent(MainViewHandle, MainChessBoard, LocalEvent);
#if 1
	/*print rank and file of the selected coordinate*/
	if (LocalEvent->Type == SelectCoordinate){
		printf("Rank %d, File %d\n", LocalEvent->Coordinate->Rank, LocalEvent->Coordinate->File);
	}
	
	/*get some coordinate list*/
	ChessCoordinateList * TempList = ChessCoordinateList_Initialize();
	ChessCoordinateList_AppendCoord(TempList, MainChessBoard->Board[0][0]);
	ChessCoordinateList_AppendCoord(TempList, MainChessBoard->Board[1][0]);
	ChessCoordinateList_AppendCoord(TempList, MainChessBoard->Board[2][0]);
	
	HighlightCoordinates(MainViewHandle, MainChessBoard, TempList);
	getchar();
#endif	
	MainViewHandle = View_CleanUp(MainViewHandle);

	  
	TTF_Quit();
	SDL_Quit();
	return 0;
}

#endif