#ifndef VIEW_H
#define VIEW_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Model.h"

/*****************************************************************
 * Common define
 *****************************************************************/

/*may add more type of event here*/
typedef enum {SelectCoordinate, UndoMove, Exit, SelectTranformation, Checkmate, Stalemate} EventTypeEnum;

/*may add more things to hang on to the event here*/
typedef struct {
	EventTypeEnum Type;
	ChessCoordinate * Coordinate;
	ChessPlayer *	Player;
} Event;

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

typedef enum {Color, Image, Text, Outline} ObjectType;
typedef enum {Title, OnePlayerButton, TwoPlayerButton, AIvsAIButton} ObjectTag;

typedef struct {
	/*id info*/
	ObjectType		Type;
	ObjectTag		Tag;
	int			Index;
	
	/*location information*/
	int X,Y, Width, Height;
	
	/*texture to change*/
	SDL_Texture * Texture;
	
	/*information only apply to certain types*/
	/*Image*/char  ImageFileName[255];
	
	/*Text*/int TextSize; char * FontName; char * String;
	
  /*Color*/SDL_Color Color; int hexR; int hexG; int hexB; int hexA;
	
} ObjectHandle;

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

typedef struct {
	WindowHandle * CurrentWindow;	
} ViewHandle;

#include "render.h"
#include "display.h"
#include "constants.h"
#include "sdlUtilities.h"
#include "ObjectHandleList.h"

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
