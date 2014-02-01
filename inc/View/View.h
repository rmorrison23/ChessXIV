#ifndef VIEW_H
#define VIEW_H
#include <stdlib.h>
#include <stdio.h>

#include "Model.h"

/*may add more type of event here*/
typedef enum {SelectCoordinate, UndoMove, Exit, SelectTranformation, Checkmate, Stalemate} EventTypeEnum;

/*may add more things to hang on to the event here*/
typedef struct {
	EventTypeEnum Type;
	ChessCoordinate * Coordinate;
	ChessPlayer *	Player;
} Event;

/*initialize*/
void View_Initialize(void);

/*clean up*/
void View_CleanUp(void);

/*for settings*/
ChessBoard * SetOptions(ChessBoard *);

/*for displaying*/
void DisplayChessBoard(ChessBoard *);
void HighlightCoordinates(ChessBoard *, ChessCoordinateList *);

/*get event from user*/
/*this function is supposed to overwrite the input pointer with new event data*/
Event * View_GetEvent(ChessBoard * CurrBoard, Event *);
ChessCoordinate * View_GetOneCoordinate(ChessBoard *);

/*DisplayEvent*/
void View_DisplayEvent(ChessBoard * CurrBoard, Event *);

void View_ConcludeGame(ChessBoard *);

/*for transformation: ask user which type to transform to*/
ChessPieceTypeEnum View_AskMoveTransform(void);
#endif 
