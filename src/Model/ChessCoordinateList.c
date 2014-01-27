
#include "ChessCoordinateList.h"
ChessCoordinateList * ChessCoordinateList_AppendNoRedundancy(ChessCoordinateList * FirstList, ChessCoordinateList * SecondList){
	ChessCoordinateNode * CurrNode = SecondList->FirstNode;
	while (CurrNode){
		if (!(ChessCoordinateList_CheckRedundancy(FirstList, CurrNode->Coordinate))){
			FirstList = ChessCoordinateList_AppendCoord(FirstList, CurrNode->Coordinate);
		} 
		
		CurrNode = CurrNode->NextNode;
	}
	
	ChessCoordinateList_Free(SecondList);
	return FirstList;
	
}

Boolean ChessCoordinateList_CheckRedundancy(ChessCoordinateList * List, ChessCoordinate * Coord){
	Boolean RedundancyFlag = False;
	ChessCoordinateNode * CurrNode = List->FirstNode;
	while (CurrNode && !RedundancyFlag){
		if (CurrNode->Coordinate == Coord)
			RedundancyFlag = True;
		CurrNode = CurrNode->NextNode;
	}
	return RedundancyFlag;
}

ChessCoordinateList * ChessCoordinateList_AppendCoord(ChessCoordinateList * List, ChessCoordinate * Coord){
	ChessCoordinateNode * NewNode = malloc(sizeof(ChessCoordinateNode));
	assert(NewNode);
	NewNode->Coordinate = Coord;
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


void ChessCoordinateList_Free(ChessCoordinateList * List){
	ChessCoordinateNode * CurrNode = List->FirstNode, *NextNode;
	while (CurrNode){
		NextNode = CurrNode->NextNode;
		free(CurrNode);
		CurrNode = NextNode;
	}
	free(List);
}

ChessCoordinateList * ChessCoordinateList_Initialize(void){
	ChessCoordinateList * NewList = malloc(sizeof(ChessCoordinateList));
	NewList->FirstNode = NULL;
	NewList->LastNode = NULL;
	return NewList;
}