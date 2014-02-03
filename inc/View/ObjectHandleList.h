#ifndef OBJECT_LIST_H
#define OBJECT_LIST_H
#include "View.h"

ObjectHandleList * ObjectHandleList_Initialize(void);
ObjectHandleList * ObjectHandleList_AppendObject(ObjectHandleList * List, ObjectHandle * Object);
void ObjectHandleList_DeepFree(ObjectHandleList * List);
void ObjectHandleList_ShallowFree(ObjectHandleList * List);
ObjectHandleList * GetObjectListByTag(ObjectHandleList * List, ObjectTagEnum Tag);
#endif