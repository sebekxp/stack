#include"stdafx.h"
#include <stdlib.h>
#include "mStack.h"
#include "messError.h"
#include "utilities.h"

static STACK *head = NULL;
static FreeData ptrFreeFunc;
static DisplayData ptrDisplayData;
static SaveToFile ptrSaveToFile;
static ReadFromFile ptrReadFromFile;
static TableHeader ptrTableHeader;
static TableBottom ptrTableBottom;

void STACK_Init(FreeData pFreeFunc, DisplayData pDisplayData, SaveToFile pSaveToFile,
	ReadFromFile pReadFromFile, TableHeader pTableHeader, TableBottom pTableBottom) {
	
	head = NULL;
	ptrFreeFunc = pFreeFunc;
	ptrDisplayData = pDisplayData;
	ptrSaveToFile = pSaveToFile;
	ptrReadFromFile = pReadFromFile;
	ptrTableHeader = pTableHeader;
	ptrTableBottom = pTableBottom;

}
void STACK_Free() {
	STACK *curr;
	while ((curr = head) != NULL) {
		head = head->next;		
		ptrFreeFunc(curr->sData);
		free(curr);
	}
}
void STACK_displayStack() {
	
	STACK *tmp = head;

	if (tmp != NULL) {
		puts(" ============================== Stack Content =============================");
		ptrTableHeader();
		do {
			ptrDisplayData(tmp->sData);
			tmp = tmp->next;
		} while (tmp != NULL);
		ptrTableBottom();
	}
	else {
		printf("\n\nStack is empty!!!\n\n");
	}
}

STACK *STACK_Push(void *data) {

	STACK *nElem = (STACK*)malloc(sizeof(STACK)); 
	if (!nElem) {
		messError(MEM_ALOC_ERROR);
		return NULL;
	}

	nElem->sData = data;  
	nElem->next = head;   
	head = nElem;		 

	return head;
}

STACK *STACK_Pop() {

	if (head == NULL) {
		printf("\n\nStack is empty!!!\n\n");
		return NULL;
	}

	STACK *temp = head;
	head = temp->next;
	temp->next = NULL;

	return temp;
}

void STACKDATA_Free() {
	STACK *temp = STACK_Pop();
	if (temp != NULL) {
		ptrFreeFunc(temp->sData);
		free(temp);
	}
}
void *STACK_Search(void *pSearch, CompData compFunc, int firstEntry) {
	static STACK *p;
	STACK *pTemp = NULL;
	if (firstEntry)
		p = head;

	while (p) {
		if (!(compFunc)(p->sData, pSearch)) {
			p = p->next;
		}
		else {
			pTemp = p;
			p = p->next;
			return pTemp->sData;
		}
	}
	return NULL;
}
static int countElem() {
	STACK *tmp = head;
	int count = 0;
	if (tmp != NULL) {
		while (tmp != NULL) {
			count++;
			tmp = tmp->next;
		}
	}
	return count;
}

void STACK_saveToFile() {

	FILE *save;
	save = fopen("binFille.bin", "wb");
	if (!save) {
		messError(NO_FILE);

	}
	STACK *tmp = head;

	int noItems = countElem();

	__int64  *arr = (__int64*)malloc((noItems + 1) * sizeof(__int64));
	if (!arr) {
		exitError(save, tmp->sData, arr, ptrFreeFunc);
	}

	if (fwrite(&noItems, sizeof(unsigned int), 1, save) != 1) {
		exitError(save, tmp->sData, arr, ptrFreeFunc);
	}
	_fseeki64(save, (noItems + 1) * sizeof(__int64), SEEK_CUR);

	size_t i = 0;
	if (tmp != NULL) {
		do {
			arr[i] = ftell(save);
			ptrSaveToFile(tmp->sData, save, &arr[i]);
			tmp = tmp->next;
			i++;
		} while (tmp != NULL);
	}
	arr[i] = ftell(save);
	_fseeki64(save, sizeof(unsigned int), SEEK_SET);
	if (fwrite(arr, sizeof(__int64), noItems + 1, save) != noItems + 1) {
		exitError(save, tmp->sData, arr, ptrFreeFunc);
	}

	if (save)
		fclose(save);
	save = NULL;

	if (arr)
		free(arr);
	arr = NULL;
}

void STACK_readfromFile() {

	STACK_Free();

	FILE *read = fopen("binFille.bin", "rb");
	if (!read) {
		messError(NO_FILE);
	}

	unsigned int noItems = 0, it, rec;
	__int64 *arr = NULL;


	if (fread(&noItems, sizeof(unsigned int), 1, read) != 1) {
		exitErrorStack(read,arr);
	}
	arr = (__int64*)malloc((noItems + 1) * sizeof(__int64));

	if (!arr) {
		exitErrorStack(read, arr);
	}

	if (fread(arr, sizeof(arr[0]), noItems + 1, read) != noItems + 1) {
		exitErrorStack(read, arr);
	}

	for (it = 0; it < noItems; ++it) {

		rec = noItems - it - 1;
		_fseeki64(read, arr[rec], SEEK_SET);

		void* pDat = ptrReadFromFile(read, arr, rec, noItems);
		
		if (!STACK_Push(pDat)) {
			exitErrorStack(read, arr);
		}
	}
	if (arr)
		free(arr);
	arr = NULL;

	if (read)
		fclose(read);
	read = NULL;
}
