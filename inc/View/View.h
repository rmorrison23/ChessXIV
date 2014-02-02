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



#define SDL_COLOR_SELETED_BUTTON 	(SDL_Color) {255,165,0}
#define SDL_COLOR_NORMAL_BUTTON 	(SDL_Color) {165,165,255}

typedef enum {Color, Image, Text, Button} ObjectType;
typedef enum {OnePlayerButton, TwoPlayerButton, AIvsAIButton, 	\
	Option_OnePlayer, Option_TwoPlayer, Option_AIvsAI, 		\
	Option_Black, Option_White,						\
	Option_EasyAI, Option_MediumAI, Option_DifficultAI,		\
	Option_PlayButton
} ObjectTagEnum;

struct ObjectHandleStruct {
	/*id info*/
	ObjectType			Type;
	ObjectTagEnum		Tag;
	EventTypeEnum		Event;
	int				Index;
	
	/*location information*/
	int X,Y, Width, Height;
	
	/*texture to change*/
	SDL_Texture * Texture;
	
	/*information only apply to certain types*/
	/*Image*/char * ImageFileName;
	
	/*Text*/int TextSize; char * FontName; char * String;
	
  /*Color*/SDL_Color Color; int hexR; int hexG; int hexB; int hexA;
	
};

typedef struct ObjectHandleNodeStruct ObjectHandleNode;
struct ObjectHandleNodeStruct {
	ObjectHandleNode * PrevNode, * NextNode;
	
	ObjectHandle * Object;
};



typedef struct {
	ObjectHandleNode * FirstNode, * LastNode;
} ObjectHandleList;

typedef struct {
	SDL_Window * Window;
	SDL_Renderer * WindowRenderer;
	ObjectHandleList * ObjectList;
} WindowHandle;
>>>>>>> finish writing View.c for user option. No test yet.

#ifdef GUI_ENABLE

#include "render.h"
#include "display.h"
#include "constants.h"
#include "sdlUtilities.h"
#include "ObjectHandleList.h"
#include "ObjectHandle.h"


#else
typedef struct {
	int a;		/*just dummy variable for ViewHandle of commandline display*/
} ViewHandle;
#endif




/*initialize*/
ViewHandle * View_Initialize(void);

/*clean up*/
ViewHandle * View_CleanUp(ViewHandle *);

/*for settings*/
ChessBoard * SetOptions(ViewHandle *, ChessBoard *);

/*for displaying*/
void DisplayChessBoard(ChessBoard *);
void HighlightCoordinates(ChessBoard *, ChessCoordinateList *);

/*get event from user*/
/*this function is supposed to  overwrite the input pointer with new event data*/
Event * View_GetEvent(ChessBoard * CurrBoard, Event *);
ChessCoordinate * View_GetOneCoordinate(ChessBoard *);

/*DisplayEvent*/
void View_DisplayEvent(ChessBoard * CurrBoard, Event *);

void View_ConcludeGame(ChessBoard *);

/*for transformation: ask user which type to transform to*/
ChessPieceTypeEnum View_AskMoveTransform(void);
#endif 
