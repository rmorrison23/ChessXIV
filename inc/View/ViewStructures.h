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

#define SDL_COLOR_SCREEN_TITLE          (SDL_Color) {0xA8, 0xC6, 0xDB}
#define SDL_COLOR_SELETED_BUTTON 	(SDL_Color) {0x29, 0xEF, 0x48}
#define SDL_COLOR_NORMAL_BUTTON 	(SDL_Color) {255, 255, 255}
#define SDL_COLOR_HIGHLIGHT_COORDINATE	(SDL_Color) {100, 100, 100}
#define SDL_COLOR_BLACK                 (SDL_Color) {0, 0, 0}

#define SDL_INT_TEXT_SIZE               50

typedef enum {Color, Image, Text, Button, Piece, Coordinate, Outline} ObjectType;
typedef enum {
	Option_OnePlayer, Option_TwoPlayer, Option_AIvsAI, 		\
	Option_Black, Option_White,						\
	Option_EasyAI, Option_MediumAI, Option_DifficultAI,		\
	Option_PlayButton, \
	Title, Background, \
	PieceObject,	\
	Label_Color, Label_Difficulty,	   \
	Option_Undo, Option_Quit,\
	Box,\
	Square
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
  
	/*coordinate*/int Rank, File;
	
	/*piece type*/
	ChessPieceTypeEnum PieceType;
	PlayerColorEnum	PlayerColor;
	
	
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
