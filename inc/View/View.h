#ifndef VIEW_H
#define VIEW_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Model.h"

/*****************************************************************
 * Common define
 *****************************************************************/



#ifdef GUI_ENABLE
#ifdef LINUX_OS
	#include "SDL.h"
	#include "SDL_image.h"
	#include "SDL_ttf.h"
#else
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
	#include <SDL2_ttf/SDL_ttf.h>
#endif
#endif


#include "ViewStructures.h"


#ifdef GUI_ENABLE

#include "render.h"
#include "display.h"
#include "constants.h"
#include "sdlUtilities.h"
#include "ObjectHandleList.h"
#include "ObjectHandle.h"


#else
typedef struct {
	ChessPlayer * CurrentPlayer;		/*just dummy variable for ViewHandle of commandline display*/
	Event * ViewHandleEvent;
} ViewHandle;
#endif




/*initialize*/
ViewHandle * View_Initialize(void);

/*clean up*/
ViewHandle * View_CleanUp(ViewHandle *);

/*for settings*/
Event * SetOptions(ViewHandle *, ChessBoard *);

/*for displaying*/
void DisplayChessBoard(ViewHandle * MainViewHandle, ChessBoard * MainBoard);
void HighlightCoordinates(ViewHandle * MainViewHandle, ChessBoard * MainBoard, ChessCoordinateList * CoordList);

/*get event from user*/
/*this function is supposed to overwrite the input pointer with new event data*/
Event * View_GetEvent(ViewHandle * MainViewHandle, ChessBoard * CurrBoard, Event *);


/*DisplayEvent*/
void View_DisplayEvent(ViewHandle * MainViewHandle, ChessBoard * CurrBoard, Event *);

void View_ConcludeGame(ViewHandle * MainViewHandle, ChessPlayer *);



/*for transformation: ask user which type to transform to*/
Event * View_AskMoveTransform(ViewHandle * MainViewHandle, ChessPlayer * ChessPlayerAsking);
#endif 
