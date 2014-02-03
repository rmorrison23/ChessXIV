#include "View.h"
#include "Model.h"

#ifdef GUI_ENABLE
int main(void){
	ViewHandle * MainViewHandle = View_Initialize();
	ChessBoard * MainChessBoard = ChessBoard_Initialize();
	/*Event * LocalEvent = SetOptions(MainViewHandle, MainChessBoard);  */
	DisplayChessBoard(MainViewHandle, MainChessBoard);
	Event * LocalEvent = View_GetEvent(MainViewHandle, MainChessBoard, LocalEvent);
	
	MainViewHandle = View_CleanUp(MainViewHandle);
	
	  
	TTF_Quit();
	SDL_Quit();
	return 0;
}

#endif