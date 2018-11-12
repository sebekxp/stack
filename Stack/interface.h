#ifndef INTERFACE__H
#define INTERFACE__H
enum INTERF
{
	PUSH,
	POP,
	DISPLAY_STACK,
	CLEAR,
	FIND_LASTNAME,
	SAVE_TO_FILE,
	LOAD_FROM_FILE,
	EXIT,
	TOTAL
};
enum KIERUNEK
{
	MATEMATYKA,
	INFORMATYKA,
	FIZYKA
};

void push();
void pop();
void clear();
void displayStack();
void menu();
void find_lastname();

#endif 
