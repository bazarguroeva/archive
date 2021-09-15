#include "tree.h"
#include <stdio.h>

int compare(const void *p1, const void *p2){
	int x1, x2;
	x1 = ((*(Tree**)p1)->freq);
	x2 = ((*(Tree**)p2)->freq);
	return x2 - x1;
}
double count_size(FILE *f){
	double count = 0;
	unsigned char byte;
	fread(&byte, sizeof(unsigned char), 1, f);
	while (!feof(f)){
		count++;
		fread(&byte, sizeof(unsigned char), 1, f);
	}
	return count;
}
void count_frequency(FILE *f, int *arr){
	unsigned char symb;
	for (int i = 0; i < 256; i++)
		arr[i] = 0;
	fread(&symb, sizeof(unsigned char), 1, f);
	while (!feof(f)){
		arr[symb]++;
		fread(&symb, sizeof(unsigned char), 1, f);
	}
}
