#include "View.h"
#include "Model.h"

#ifdef GUI_ENABLE
int main(void){
	ViewHandle * MainViewHandle = View_Intialize(void);
	ChessBoard * MainChessBoard = ChessBoard_Initialize();
	MainViewHandle = View_GetOptions(MainViewHandle, MainChessBoard);  
	MainViewHandle = View_CleanUp(MainViewHandle);
	
	
	TTF_Quit();
	SDL_Quit();
}

#endif