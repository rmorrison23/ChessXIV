#include "ObjectHandle.h"


ObjectHandle * ObjectHandle_Initialize(ObjectType type, int x, int y, int width, int height){
	ObjectHandle * Handle = malloc(sizeof(ObjectHandle));
	Handle->Type = type;
	Handle->X = x;
	Handle->Y = y;
	Handle->Width = width;
	Handle->Height = height;
	
	Handle->ImageFileName = NULL;
	/*text and color too set NULL*/
	return Handle;
	
}

ObjectHandle_Render(ViewHandle * MainHandle, ObjectHandle * Object){
	switch (Object->Type){
	case Image:
	  assert(Object->ImageFileName);
	  Object->Texture =  loadTexture(Object->ImageFileName, MainHandle->CurrentWindow->WindowRenderer);
	  if (Object->Width > 0 && Object->Height > 0){
	    renderTexture(Handle->Texture, MainHandle->CurrentWindow->WindowRenderer, Handle->X, Handle->Y, Handle->Width, Handle->Height);
	  } else {
	    
	  }
	  break;
	case Text:
	  Object->Texture = renderText(ObjectHandle->String, ObjectHandle->imageFileName, ObjectHandle->Color, ObjectHandle->TextSize, MainHandle->CurrentWindow->WindowRenderer);
	  break;
	case Color:
	  Object->Texture = renderFilledBox(ObjectHandle->hexR, ObjectHandle->hexG, ObjectHandle->hexB, ObjectHandle->hexA, ObjectHandle->X, ObjectHandle->Y, ObjectHandle->Width, ObjectHandle->Height, MainHandle->CurrentWindow->WindowRenderer);
	  break;
	case Outline:
	  Object->Texture = renderEmptyBox(ObjectHandle->hexR, ObjectHandle->hexG, ObjectHandle->hexB, ObjectHandle->hexA, ObjectHandle->X, ObjectHandle->Y, ObjectHandle->Width, ObjectHandle->Height, MainHandle->CurrentWindow->WindowRenderer, X, Y, Width, Height);
	  break;
	}
}

ObjectHandle * ObjectHandle_Free(ObjectHandle * object){
	free(object);
	return NULL;
}
