#include <stdio.h>
#include "tree.h"
#include "addlib.h"

Tree *build_tree(FILE *f, int *n){
	int *arr = (int *)malloc(sizeof(int)* 256);
	int j = 0, gen_freq, count = 0;
	count_frequency(f, arr);
	Tree **node = (Tree**)malloc(sizeof(Tree*)*256);

	for (int i = 0; i < 256; i++){
		if (arr[i]>0){
			node[count++] = create_node((char)(i), arr[i], NULL, NULL);
			qsort(node, count, sizeof(Tree*), (int(*)(const void*, const void*)) compare);
		}
	}
	
	while (count != 1){
		Tree *left = node[--count], *right = node[--count];
		gen_freq = left->freq + right->freq;
		Tree *t = create_node('#', gen_freq, left, right);
		node[count] = t;
		count++;
		qsort(node, count, sizeof(Tree*), (int(*)(const void*, const void*)) compare);
	}

	(*n) = gen_freq;
	return node[0];
}

void create_code(Tree *t, char **table, int n){
	if (t->left){
		if (n == t->freq)
			strcpy(t->left->code, "0");
		else{
			strcpy(t->left->code, t->code);
			strcat(t->left->code, "0");
		}
		create_code(t->left, table, n);
	}
	if (t->right){
		if (n == t->freq)
			strcpy(t->right->code, "1");
		else{
			strcpy(t->right->code, t->code);
			strcat(t->right->code, "1");
		}
		create_code(t->right, table, n);
	}
	else{
		table[t->symb] = (char*)malloc(sizeof(char)* 256);
		strcpy(table[t->symb], t->code);
	}
}

Tree *encode(FILE *arc, FILE *f, Tree *t){
	char **table = (char**)malloc(sizeof(char*)* 256);
	unsigned char symb, bit = 0;
	int k = 7, flag = 0, n = 0;

	t = build_tree(f, &n);
	create_code(t, table, n);
	fseek(f, 0, SEEK_SET);
	fread(&symb, sizeof(unsigned char), 1, f);
	while (!feof(f)){
		for (int i = 0; table[symb][i]; i++){
			if (k == -1){
				k = 7;
				fwrite(&bit, sizeof(unsigned char), 1, arc);
				bit = 0;
			}
			bit = bit | ((table[symb][i] - '0') << k);
			k--;
		}
		fread(&symb, sizeof(unsigned char), 1, f);
	}
	if (k != -1)
		fwrite(&bit, sizeof(unsigned char), 1, arc);
	for (int i = 0; i < 256; i++){
		if (table[i]){
			printf("%d: ", i);
			for (int j = 0; table[i][j]; j++){
				printf("%c", table[i][j]);
			}
			printf("\n\0");
		}
	}
	return t;
}

void decode(FILE *arc, FILE *f, Tree *t, int f_size){
	Tree *p = t;
	char byte, tmp = '\0';
	int k = 7;
	fread(&byte, sizeof(unsigned char), 1, arc);
	while (!feof(arc)){
		int b = (byte & (1 << k)) >> k;
		if (b == 0)
			p = p->left;
		else if (b == 1)
			p = p->right;
		k--;
		if (!p->left && !p->right){
			fwrite(&p->symb, sizeof(unsigned char), 1, f);
			p = t;
			f_size--;
		}
		if (k == -1){
			k = 7;
			fread(&byte, sizeof(unsigned char), 1, arc);
		}
		if (f_size == 0)
			break;
	}
	fwrite(&tmp, sizeof(unsigned char), 1, f);
}