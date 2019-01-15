/*
Brayden Klemens
1000487
October 15, 2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct stack{

	float input;
	struct stack *next;
	
}Node;

/*prototypes*/
Node * push(Node *stack, float input);

Node * pop(Node *stack);

float getTopNode(Node *stack);

float calculate(Node *stack, char *input);


int main(int argc, char* argv[]){

	/*vars*/
	char *input;
	float result = 0;

	/*malloc for size of string and copy input into it*/
	input = malloc(sizeof(char)*200);
	strcpy(input, argv[1]);

	/*create a stack with space malloced then initialize*/
	Node *stack;
	stack = malloc(sizeof(Node));
	stack = NULL;

	/*calculate the result*/
	result = calculate(stack, input);

	/*display result*/
	printf("result = %.2f\n", result);

	/*remove the result from the stack*/
	stack = pop(stack);

	return 0;
}

/*pushes new node into the stack, return the updated stack*/
Node * push(Node *stack, float input){

	/*initalize temp node to be pushed*/
	Node *temp = malloc(sizeof(Node));
	temp->next = NULL;
	temp->input = input;

	/*
	- if stack is empty set the head to the temp
	- other wise push
	*/
	if(stack == NULL){
		stack = temp;
	}else{
		temp->next = stack;
		stack = temp;
	}
	return stack;
}

/*remove the head node from the stack*/
Node * pop(Node *stack){

	/*only pop if nodes exist in it*/
	if(stack != NULL){
		/*temp = first element then free it and return stack without*/
		Node *temp = malloc(sizeof(Node));
		temp = stack;
		stack = stack->next;
		free(temp);
		return stack;
	}
	return stack;
}


float getTopNode(Node *stack){
	/*get value from node at top of stack*/
	if(stack != NULL){
		return stack->input;
	}
	return 0; 
}

float calculate(Node *stack, char *input){

	/*vars*/
	char element;
	float left = 0;
	float right = 0;
	float result = 0;

	/*go through each char in the input*/
	for(int i = 0; i < strlen(input); i++){

		/*get each char*/
		element = input[i];

		/*if the element is a digit, push onto the stack as an int*/
		if(isdigit(element)){
			stack = push(stack,(atoi(&element)));

		/*
		- goes through each case of possible operations
		- since the digits are pushed, the right (second) digit is at the top of the stack first
		- then pop off the right digit so the left digit is on top
		- get the left digit, then pop it off the stack as well
		- now that I have the values of each digit I can perform the operation on them
		- then store the result of the operation back in the stack so that it can be used in further operations
		*/
		}else if(element == '+'){

			right = getTopNode(stack);
			stack = pop(stack);
			left = getTopNode(stack);
			stack = pop(stack);
			result = left + right;
			stack = push(stack, result);

		}else if(element == '-'){
			right = getTopNode(stack);
			stack = pop(stack);
			left = getTopNode(stack);
			stack = pop(stack);
			result = left - right;
			stack = push(stack, result);

		}else if(element == '*'){
			right = getTopNode(stack);
			stack = pop(stack);
			left = getTopNode(stack);
			stack = pop(stack);
			result = left * right;
			stack = push(stack, result);

		}else if(element == '/'){
			right = getTopNode(stack);
			stack = pop(stack);
			left = getTopNode(stack);
			stack = pop(stack);
			result = left / right;
			stack = push(stack, result);

		}else{
			/*exit program upon finding an invalid operation*/
			printf("Invalid input");
			exit(0);
		}
	}

	/*at the end of the operation, the stack will have the result pushed to it only
	therefore, I just get the value from the top node for the result*/
	result = getTopNode(stack);

	return result;
}








