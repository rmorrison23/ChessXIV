#ifndef OBJECT_LIST_H
#define OBJECT_LIST_H
#include "View.h"

ObjectHandleList * ObjectHandleList_Initialize(void);
ObjectHandleList * ObjectHandleList_AppendObject(ObjectHandleList * List, ObjectHandle * Object);
#endif