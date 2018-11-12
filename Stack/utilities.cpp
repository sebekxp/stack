#include "stdafx.h"
#include "utilities.h"

int readIntFromTo(int from, int to) {

	int num;
	int valid = 0;

	do {

		if (scanf("%d", &num) && num >= from && num <= to) {
			valid = 1;
		}
		else {
			printf("Invalid input data!!\n");
		}

		while (getchar() != '\n');

	} while (!valid);

	return num;

}

int readIntFrom(int from) {

	int num;
	int valid = 0;

	do {

		if (scanf("%d", &num) && num >= from) {
			valid = 1;
		}
		else {
			printf("Invalid input data!!\n");
		}

		while (getchar() != '\n');

	} while (!valid);

	return num;

}

