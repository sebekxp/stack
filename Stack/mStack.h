#ifndef STACK__H
#define STACK__H

struct STACK
{
	void *sData;
	STACK *next;
};

typedef int (CompData)(void * pCurData, void * pSearchData);
typedef void(*FreeData)(void *pData);
typedef void(*FreeData)(void *pData);
typedef void(*DisplayData)(void *pDat);
typedef void(*SaveToFile)(void *ptr,FILE *save, __int64 *arr);
typedef void*(*ReadFromFile)(FILE* file, __int64 *arr, unsigned int rec, unsigned int noItems);
typedef void(*TableHeader)();
typedef void(*TableBottom)();

void STACK_Init(FreeData pFreeFunc, DisplayData pDisplayData, SaveToFile pSaveToFile,
	ReadFromFile pReadFromFile,TableHeader pTableHeader, TableBottom pTableBottom);

STACK *STACK_Push(void *data);
STACK *STACK_Pop();
void STACK_Free();
void STACKDATA_Free();
void *STACK_Search(void *pSearch, CompData compFunc, int firstEntry);
void STACK_saveToFile();
void STACK_readfromFile();
void STACK_displayStack();

#endif


