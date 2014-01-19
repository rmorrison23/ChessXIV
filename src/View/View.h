#ifndef VIEW_H
#define VIEW_H
#include <stdlib.h>
#include <stdio.h>

#include "Model.h"

/*may add more type of event here*/
typedef enum {SelectCoordinate, UndoMove} EventTypeEnum;

/*may add more things to hang on to the event here*/
typedef struct {
	EventTypeEnum EventType;
	ChessCoordinate * Coordinate;
	ChessPlayer *	Player;
} Event;

/*for settings*/
PlayerControlEnum AskWhitePlayerControl(void);
PlayerControlEnum AskBlackPlayerControl(void);

/*for displaying*/
void DisplayChessBoard(ChessBoard *);



#ifdef GUI_ENABLE
/*get event from user*/
Event * View_GetEvent(void);



#else
/*get input coordinate from user*/
ChessCoordinate * View_GetCoordinate(void);

#endif

/*static void PrintChessCoordinate(ChessPiece * CurrPiece);*/
#endif 
