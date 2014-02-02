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

#define SDL_COLOR_SCREEN_TITLE          (SDL_Color) {0xA8, 0xC6, 0xDB}
#define SDL_COLOR_SELETED_BUTTON 	(SDL_Color) {0x29, 0xEF, 0x48}
#define SDL_COLOR_NORMAL_BUTTON 	(SDL_Color) {255, 255, 255}

#define SDL_INT_TEXT_SIZE               50

typedef enum {Color, Image, Text, Button, Outline} ObjectType;
typedef enum {
	Option_OnePlayer, Option_TwoPlayer, Option_AIvsAI, 		\
	Option_Black, Option_White,						\
	Option_EasyAI, Option_MediumAI, Option_DifficultAI,		\
	Option_PlayButton, \
	Title, Background, \
	Label_Color, Label_Difficulty	   \
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
	
	/*Text*/int TextSize; char FontName[255]; char String[255];
	
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
