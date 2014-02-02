#ifndef VIEW_STRUCTURES_H
#define VIEW_STRUCTURES_H


/*may add more type of event here*/
typedef enum {NoEvent, SelectCoordinate, UndoMove, Exit, AskTransform, Checkmate, Stalemate,	\
	ButtonClicked, CoordinateClicked, InCheck
} EventTypeEnum;

#ifdef GUI_ENABLE
typedef struct ObjectHandleStruct ObjectHandle;
#endif

/*may add more things to hang on to the event here*/
typedef struct {
	EventTypeEnum Type;
	ChessCoordinate * Coordinate;
	ChessPlayer *	Player;
	ChessPieceTypeEnum	PieceType;
#ifdef GUI_ENABLE
	ObjectHandle *	Object;
#endif
} Event;

#ifdef GUI_ENABLE

#define SDL_COLOR_SELETED_BUTTON 	(SDL_Color) {255,165,0}
#define SDL_COLOR_NORMAL_BUTTON 	(SDL_Color) {165,165,255}

typedef enum {Color, Image, Text, Button, Coordinate, Outline} ObjectType;
typedef enum {
	Option_OnePlayer, Option_TwoPlayer, Option_AIvsAI, 		\
	Option_Black, Option_White,						\
	Option_EasyAI, Option_MediumAI, Option_DifficultAI,		\
	Option_PlayButton, \
	Title, Background \
	
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
	
	/*Text and button*/int TextSize; char * FontName; char * String;
	
  /*color, coordinate or outline*/SDL_Color Color; int hexR; int hexG; int hexB; int hexA;
	
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

typedef struct {
	WindowHandle * CurrentWindow;	
} ViewHandle;
#endif

#endif