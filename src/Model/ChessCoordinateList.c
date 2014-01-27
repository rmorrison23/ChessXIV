
#include "ChessCoordinateList.h"
ChessCoordinateList * ChessCoordinateList_AppendNoRedundancy(ChessCoordinateList * FirstList, ChessCoordinateList * SecondList){
	ChessCoordinateNode * CurrNode = SecondList->FirstNode, * FutureNode;
	while (CurrNode){
		FutureNode = CurrNode->NextNode;
		if (!ChessCoordinateList_CheckRedundancy(FirstList, CurrNode->Coordinate)){
			FirstList = ChessCoordinateList_AppendNode(FirstList, CurrNode);
			CurrNode->List = FirstList;
		} else {			
			free(CurrNode->Coordinate);			
			free(CurrNode);
		}
		
		CurrNode = FutureNode;
	}
	
	free(SecondList);
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

ChessCoordinateList * ChessCoordinateList_AppendNode(ChessCoordinateList * List, ChessCoordinateNode * NewNode){
	
	if (List->LastNode){
		NewNode->NextNode = NULL;
		NewNode->PrevNode = List->LastNode;
		List->LastNode->NextNode = NewNode;
		List->LastNode = NewNode;
	} else {
		/*empty list*/
		List->FirstNode = NewNode;
		List->LastNode = NewNode;
		NewNode->PrevNode = NULL;
		NewNode->NextNode = NULL;
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