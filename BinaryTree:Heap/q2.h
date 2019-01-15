/*
Brayden Klemens
1000487
11/05/2018
Assignment 3
*/

#ifndef Q2_H
#define Q2_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//sorting algorithm
void downHeap(int nums[20][10]);

//display the sorted heap
void display(int nums[20][10]);

//swap all data with child 1
void swapC1(int nums[20][10], int i);

//swap all data with child 2 
void swapC2(int nums[20][10], int i);

#endif

