#pragma once
#ifndef ADDLIB_H
#define ADDLIB_H

#include <stdio.h>

int compare(const void *p1, const void *p2);
double count_size(FILE *f);
int count_frequency(FILE *f, int *arr);

#endif