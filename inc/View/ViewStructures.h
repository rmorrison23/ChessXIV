#ifndef VIEW_STRUCTURES_H
#define VIEW_STRUCTURES_H


/*may add more type of event here*/
typedef enum {NoEvent, SelectCoordinate, UndoMove, Exit, SelectTranformation, Checkmate, Stalemate,	\
	Option_OnePlayer_Clicked, Option_TwoPlayer_Clicked, Option_AIvsAI_Clicked, 		\
	Option_Black_Clicked, Option_White_Clicked,						\
	Option_EasyAI_Clicked, Option_MediumAI_Clicked, Option_DifficultAI_Clicked,		\
	Option_PlayButton_Clicked
} EventTypeEnum;

#ifdef GUI_ENABLE
typedef struct ObjectHandleStruct ObjectHandle;
#endif

/*may add more things to hang on to the event here*/
typedef struct {
	EventTypeEnum Type;
	ChessCoordinate * Coordinate;
	ChessPlayer *	Player;
#ifdef GUI_ENABLE
	ObjectHandle *	Object;
#endif
} Event;


#define SDL_COLOR_SELETED_BUTTON 	(SDL_Color) {255,165,0}
#define SDL_COLOR_NORMAL_BUTTON 	(SDL_Color) {165,165,255}

typedef enum {Color, Image, Text, Button, Outline} ObjectType;
typedef enum {OnePlayerButton, TwoPlayerButton, AIvsAIButton, 	\
	Option_OnePlayer, Option_TwoPlayer, Option_AIvsAI, 		\
	Option_Black, Option_White,						\
	Option_EasyAI, Option_MediumAI, Option_DifficultAI,		\
	Option_PlayButton, \
	Title
	
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
	/*Image*/char  ImageFileName[255];
	
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

typedef struct {
	WindowHandle * CurrentWindow;	
} ViewHandle;

#endif