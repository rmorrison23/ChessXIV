#include "ObjectHandle.h"


ObjectHandle * ObjectHandle_Initialize(ObjectType type, ObjectTagEnum TagIn, int x, int y, int width, int height){
	ObjectHandle * Handle = malloc(sizeof(ObjectHandle));
	Handle->Type = type;
	Handle->Tag = TagIn;
	Handle->X = x;
	Handle->Y = y;
	Handle->Width = width;
	Handle->Height = height;
	
	switch (type){
		case Piece:
		case Image:
			Handle->ImageFileName = (char *) malloc(sizeof(char) * 255);
			assert(Handle->ImageFileName);
			break;
		case Text:
		case Button:			
			Handle->FontName = (char *) malloc(sizeof(char) * 255);
			Handle->String = (char *) malloc(sizeof(char) * 255);
			assert(Handle->FontName && Handle->String);
			break;
	}
	
	
	return Handle;
	
}


#if 1


void ObjectHandle_Render(ViewHandle * MainHandle, ObjectHandle * Object){
	switch (Object->Type){
	case Piece:
		switch (Object->PlayerColor){
			case Black:
				switch (Object->PieceType){
					case Pawn:
						strcpy(Object->ImageFileName, "Assets/pieces/B_Pawn.png");
						break;
					case Rook:
						strcpy(Object->ImageFileName, "Assets/pieces/B_Rook.png");
						break;
					case Knight:
						strcpy(Object->ImageFileName, "Assets/pieces/B_Knight.png");
						break;
					case Bishop:
						strcpy(Object->ImageFileName, "Assets/pieces/B_Bishop.png");
						break;
					case Queen:
						strcpy(Object->ImageFileName, "Assets/pieces/B_Queen.png");
						break;
					case King:
						strcpy(Object->ImageFileName, "Assets/pieces/B_King.png");
						break;
				}
				break;
			case White:
				switch (Object->PieceType){
					case Pawn:
						strcpy(Object->ImageFileName, "Assets/pieces/W_Pawn.png");
						break;
					case Rook:
						strcpy(Object->ImageFileName, "Assets/pieces/W_Rook.png");
						break;
					case Knight:
						strcpy(Object->ImageFileName, "Assets/pieces/W_Knight.png");
						break;
					case Bishop:
						strcpy(Object->ImageFileName, "Assets/pieces/W_Bishop.png");
						break;
					case Queen:
						strcpy(Object->ImageFileName, "Assets/pieces/W_Queen.png");
						break;
					case King:
						strcpy(Object->ImageFileName, "Assets/pieces/W_King.png");
						break;
				}
			break;
		}
			
	case Image:
	  assert(Object->ImageFileName);
	  Object->Texture =  loadTexture(Object->ImageFileName, MainHandle->CurrentWindow->WindowRenderer);
	  if (Object->Width > 0 && Object->Height > 0){
	    renderTexture(Object->Texture, MainHandle->CurrentWindow->WindowRenderer, Object->X, Object->Y, Object->Width, Object->Height);
	   
	  } else {
	    
	  }
	  break;
	case Button:
	case Text:

	Object->Texture = renderText(Object->String, Object->FontName, Object->Color, Object->TextSize, MainHandle->CurrentWindow->WindowRenderer);
	renderTexture2(Object->Texture, MainHandle->CurrentWindow->WindowRenderer, Object->X, Object->Y);
	SDL_QueryTexture(Object->Texture , NULL, NULL, &(Object->Width), NULL);
	SDL_QueryTexture(Object->Texture , NULL, NULL, NULL, &(Object->Height));
	/*printf("text is %d wide and %d high\n", Object->Width, Object->Height);*/
	  break;
	case Coordinate:
	case Color:
	  Object->Texture = renderFilledBox(Object->hexR, Object->hexG, Object->hexB, Object->hexA, Object->X, Object->Y, Object->Width, Object->Height, MainHandle->CurrentWindow->WindowRenderer);
	  renderTexture2(Object->Texture, MainHandle->CurrentWindow->WindowRenderer, 0, 0);
	  break;
	case Outline:
	  Object->Texture = renderEmptyBox(Object->hexR, Object->hexG, Object->hexB, Object->hexA, Object->X, Object->Y, Object->Width, Object->Height, MainHandle->CurrentWindow->WindowRenderer);
	  renderTexture2(Object->Texture, MainHandle->CurrentWindow->WindowRenderer, 0, 0);
	  break;
	}
}

ObjectHandle * ObjectHandle_Free(ObjectHandle * object){
	free(object);
	return NULL;
}


void windowRender(ViewHandle * MainHandle){

  	ObjectHandleNode * CurrNode = MainHandle->CurrentWindow->ObjectList->FirstNode;
	while(CurrNode){		
		ObjectHandle_Render(MainHandle, CurrNode->Object);
		CurrNode = CurrNode->NextNode;
	}
	SDL_RenderPresent(MainHandle->CurrentWindow->WindowRenderer);

}
#endif
char * GetTimeString(ChessPlayer * Player, Boolean InTurnFlag) {
	char * ReturnString = malloc(sizeof(char) * 10);
	int minute, second;
	second = floor(78.0/*Player->ElapsedTime*/);
		
	if (InTurnFlag){		
		time_t now;
		time(&now);
		/*second += floor(difftime(now, Player->StartTime));*/
		
	} 
	minute = second / 60;
	second = second % 60;
	sprintf(ReturnString, "%d:%d", minute, second);
	return ReturnString;
}

Event GetSDLEvent(ViewHandle * MainHandle){
	SDL_Event event;
	Event ReturnEvent; ReturnEvent.Type = NoEvent;
	ObjectHandleList * ObjectSelectedList;
	ObjectHandleNode * Node;
	ObjectHandle * ObjectSelected;
	ObjectHandleList * TimerDisplayList;
	Boolean DoneFlag = False;
	
	while (!DoneFlag){
	while(SDL_PollEvent(&event)){

		switch(event.type){
			
			case SDL_QUIT:
				TTF_Quit();
				SDL_Quit();
				exit(1);
				ReturnEvent.Type = Exit;
				DoneFlag = True;
				break;
	
			case SDL_MOUSEBUTTONDOWN:
				/*find out where it is clicked then*/
				ObjectSelectedList = GetObjectByCoordinate(MainHandle, event.motion.x, event.motion.y);
				Node  = ObjectSelectedList->FirstNode;
				while (Node){
					ObjectSelected = Node->Object;
					switch (ObjectSelected->Type){
						case Button:
							ReturnEvent.Type = ButtonClicked;
							ReturnEvent.Object = ObjectSelected;
							DoneFlag = True;
							break;
						case Coordinate:
							ReturnEvent.Type = SelectCoordinate;
							ReturnEvent.Object = ObjectSelected;
							DoneFlag = True;
							break;
						case Piece:
							if (ObjectSelected->Tag == TransformPiece){
								ReturnEvent.Type = PieceClicked;
								ReturnEvent.PieceType = ObjectSelected->PieceType;
								DoneFlag = True;
								break;
							}
							break;
					}
										
					Node = Node->NextNode;
				}
				
				ObjectHandleList_ShallowFree(ObjectSelectedList);
				if (DoneFlag) 
					return ReturnEvent;
				
				
				break;

			default:
				/*update the timer*/
				/*printf("updating timer\n");
				TimerDisplayList = GetObjectListByTag(MainHandle->CurrentWindow->ObjectList, Timer);
				ObjectHandleNode * Node = TimerDisplayList->FirstNode;
				while (Node){
					if (Node->Object->PlayerColor == MainHandle->CurrentPlayer->PlayerColor){
						strcpy(Node->Object->String, GetTimeString(MainHandle->CurrentPlayer, True));
					} else {
						strcpy(Node->Object->String, GetTimeString(MainHandle->CurrentPlayer->OtherPlayer , False));
					}
					Node = Node->NextNode;
				}
				ObjectHandleList_ShallowFree(TimerDisplayList);
				windowRender(MainHandle);			
				printf("finish rendering timer\n");*/
				
				break;
		}      
	} 
	}
 }

ObjectHandleList * GetObjectByCoordinate(ViewHandle * MainHandle, int x, int y){
	ObjectHandleNode * CurrNode = MainHandle->CurrentWindow->ObjectList->FirstNode;
	ObjectHandleList * ReturnList = ObjectHandleList_Initialize();
	ObjectHandle * CurrentObject;
	while (CurrNode){
		CurrentObject = CurrNode->Object;
		if ((CurrentObject->X) < x && (CurrentObject->X + CurrentObject->Width > x) && (CurrentObject->Y < y) && (CurrentObject->Y + CurrentObject->Height > y))
			ObjectHandleList_AppendObject(ReturnList, CurrentObject);
		/*else {
			printf("%d %d %d %d doesn't cover %d %d\n", CurrentObject->X, CurrentObject->X + CurrentObject->Width, CurrentObject->Y, CurrentObject->Y + CurrentObject->Height, x, y);
		}*/
		CurrNode = CurrNode->NextNode;
	}
	
	return ReturnList;
}

ObjectHandle * GetObjectByTag(ViewHandle * MainHandle, ObjectTagEnum Tag){
	ObjectHandleNode * CurrNode = MainHandle->CurrentWindow->ObjectList->FirstNode;
	while (CurrNode){
		if (CurrNode->Object->Tag == Tag) return CurrNode->Object;		
		CurrNode = CurrNode->NextNode;
	}
	return NULL;
}

ObjectHandle * GetGUICoordinate(ViewHandle *MainViewHandle, int rank, int file){
	ObjectHandleNode * CurrNode = MainViewHandle->CurrentWindow->ObjectList->FirstNode;
	while (CurrNode){
		if (CurrNode->Object->Type == Coordinate)
			if (CurrNode->Object->Rank == rank && CurrNode->Object->File == file)
				return CurrNode->Object;
		CurrNode = CurrNode->NextNode;
	}
	return NULL;
}


