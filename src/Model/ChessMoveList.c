#include "ChessMoveList.h"


ChessMoveList * ChessMoveList_AppendMove(ChessMoveList * List, ChessMove * Coord){
	ChessMoveNode * NewNode = malloc(sizeof(ChessMoveNode));
	assert(NewNode);
	NewNode->Move = Coord;
	NewNode->NextNode = NULL;
	NewNode->List = List;
	if (List->FirstNode){		
		List->LastNode->NextNode = NewNode;
		NewNode->PrevNode = List->LastNode;
		List->LastNode = NewNode;
	} else {
		/*empty list*/
		List->FirstNode = NewNode;
		List->LastNode = NewNode;
		NewNode->PrevNode = NULL;
		
	}
	return List;
}


void ChessMoveList_Free(ChessMoveList * List){
	ChessMoveNode * CurrNode = List->FirstNode, *NextNode;
	while (CurrNode){
		NextNode = CurrNode->NextNode;
		free(CurrNode);
		CurrNode = NextNode;
	}
	free(List);
}

ChessMoveList * ChessMoveList_Initialize(void){
	ChessMoveList * NewList = malloc(sizeof(ChessMoveList));
	NewList->FirstNode = NULL;
	NewList->LastNode = NULL;
	return NewList;
}