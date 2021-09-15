#pragma once
#ifndef TREE_H
#define TREE_H

typedef struct Tree{
	int freq;
	unsigned char symb;
	char code[256];
	struct Tree *left;
	struct Tree *right;
}Tree;
Tree *create_node(unsigned char c, int fr, Tree *left_son, Tree *right_son);
void free_tree(Tree *t);

#endif