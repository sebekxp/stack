#include "stdafx.h"
#include "interface.h"
#include "mStack.h"
#include "messError.h"
#include "mData.h"
#include <stdlib.h>
#include "utilities.h"



static char *tab[] =
{
	(char*)"[0] - Push",			     //INTERF_PUSH
	(char*)"[1] - Pop",				    //INTERF_POP	
	(char*)"[2] - Display stack",	   //INTERF_DISPLAY_STACK
	(char*)"[3] - Clear",		      //INTERF_CLEAR
	(char*)"[4] - Find lastname",    //INTERF_FIND_LASTNAME
	(char*)"[5] - Save to file",    //INTERF_SAVE_TO_FILE
	(char*)"[6] - Load from file", //INTERF_LOAD_FROM_FILE
	(char*)"[7] - Exit"           //INTERF_STOP
};
void menu() {
	size_t i;
	for (i = 0; i < TOTAL; ++i) {
		printf("%s\n", tab[i]);
	}

}

void push() {
	char name[256];
	char lastName[256];
	printf("\nName: ");
	scanf("%s", &name);
	printf("Last name: ");
	scanf("%s", &lastName);

	int year, fos; //fos - field of study
	printf("Year: ");
	year = readIntFrom(0);
	printf("\n");
	printf("[0]-MATEMATYKA\n"
		"[1]-INFORMATYKA\n"
		"[2]-FIZYKA\n");
	printf("Field of study: ");
	fos = readIntFromTo(0, 2);
	printf("\n");

	void *pDat = MDATA_Push(strlen(name),name,strlen(lastName),lastName,year, (KIERUNEK)fos);
	if (!STACK_Push(pDat)) {
		messError(MEM_ALOC_ERROR);
	}
}

void pop() {
	 STACKDATA_Free();
}
void clear() {
	STACK_Free();
}
void find_lastname() {
	char str[128];
	printf("Input lastname\n");
	scanf_s("%s", &str, sizeof(str));
	MDATA *serachDat;
	serachDat = (MDATA*)malloc(sizeof(MDATA));

	memset(serachDat, 0, sizeof(MDATA));
	serachDat->lastName = _strdup(str);


	void * pData = STACK_Search(serachDat, MDATA_SerchLastName, 1); //make a first search

	if (pData) {
		printf("        __________________________________________________________________________\n");
		printf("       |%-14s|%-14s|%-11s|%-12s|\n", "\t  NAME ", "\t    LAST NAME    ", " YEAR OF BIRTH ", " FIELD OF STUDY ");
		printf("       |_____________________|___________________|_______________|________________|\n");
		printf("Found: ");
		MDATA_Print(pData);
		printf("       |_____________________|___________________|_______________|________________|\n");
	}
	else {
		printf("\n\n%s not found\n\n",serachDat->lastName);
	}
	while (pData) {
		pData = STACK_Search(serachDat, MDATA_SerchLastName, 0); 
		if (pData) {
			printf("Found: ");
			MDATA_Print(pData);
			printf("       |_____________________|___________________|_______________|________________|\n");
		}
	}
	MDATA_Free((void*)serachDat);
}
void displayStack() {
	STACK_displayStack();
}
