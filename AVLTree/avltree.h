/*
Brayden Klemens
1000487
11/15/2018
Assignment 3
*/

#ifndef AVLTREE_H
#define AVLTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct node{
	char *data;
	int value;
	int count;
	int balance;
	struct node *left;
	struct node *right;
} Node;


//Prototypes

Node *insert(Node **root, Node *add);

void deleteNode(Node **root, char *delete);

Node *findKey(Node *root, char *data);

Node *buildTree(char *file);

int getHeight(Node *root);

Node *newNode(char *data);

int getTotalCount(Node *root);

int getSize(Node *root);

void findAll(Node *root, int frequency);

void addBalanceFactor(Node *root);

Node *inOrder(Node *root);

Node *rightRotate(Node *y);

Node *leftRotate(Node *x);

Node *balanceTree(Node *root);

#endif 


