#pragma once
#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdio.h>
#include "tree.h"

Tree *build_tree(FILE *f, int *n);
void create_code(Tree *t, char **table, int n);
Tree *encode(FILE *arc, FILE *f, Tree *t);
void decode(FILE *arc, FILE *f, Tree *t, int f_size);

#endif