/*
Brayden Klemens
1000487
11/05/2018
Assignment 3
*/

#ifndef Q1_H
#define Q1_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct node{
	char *data;
	float value;
	struct node *left;
	struct node *right;
} Node;

typedef struct stack{
	struct node *node;
	struct stack *next;
}Stack;

//tree building functions
Node *buildTree(char *buffer);

Node *newNode(char *data);

Node *newFNode(char *data);

void addChildren(Node *parent, Node *left, Node *right);

Stack *getRoot(Stack *stack);

void inOrder(Node *root);

void preOrder(Node *root);

void postOrder(Node *root);

void update(Node *root);

void findVar(Node *root, char *var, float value);

float calculate(Node *root);

void display(Node *root);

//stack functions
Stack *push(Stack *stack, Node *node);

Stack *pop(Stack *stack);

Node *getTopNode(Stack *stack);

#endif






