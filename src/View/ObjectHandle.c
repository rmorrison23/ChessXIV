#include "ObjectHandle.h"


ObjectHandle * ObjectHandle_Initialize(ObjectType type, int x, int y, int width, int height){
	ObjectHandle * Handle = malloc(sizeof(ObjectHandle));
	Handle->Type = type;
	Handle->X = x;
	Handle->Y = y;
	Handle->Width = width;
	Handle->Height = height;
	
	strcpy(Handle->ImageFileName,"");
	/*text and color too set NULL*/
	printf("inside: %p\n", Handle);
	return Handle;
	
}
#if 1
void ObjectHandle_Render(ViewHandle * MainHandle, ObjectHandle * Object){
	switch (Object->Type){
	case Image:
	  assert(Object->ImageFileName);
	  Object->Texture =  loadTexture(Object->ImageFileName, MainHandle->CurrentWindow->WindowRenderer);
	  if (Object->Width > 0 && Object->Height > 0){
	    renderTexture(Object->Texture, MainHandle->CurrentWindow->WindowRenderer, Object->X, Object->Y, Object->Width, Object->Height);
	   
	  } else {
	    
	  }
	  break;
	case Text:
	  Object->Texture = renderText(Object->String, Object->FontName, Object->Color, Object->TextSize, MainHandle->CurrentWindow->WindowRenderer);
	  renderTexture2(Object->Texture, MainHandle->CurrentWindow->WindowRenderer, Object->X, Object->Y);
	  break;
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

  SDL_Renderer *renderer = MainHandle->CurrentWindow->WindowRenderer;


}
#endif
