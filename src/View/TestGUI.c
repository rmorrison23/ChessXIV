#include "View.h"
#include "Model.h"

#ifdef GUI_ENABLE
int main(void){
	ViewHandle * MainViewHandle = View_Initialize();
	ChessBoard * MainChessBoard = ChessBoard_Initialize();
	Event * LocalEvent = SetOptions(MainViewHandle, MainChessBoard);  
	
	MainViewHandle = View_CleanUp(MainViewHandle);
	
	  
	TTF_Quit();
	SDL_Quit();
	return 0;
}

#endif