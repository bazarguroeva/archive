#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <malloc.h>
#include "tree.h"
#include "addlib.h"
#include "huffman.h"

int main(int argc, char **argv){
	setlocale(LC_ALL, "Rus");
	FILE *fin = NULL, *arc = NULL, *fout;
	char *finname, *arcname, *com, *foutname;
	finname = (char*)malloc(sizeof(char)* 260);
	arcname = (char*)malloc(sizeof(char)* 260);
	com = (char*)malloc(sizeof(char)* 260);
	foutname = (char*)malloc(sizeof(char)* 260);

	if (argc <= 4){
		if (argc <= 3){
			if (argc <= 2){
				if (argc <= 1){
					printf("\tEnter the command: ");
					scanf("%s", com);
				}
				else 
					strcpy(com, argv[1]);

				printf("\tEnter the archiver name: ");
				scanf("%s", arcname);
			}
			else{
				strcpy(com, argv[1]);
				strcpy(arcname, argv[2]);
			}
		
			printf("\tEnter the input file name: ");
			scanf("%s", finname);
		}
		else{
			strcpy(com, argv[1]);
			strcpy(arcname, argv[2]);
			strcpy(finname, argv[3]);
		}		

		printf("\tEnter the output file name: ");
		scanf("%s", foutname);
	}
	else{
		strcpy(com, argv[1]);
		strcpy(arcname, argv[2]);
		strcpy(finname, argv[3]);
		strcpy(foutname, argv[4]);
	}

	arc = fopen(arcname, "w+b");
	fin = fopen(finname, "rb");
	fout = fopen(foutname, "w+b");

	Tree *t = (Tree*)malloc(sizeof(Tree));
	double fin_size = 0, fout_size = 0, arc_size = 0;
	for (int i = 0; com[i]; i++){
		fseek(fin, 0, SEEK_SET);
		fseek(fout, 0, SEEK_SET);
		fseek(arc, 0, SEEK_SET);
		if (com[i] == '-')
			continue;
		if (com[i] == 'a'){
			t = encode(arc, fin, t);
			fseek(fin, 0, SEEK_SET);
			fin_size = count_size(fin);
		}
		else if (com[i] == 'x'){
			decode(arc, fout, t, fin_size);
		}
		else if (com[i] == 'l'){
			double k;
			fin_size = count_size(fin);
			arc_size = count_size(arc);
			fout_size = count_size(fout);
			k = ((fin_size - arc_size) / fin_size) * 100;
			printf("\n\tInput file: %s\n", finname);
			printf("\tSize of input file: %.0lf Bytes\n", fin_size);
			printf("\tOutput file: %s\n", foutname);
			printf("\tSize of output file: %.0lf Bytes\n", fout_size);
			printf("\tArchived file: %s\n", arcname);
			printf("\tSize of archived file: %.0lf Bytes\n", arc_size);
			printf("\tCompression percentage: %.2lf%\n", k);
		}
	}

	free_tree(t);
	fclose(fin);
	fclose(fout);
	fclose(arc);
	return 0;
}