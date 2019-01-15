/*
Brayden Klemens
1000487
11/15/2018
Assignment 4
*/

#include "avltree.h"


int main(int argc, char *argv[]){

	//variables
	int option = 0;
	int height = 0; 
	int count = 0; 
	int size = 0;
	int frequency = 0;
	char *string = malloc(sizeof(char)*10);
	bool repeat =  false;
	bool init = false;
	Node *root = malloc(sizeof(Node));
	Node *search = malloc(sizeof(Node));
	Node *add = malloc(sizeof(Node));

	while(repeat == false){

		printf("1. Initialization\n2. Find\n3. Insert\n4. Remove\n5. Check Height, Size, and Total Count\n");
		printf("6. Find All (above a given frequency)\n7. Exit\n");
		printf("avl/> ");

		scanf("%d", &option);

		switch(option){

			case 1:
				root = buildTree(argv[1]);
				init = true;
				addBalanceFactor(root);
			break;
			case 2:
			if(init){
				printf("find key: ");
				scanf("%s", string);
				search = findKey(root, string);
				if(strcmp(search->data, "NULL") != 0){
					printf("key: %s, frequency: %d\n\n", search->data, search->count);
				}
			}else{
				printf("Initialize Tree!\n\n");
			}
			break;
			case 3:
			if(init){
				printf("insert key: ");
				scanf("%s", string);
				add = newNode(string);
				insert(&root, add);
				//balance tree here
				search = findKey(root, string);
				printf("key: %s, frequency: %d\n\n", search->data, search->count);
			}else{
				printf("Initialize Tree!\n\n");
			}
			break;
			case 4:
			if(init){
				printf("remove key: ");
				scanf("%s", string);
				search = findKey(root, string);
				if(strcmp(search->data, "NULL") != 0){
					deleteNode(&root, string);
					addBalanceFactor(root);
					search = findKey(root, string);
					if(strcmp(search->data, "NULL") != 0){
						printf("key: %s, frequency: %d\n\n", search->data, search->count);
					}
				}
			}else{
				printf("Initialize Tree!\n\n");
			}
			break;
			case 5:
			if(init){
				size = getSize(root);
				count = getTotalCount(root);
				height = getHeight(root);
				printf("Height: %d, Size: %d Count: %d\n\n", height, size, count);
			}else{
				printf("Initialize Tree!\n\n");
			}
			break;
			case 6:
			if(init){
				printf("frequency: ");
				scanf("%d", &frequency);
				findAll(root, frequency);
				printf("\n");
			}else{
				printf("Initialize Tree!\n\n");
			}
			break;
			case 7:
				repeat = true;
				printf("Exiting program...\n\n");
				exit(0);
			break;
			default:
				printf("Invalid user option! Choose an option.\n\n");
			break;
		}
	}

	return 0;
}

//builds the AVL tree and returns the root node
Node *buildTree(char *file){

	//vars for file reading
	Node *node = malloc(sizeof(Node));
	char *buffer = malloc(sizeof(char)*5000);
	char *token = malloc(sizeof(char)*100);
	Node *root = NULL;

	//Open file for reading
	FILE *fp;
	fp = fopen(file, "r");

	//check if file opened
	if(fp != NULL) {
		printf("\nFile read success...\n\n");
	}else{
		printf("Failed to open file...\n\n");
		exit(0);
	}

	//read data from file create nodes and insert into tree
	while (fgets(buffer,5000,fp)){

		token = strtok(buffer," ");

		if(token != NULL && strcmp(token,"") != 0){
			node = newNode(token);
			root = insert(&root, node);
		}

		token = strtok(NULL, " ");

		while(token != NULL && strcmp(token,"") != 0){
			node = newNode(token);
			root = insert(&root, node);
			token = strtok(NULL, " ");
		}				
	}
		
	fclose(fp);	

	return root;
}

//inserts a node into the tree if the key doesnt already exist
Node *insert(Node **root, Node *add){

	//vars
	Node *base;
	base = *root;

	//increase te count if it already exists
	if(base != NULL && strcmp(add->data, base->data) == 0){
		(*root)->count += 1;
		return *root;
	}

	//check if the root is null
	if(base == NULL){
		*root = add;
		return *root;
	}else{
		//move through tree to find where it needs to be inserted in order
		if(add->value < base->value){
			(*root)->left = insert(&(base->left), add);
		}else{
			(*root)->right = insert(&(base->right), add);
		}
	}

	return balanceTree(*root);
}

//searches for the node to be deleted and removes it
void deleteNode(Node **root, char *delete){

	if(*root == NULL){

		return;

	}else{

		if(strcmp((*root)->data, delete) == 0){

			if((*root)->count > 1){
				(*root)->count -= 1;
			}else{

				if((*root)->left == NULL && (*root)->right != NULL){

					Node *temp = (*root)->right;
					(*root)->right = NULL;
					(*root) = temp;

				}else if((*root)->left != NULL && (*root)->right == NULL){
					
					Node *temp = (*root)->left;
					(*root)->left = NULL;
					(*root) = temp;

				}else if((*root)->left == NULL && (*root)->right == NULL){
					(*root) = NULL;
				}else{
					
					Node *temp = inOrder((*root)->right);
					deleteNode(&((*root)->right), temp->data);
					
					Node *right = (*root)->right;
					temp->right = right;
					Node *left = (*root)->left;
					temp->left = left;

					*root = temp;
				}
			}
		}else{
			deleteNode(&((*root)->left),delete);
			deleteNode(&((*root)->right),delete);
		}
	}
}

//finds a key in the tree and returns the node with that data, if it doesnt find, then it inserts it
Node *findKey(Node *root, char *data){

	//create a null node to return
	Node *nullNode = malloc(sizeof(Node));
	nullNode->data = malloc(sizeof(char)*10);
	strcpy(nullNode->data, "NULL");
	

	//create a temp node of the data being passed for comparison
	Node *temp = malloc(sizeof(Node));
	temp = newNode(data);

	/*
	- if external node return a null node nothing found
	- if searched key is less than current, then recursive to left branch
	- if searched key is greater than current, recursive right branch of node
	- if found return the node
	*/
	if(root == NULL){
		printf("no_such_key\n\n");
		return nullNode;
	}
	if(temp->value < root->value){
		return findKey((root->left), data);
	}else if(temp->value > root->value){
		return findKey((root->right), data);
	}else {
		return root;
	}
}

//creates a new node
Node *newNode(char *data){

	//var
	char *tempVal = malloc(sizeof(char)*100);
	int length = 0;
	int j = 0;

	//set data
	Node *newNode = malloc(sizeof(Node));
	newNode->data = malloc(sizeof(char)*100);
	strcpy(newNode->data, data);
	newNode->balance = 0;
	newNode->count = 1;

	//remove new line read in from file
	if(newNode->data[strlen(newNode->data) - 1] == '\n'){
		newNode->data[strlen(newNode->data) - 1] = '\0';
	}

	//make temp string of value, get int value from temp string
	length = strlen(data);

	for(int i = 3; i < length; i++){
		tempVal[j] = data[i];
		j++;
	}

	//fill last character with null value
	tempVal[strlen(tempVal)] = '\0';

	newNode->value = atoi(tempVal);

	//set left and right null
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

//adds the correct baalnce for each node mainly used for testing
void addBalanceFactor(Node *root){

	//return if root is null
	if(root == NULL){
		return;
	}else{

		//subtract left subtree from right subtree then assign to the current node
		if(root->left != NULL || root->right != NULL){
			
			int left = getHeight(root->left);
			int right = getHeight(root->right);

			root->balance = (left - right);
		
			//move through all nodes
			addBalanceFactor(root->left);
			addBalanceFactor(root->right);
		}
	}
}

//gets the size of the tree
int getSize(Node *root){

	//base case 
	if(root == NULL){
		return 0;
	}

	//adds each node on left and right subtrees
	return getSize(root->left) + getSize(root->right) + 1;
}

//adds the count of each node and returns the total
int getTotalCount(Node *root){

	//base case 
	if(root == NULL){
		return 0;
	}

	//adds each node on left and right subtrees
	return getTotalCount(root->left) + getTotalCount(root->right) + root->count;
}

//returns the longest path in the tree
int getHeight(Node *root){

	//base case
	if(root == NULL){
		return 0;
	}else{
		//recursivly checks left and right subtree and returns which side is greater
		//eventually comparing the total heigh of the left subtree and right subtree of the root
		//returns greater value + 1 to get height
		int left = getHeight(root->left);
		int right = getHeight(root->right);

		if(left > right){
			return left + 1;
		}else{
			return right + 1;
		}
	}
}

//prints all nodes with a given frequency above the passed in integer 
void findAll(Node *root, int frequency){
		
	//uses a in order traverse
	if(root->left != NULL){
		findAll(root->left, frequency);
	}

	//checks if the current nodes frequency is greater or equal, if so print it
	if(root->count >= frequency){
		printf("key: %s, frequency: %d\n", root->data, root->count);
	}
	
	if(root->right != NULL){
		findAll(root->right, frequency);
	}
}

//used to find the inOrder next node on right subtree for deleteing
Node *inOrder(Node *root){

	Node *current = root;

	while(current->left != NULL){
		current = current->left;
	}

	return current;
}

//rotate right and give new strcuture balance factors
Node *rightRotate(Node *root){ 

    Node *x = root->left; 
    Node *z = x->right; 
  
    x->right = root; 
    root->left = z; 

    addBalanceFactor(root);
    addBalanceFactor(x);
    
    return x; 
} 

//rotate left and give new strcuture balance factors
Node *leftRotate(Node *root){ 

    Node *y = root->right; 
    Node *z = y->left; 
  
    y->left = root; 
    root->right = z; 

    addBalanceFactor(root);
    addBalanceFactor(y);
  
    return y; 
}

//balance upon insert function
Node *balanceTree(Node *root){

	/*
	- check to see if th right and left subtree are balanced
	- single rotate on left child
	- single right rotate on node that is unbalanced
	*/

	if(getHeight(root->left) - getHeight(root->right) == 2){
        if(getHeight(root->left->right) > getHeight(root->left->left)){
            root->left = leftRotate(root->left);
        }
        return rightRotate(root);

    }
    if(getHeight(root->right) - getHeight(root->left) == 2){
        if(getHeight(root->right->left) > getHeight(root->right->right)){
            root->right = rightRotate(root->right); 
        }
        return leftRotate(root);
    }

    return root;
}








