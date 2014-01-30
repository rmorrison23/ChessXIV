
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

ChessCoordinateList * ChessCoordinateList_RemoveAtNode( ChessCoordinateList * CoordList, ChessCoordinateNode * CoordNode){
	/*if list has only 1 node*/
	if (CoordList->FirstNode == CoordList->LastNode){
		free(CoordList->FirstNode);
		CoordList->FirstNode = NULL;
		CoordList->LastNode = NULL;
	/*if that node is first node*/
	} else if (!CoordNode->PrevNode){	
		CoordList->FirstNode = CoordNode->NextNode;
		CoordNode->NextNode->PrevNode = NULL;
		free(CoordNode);
	/*if that node is last node*/
	} else if(!CoordNode->NextNode) {
		CoordList->LastNode = CoordNode->PrevNode;
		CoordNode->PrevNode->NextNode = NULL;
		free(CoordNode);
	/*node must be in the middle of at least 3 node list*/
	} else {
		CoordNode->NextNode->PrevNode = CoordNode->PrevNode;
		CoordNode->PrevNode->NextNode = CoordNode->NextNode;
		free(CoordNode);
	}
	return CoordList;
}