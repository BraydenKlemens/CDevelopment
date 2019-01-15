/*
Brayden Klemens
1000487
11/05/2018
Assignment 3
*/

#include "q1.h"

int main(int argc, char *argv[]){

	//vars
	Node *root;
	int option = 0;
	bool repeat = false;
	char *buffer = malloc(sizeof(char)*100);
	strcpy(buffer, argv[1]);
	

	//get the root of the tree
	root = buildTree(buffer);
	
	while(repeat == false){

		printf("1. Display\n2. Preorder\n3. Inorder\n4. Postorder\n5. Update\n6. Calculate\n7. Exit\n");

		scanf("%d", &option);

		switch(option){

			case 1:
				display(root);
			break;
			case 2:
				preOrder(root);
				printf("\n");
			break;
			case 3:
				inOrder(root);
				printf("\n");
			break;
			case 4:
				postOrder(root);
				printf("\n");
			break;
			case 5:
				update(root);
			break;
			case 6:
				printf("result = %.2f\n",calculate(root));
			break;
			case 7:
				repeat = true;
				printf("Exiting program...\n");
				exit(0);
			break;
			default:
				printf("Invalid user option! Choose an option.\n");
			break;
		}
	}

	return 0;

}

//display the internal nodes with their left and right children
void display(Node *root){

	//base case
	if(root == NULL){
		return;
	}

	/*
	- if it is an internal node, print right and left children
	- check if it is a variable then print the varible with its value
	- otherwise print the parent with its children and floating point values
	*/
	if(strcmp(root->data, "+") == 0 || strcmp(root->data, "-") == 0 || strcmp(root->data, "*") == 0 || strcmp(root->data, "/") == 0){
			if(root->right->data[0] == 'x' && root->left->data[0] == 'x'){
				printf("Parent: %s, Left: %s: %.1f, Right: %s: %.1f\n", root->data, root->left->data, root->left->value, root->right->data, root->right->value);
			}else if(root->right->data[0] == 'x'){
				printf("Parent: %s, Left: %s, Right: %s: %.1f\n", root->data, root->left->data, root->right->data, root->right->value);
			}else if( root->left->data[0] == 'x'){
				printf("Parent: %s, Left: %s: %.1f, Right: %s\n", root->data, root->left->data, root->left->value, root->right->data);
			}else{
				printf("Parent: %s, Left: %s, Right: %s\n", root->data, root->left->data, root->right->data);
			}
	}
	//traverse left and right
	display(root->left);
	display(root->right);
}

//calculate the expression
float calculate(Node *root){

	//vars
	float x, y;
	
	//return the value if the node is a leaf
	if(root->right == NULL && root->left == NULL){
		return root->value;
	}else{
		//recursive until finding a leaf and return the value
		x = calculate(root->left);
		y = calculate(root->right);

		//do operation on x and y depending on the operator stored at the parent node
		if(strcmp(root->data,"+") == 0){
			return x + y;
		}else if(strcmp(root->data,"-") == 0){
			return x - y;
		}else if(strcmp(root->data, "*") == 0){
			return x * y;
		}else if(strcmp(root->data, "/") == 0){
			if(y == 0){
				printf("Divide by zero not possible! (return 0) (exit)\n");
				return 0;
			}else{
				return x / y;
			}
		}else{
			printf("Could not find operation\n");
			return 0;
		}
	}
}

//get user input makes a call to findVar to do the work
void update(Node *root){
	char *var = malloc(sizeof(char)*10);
	float value = 0;
	printf("Enter the variable to change: ");
	scanf("%s", var);
	printf("Enter the new value: ");
	scanf("%f", &value);
	findVar(root, var, value);
}

//traverse tree pre order to find the matching varibale name then update its value
void findVar(Node *root, char *var, float value){
	if(root == NULL){ 
		return;
	}
	findVar(root->left, var, value);

	//if not found the variable name is not updated and everything remains the same
	if(strcmp(root->data,var) == 0){
		root->value = value;
	}

	findVar(root->right, var, value);
}

//traverse tree in order
void inOrder(Node *root){
	
	/*
	- print '(' before traversing left subtree if its an internal node
	- print data 
	- print ')' before traversing right subtree if its an internal node
	*/
	if(root->right != NULL || root->left != NULL){
		printf("(");
		inOrder(root->left);
	}
	printf("%s",root->data);

	if(root->right != NULL || root->left != NULL){
		inOrder(root->right);
		printf(")");
	}
}

//traverse tree pre order
void preOrder(Node *root){
	if(root == NULL){ 
		return;
	}
	printf("%s ", root->data);
	preOrder(root->left);
	preOrder(root->right);
}

//traverse tree post order
void postOrder(Node *root){
	if(root == NULL){ 
		return;
	}
	postOrder(root->left);
	postOrder(root->right);
	printf("%s ", root->data);
}

//returns the root of the tree
Node *buildTree(char *buffer){

	//vars
	char *data = malloc(sizeof(char)*5);
	char temp;
	int count = 0;
	Node *node;

	Stack *stack;
	Node *root;
	stack = malloc(sizeof(Stack));
	stack = NULL;


	for(int i = 0; i < strlen(buffer); i++){

		//get a temp varible with one char
		temp = buffer[i];

		/*
		- this means that a nested parenthesis pair with 3 components ended
		- add the children nodes to the internal node and push back to stack
		*/
		if(temp == ')'){
			stack = getRoot(stack);
		}

		//make a new node for operators and push to stack
		if(temp == '+' || temp == '-' || temp == '*' || temp == '/'){
			data[0] = temp;
			data[1] = '\0';
			node = newNode(data);
			stack = push(stack, node);
			strcpy(data,"");
		}

		//make a new node for leaf variables and push to stack
		if(temp == 'x'){
			data[0] = temp;
			data[1] = buffer[i + 1];
			data[2] = '\0';
			node = newNode(data);
			stack = push(stack, node);
			strcpy(data, "");
			i = i + 1;
		}

		//make a new node for a floating point variable 
		if(isdigit(temp) || temp == '.'){
			
			if(strlen(data) < 4){
				data[count] = temp;
				data[count + 1] = '\0';
				count++;
			}

			/*
			printf("%s ", data);
			printf("length: %lu\n",strlen(data));
			*/

			if(strlen(data) >= 4){
				node = newFNode(data);
				stack = push(stack, node);
				strcpy(data,"");
				count = 0;
			}
		}
	}

	/*
	- last parethesis will make the final root node
	- get that node and return it
	*/
	root = getTopNode(stack);
	stack = pop(stack);

	return root;
}

//add children to an internal node from stack
Stack *getRoot(Stack *stack){

	/*
	- algorithm to add children
	- get right parent left and add children to parent
	- push back to stack for later addiions
	*/
	Node *left, *right, *parent;

	right = getTopNode(stack);
	stack = pop(stack);
	parent = getTopNode(stack);
	stack = pop(stack);
	left = getTopNode(stack);
	stack = pop(stack);
	addChildren(parent, left, right);
	stack = push(stack, parent);

	return stack;
}

//creates new node for vars and operators
Node *newNode(char *data){

	Node *newNode = malloc(sizeof(Node));
	newNode->data = malloc(strlen(data) + 1);
	strcpy(newNode->data, data);
	newNode->value = 0;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

//creates new node for floating values
Node *newFNode(char *data){

	Node *newNode = malloc(sizeof(Node));
	newNode->data = malloc(strlen(data) + 1);
	strcpy(newNode->data, data);
	newNode->value = atof(data);
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

//simplifier function to add children
void addChildren(Node *parent, Node *left, Node *right){

	parent->left = left;
	parent->right = right;
}

/*pushes new node into the stack, return the updated stack*/
Stack *push(Stack *stack, Node *node){

	/*initalize temp node to be pushed*/
	Stack *temp = malloc(sizeof(Stack));
	temp->next = NULL;
	temp->node = malloc(sizeof(Node));
	temp->node = node;

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
Stack *pop(Stack *stack){

	/*only pop if nodes exist in it*/
	if(stack != NULL){
		/*temp = first element then free it and return stack without*/
		Stack *temp = malloc(sizeof(Stack));
		temp = stack;
		stack = stack->next;
		free(temp);
		return stack;
	}
	return stack;
}

/*get the top node without removing it from stack*/
Node *getTopNode(Stack *stack){

	Node *tempNode;
	tempNode = malloc(sizeof(Node));

	if(stack != NULL){
		return stack->node;
	}
	return tempNode;
}









