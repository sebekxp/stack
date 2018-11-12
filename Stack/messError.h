#ifndef ERROR_MESSAGES__H
#define ERROR_MESSAGES__H
#include "mStack.h"

enum ERROR_MESSAGES
{
	MEM_ALOC_ERROR,			  //0
	INCORR_INDEX_WARN,	     //1
	MEM_ALLOC_NOT_FATAL,    //2
	FATAL_ERROR,		   //3
	NO_FILE,			  //4
	LAST                 //LAST
};

void messError(enum ERROR_MESSAGES mess);
void exitError(FILE *file, void *tmp, __int64 *arr, FreeData ptrFreeFunc);
void exitErrorStack(FILE *file, __int64 *arr);

#endif