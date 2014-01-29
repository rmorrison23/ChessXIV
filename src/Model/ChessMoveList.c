#include "ChessMoveList.h"


ChessMoveList * ChessMoveList_AppendMove(ChessMoveList * List, ChessMove * Move){
	ChessMoveNode * NewNode = malloc(sizeof(ChessMoveNode));
	assert(NewNode);
	NewNode->Move = Move;
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
		free(CurrNode->Move);
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

ChessMoveList * ChessMoveList_PopLastMove(ChessMoveList * List){
	if (!List->FirstNode) return List;
	
	/*not empty list*/
	if (List->LastNode->PrevNode){
		/*list has more than 1 move*/
		free(List->LastNode->Move);
		List->LastNode = List->LastNode->PrevNode;
		free(List->LastNode->NextNode);
		List->LastNode->NextNode = NULL;
	} else {
		/*exactly 1 move*/
		free(List->LastNode->Move);
		free(List->LastNode);
		List->FirstNode = NULL;
		List->LastNode = NULL;
	}
	return List;
}