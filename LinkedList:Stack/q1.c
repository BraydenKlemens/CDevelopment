/*
Brayden Klemens
1000487
October 15, 2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*struct for car data*/
typedef struct car_struct {

	int mileage;
	int returnDate;
	char plate[10];

}Car;

/*struct for list of car structs*/
typedef struct list_struct {

	Car data;
	struct list_struct *next;

}Node;

/*prototypes*/

Node removeNode(Node **head, char plate[8]);

Node popFirstNode(Node **head);

Car newCar(char plate[8], int mileage, int returnDate);

void insertRepair(Node **head, Car toAdd);

void insertAvailable(Node **head, Car toAdd);

void insertRented(Node **head, Car toAdd);

void printLinkedList(Node **head);

void transferNode(Node **get, Node **receive, char plate[8], int mileage, int code);

void writeToFile(Node **availableListHead, Node **rentedListHead,Node  **repairListHead);

void readFromFile(Node **availableListHead, Node **rentedListHead,Node  **repairListHead);

int main(){

	/*variables*/
	int code = 0; 
	char plate[20];
	int mileage = 0;
	int returnDate = 0;
	bool repeat = false;

	/*three lists that are maintained*/
	Node *availableListHead = NULL;
	Node *rentedListHead = NULL;
	Node *repairListHead = NULL;

	/*used for removing cars from rent list*/
	Node rent;

	/*Fill Linked lists with data from text file*/
	readFromFile(&availableListHead,&rentedListHead,&repairListHead);

	/*allows continueous transaction until exit*/
	while(repeat == false){

		printf("Enter a transaction code to perform the coresponsing function:\n");
		printf("1. add a new car to the available for rent list,\n");
		printf("2. add a returned car to the available-for-rent list,\n");
		printf("3. add a returned car to the repair list,\n");
		printf("4. transfer a car from the repair list to the available-for-rent list,\n");
		printf("5. rent the first available car,\n");
		printf("6. print all the lists,\n");
		printf("7. quit.\n");

		scanf("%d", &code);

		/*run transactions based on the useser input code 1-7*/
		switch(code){
			case 1:
				/*prompt and get input*/
				printf("Enter a valid plate number: \n");
				scanf("%s", plate);
				printf("Enter a mileage: \n");
				scanf("%d", &mileage);

				/*make sure the plate is a real plate then insert into list*/
				if(strlen(plate) <= 7){
					insertAvailable(&availableListHead, newCar(plate, mileage, 0));
					printf("adding new car to available for rent list...\n");
				}else{
					printf("invalid plate number\n");
				}
				break;

			case 2:
				/*prompt and get input*/
				printf("Enter a plate Number: \n");
				scanf("%s", plate);
				printf("Enter a mileage: \n");
				scanf("%d", &mileage);

				/*make sure the plate is a real plate then transfer from rented to available*/
				if(strlen(plate) <= 7){
					transferNode(&rentedListHead, &availableListHead, plate, mileage, code);
				}else{
					printf("invalid plate number\n");
				}
				break;
			case 3:
				/*prompt and get input*/
				printf("Enter a plate Number: \n");
				scanf("%s", plate);
				printf("Enter a mileage: \n");
				scanf("%d", &mileage);

				/*make sure the plate is a real plate then transfer from rented to repair*/
				if(strlen(plate) <= 7){
					transferNode(&rentedListHead, &repairListHead, plate, mileage, code);
				}else{
					printf("invalid plate number\n");
				}
				break;
			case 4:
				/*prompt and get input*/
				printf("Enter a plate Number: \n");
				scanf("%s", plate);

				/*make sure the plate is a real plate then transfer from repair to rented*/
				if(strlen(plate) <= 7){
					transferNode(&repairListHead, &availableListHead, plate, mileage, code);
				}else{
					printf("invalid plate number\n");
				}
				break;
			case 5:

				/*prompt and get return date for renting*/
				printf("Enter an expected return date yyyymmdd: \n");
				scanf("%d", &returnDate);

				/*pop first available car from available list, set a returnDate*/
				rent = popFirstNode(&availableListHead);
				rent.data.returnDate = returnDate;

				/*if not default available node, insert into rented*/
				if(strcmp(rent.data.plate,"DEFAULT") != 0){
					insertRented(&rentedListHead, rent.data);
					printf("renting the first available car...\n");
				}else{
					printf("Could not find car from available car list!\n");
				}
				break;
			case 6:
				/*print all lists*/
				printf("Available for rent list: \n");
				printLinkedList(&availableListHead);

				printf("Rented list: \n");
				printLinkedList(&rentedListHead);

				printf("In-repair list: \n");
				printLinkedList(&repairListHead);
				break;
			case 7:
				/*save data in file and exit program*/
				writeToFile(&availableListHead,&rentedListHead,&repairListHead);
				repeat = true;
				printf("Exiting program...\n");
				exit(0);
				break;
			default:
				/*case in which an invalid code was entered by user*/
				printf("Invalid transaction code!\n");
				break;
		}
	}
	return 0;
}

/*writes the data in the linked lists to a text file*/
void writeToFile(Node **availableListHead, Node **rentedListHead,Node  **repairListHead){

	FILE *fp;
	Node *curr;

	/*set the current node to the beginning of available list */
	curr = *availableListHead;

	fp =  fopen("data.txt", "w");

	/*
	- iterate, print the data of each node on a single line in the text file
	- if we reach the end of the list print a * on its own line to act as a delimiter
	- * indicates end of a list and beginning of a new list in the file
	*/
	while(curr != NULL){
		if(curr->next == NULL){
			fprintf(fp,"%d,%d,%s\n*\n", curr->data.mileage, curr->data.returnDate, curr->data.plate);
		}else{
			fprintf(fp,"%d,%d,%s\n", curr->data.mileage, curr->data.returnDate, curr->data.plate);
		}
		curr = curr->next;
	}

	/*same thing for rented list*/
	curr = *rentedListHead;

	while(curr != NULL){
		if(curr->next == NULL){
			fprintf(fp,"%d,%d,%s\n*\n", curr->data.mileage, curr->data.returnDate, curr->data.plate);
		}else{
			fprintf(fp,"%d,%d,%s\n", curr->data.mileage, curr->data.returnDate, curr->data.plate);
		}
		curr = curr->next;
	}

	/*same thing for repair list*/
	curr = *repairListHead;

	while(curr != NULL){
		if(curr->next == NULL){
			fprintf(fp,"%d,%d,%s\n*\n", curr->data.mileage, curr->data.returnDate, curr->data.plate);
		}else{
			fprintf(fp,"%d,%d,%s\n", curr->data.mileage, curr->data.returnDate, curr->data.plate);
		}
		curr = curr->next;
	}

	fclose(fp);

}

void readFromFile(Node **availableListHead, Node **rentedListHead,Node  **repairListHead){

	FILE *fp;
	Car car;

	char buffer[200];
	char *element;
	int listCounter = 0;
	
	fp = fopen("data.txt", "r");

	/*get first line in text file*/
	while(fgets(buffer, 200, fp) != NULL){
		/*used to keep track of which list to add to*/
		if(listCounter == 0){
			/*
			- if not the end of the list then create tokens from buffer using , as delimiter
			- each token is then used to store data in a car struct
			- remove newLine characters from the plate data before copying it into the car struct
			- insert the car onto the current list
			- same functionality of the next 2 code blocks
			*/
			if(buffer[0] != '*'){
				element = strtok(buffer, ",");
				car.mileage = atoi(element);
				element = strtok(NULL, ",");
				car.returnDate = atoi(element);
				element = strtok(NULL, ",");
				element[strlen(element) - 1] = '\0';
				strcpy(car.plate, element);
			
				insertAvailable(availableListHead, car);
					
			}else{
				/*if buffer finds a star, proceed to reading data into the next list*/
				listCounter++;
			}
		}else if(listCounter == 1){
			if(buffer[0] != '*'){

				element = strtok(buffer, ",");
				car.mileage = atoi(element);
				element = strtok(NULL, ",");
				car.returnDate = atoi(element);
				element = strtok(NULL, ",");
				element[strlen(element) - 1] = '\0';
				strcpy(car.plate, element);

				insertRented(rentedListHead, car);
					
			}else{
				listCounter++;
			}
		}else if(listCounter == 2){
			if(buffer[0] != '*'){

				element = strtok(buffer, ",");
				car.mileage = atoi(element);
				element = strtok(NULL, ",");
				car.returnDate = atoi(element);
				element = strtok(NULL, ",");
				element[strlen(element) - 1] = '\0';
				strcpy(car.plate, element);

				insertRepair(repairListHead, car);
					
			}else{
				listCounter++;
			}
		}
	}

	fclose(fp);
}

/*removes the head node from the passed list*/
Node popFirstNode(Node **head){

	/*variables set current to head node*/
	Node *curr, *old;
	Node *def = malloc(sizeof(Node));
	curr = *head; 

	/*create default node*/
	def->data.mileage = 0;
	def->data.returnDate = 0;
	strcpy(def->data.plate,"DEFAULT");
	def->next = NULL;

	/*
	- list doesnt exist return default node
	- otherwise pop first node and return
	*/
	if(*head == NULL){
		return *def;
	}else{
		old = curr;
		curr = (*head)->next;
		*head = curr;
		return *old;
	}
}

/*delete a node a re link the list */
Node removeNode(Node **head, char plate[8]){

	/*Variables*/
	Node *old , *curr;
	Node *def = malloc(sizeof(Node));
	curr = *head; 

	/*creat a default node*/
	def->data.mileage = 0;
	def->data.returnDate = 0;
	strcpy(def->data.plate,"DEFAULT");
	def->next = NULL;

	/*return default if list doesnt exist*/
	if(*head == NULL){
		return *def;
	}

	/*if the first node is the node were searching for remove it*/
	if(strcmp(plate, curr->data.plate) == 0){
		old = curr;
		curr = (*head)->next;
		*head = curr;
		return *old;
	} 

	/*loop through the list at next locations until finding the node with the correct plate number */
	while (curr->next != NULL && strcmp(plate, curr->next->data.plate) != 0){ 
		curr = curr->next;
	}

	/*
	- if the next exists, get the value of the removed node, relink list without it
	- if the next doesnt exit return a default node 
	*/
	if (curr->next){
		old = curr->next;
		curr->next = curr->next->next;
		return *old;
	}else{
		return *def;
	}
}


/* creates a new car to add to any list */
Car newCar(char plate[8], int mileage, int returnDate) {

	/*add car data*/
	Car car;
	strcpy(car.plate, plate);
	car.mileage = mileage;
	car.returnDate = returnDate;

	return car;
}


/* Adds a node to the front of a list*/
void insertRepair(Node **head, Car toAdd) {

	/*initialize temp node*/
	Node *temp = malloc(sizeof(Node));
	temp->data = toAdd;
	temp->next = NULL;

	if(*head == NULL){
		*head = temp;
	}else{
		temp->next = *head;
		*head = temp;
	}
}

/*least miles to most ordered insertion into  available list*/
void insertAvailable(Node **head, Car toAdd){

	Node *curr, *prev = NULL, *new;

	/*create new node and set current ro head*/
	new = malloc(sizeof(Node));
	new->data = toAdd;
	new->next = NULL;
	curr = *head;

	/*update nodes prev and current until find insertion location*/
	while(curr != NULL && toAdd.mileage > curr->data.mileage){
		prev = curr;
		curr = curr->next;
	}

	/*
	- if prev null remove head node
	- otherwise relink list in middle of 2 other nodes
	*/
	if(prev == NULL){
		new->next = *head;
		*head = new;
	}else{
		prev->next = new;
		new->next = curr;
	}
}

/*most recent to latest date insertion of rented cars*/
void insertRented(Node **head, Car toAdd){

	Node *curr, *prev = NULL, *new;
	/*create new node and set current to head*/
	new = malloc(sizeof(Node));
	new->data = toAdd;
	new->next = NULL;
	curr = *head;

	/*update nodes prev and current until find insertion location*/
	while(curr != NULL && toAdd.returnDate > curr->data.returnDate){
		prev = curr;
		curr = curr->next;
	}

	/*
	- if prev null remove head node
	- otherwise relink list in middle of 2 other nodes
	*/
	if(prev == NULL){
		new->next = *head;
		*head = new;
	}else{
		prev->next = new;
		new->next = curr;
	}
}

/* Prints out the data at each node of he Linked list*/
void printLinkedList(Node **head) {

	Node *current;
	current = *head;

	/*
	- list is null then prompt empty
	- else print car data at each node
	*/
	if(*head == NULL){
		printf("Empty!\n");
	}else{
		while(current != NULL){
		printf("Plate: %s, Mileage: %d, ReturnDate: %d\n", current->data.plate, current->data.mileage, current->data.returnDate);
		current = current->next;
		}
	}
}

/*transfer a node from one list to the other*/
void transferNode(Node **get, Node **receive, char plate[8], int mileage, int code){

	/*vars*/
	Node toAdd;
	float fee = 0;
	float feeDistance = 0;

	/*remove a node from a list and store in toAdd*/
	toAdd = removeNode(get, plate);

	/*all possible transfer cases based on transaction code*/
	switch(code){
		case 2:
		/*make sure toAdd is not a default node*/
		if(strcmp(toAdd.data.plate,"DEFAULT") != 0){
			if(mileage >= toAdd.data.mileage){
				/*only charge for distance traveled in case there was a prev mileage*/
				feeDistance = mileage - toAdd.data.mileage;

				/*update data in the removed node then transfer to new list*/
				toAdd.data.mileage = mileage;
				toAdd.data.returnDate = 0;
				insertAvailable(receive, toAdd.data);
				printf("Adding a returned car to the available-for-rent list...\n");

				/*calculate fee - wasnt in the mood to make a seperate function :) */
				if(feeDistance <= 100 && feeDistance >= 0){
					fee = 40;
				}else{
					fee = 40 + ((feeDistance - 100)*0.15);
				}
			}else{
				/*incorrect mileage, return removed node to prev list and prompt*/
				insertRented(get,toAdd.data);
				printf("Invalid mileage!\n");
			}

			/*reset values print fee*/
			printf("Fee for rent: $%.2f\n", fee);
			fee = 0;
			feeDistance = 0;
		}else{
			/*if default the car didnt exist in the searched list*/
			printf("Could not find car from rented list! \n");
		}
		break;
		case 3:
		/*make sure toAdd is not a default node*/
		if(strcmp(toAdd.data.plate,"DEFAULT") != 0){
			if(mileage >= toAdd.data.mileage){
				/*only charge for distance traveled in case there was a prev mileage*/
				feeDistance = mileage - toAdd.data.mileage;

				/*update data in the removed node then transfer to new list*/
				toAdd.data.mileage = mileage;
				toAdd.data.returnDate = 0;
				insertRepair(receive, toAdd.data);
				printf("Adding a returned car to the repair list...\n");

				/*calculate fee*/
				if(feeDistance <= 100 && feeDistance >= 0){
					fee = 40;
				}else{
					fee = 40 + ((feeDistance - 100)*0.15);
				}
			}else{
				/*incorrect mileage, return removed node to prev list and prompt*/
				insertRepair(get, toAdd.data);
				printf("Invalid mileage");
			}	
			/*reset vars and print fee*/
			printf("Fee for rent: $%.2f\n", fee);
			fee = 0;
			feeDistance = 0;
		}else{
			/*if default the car didnt exist in the searched list*/
			printf("Could not find car from rented list! \n");
		}
		break;
		case 4:
		/*if not default transfer node into available*/
		if(strcmp(toAdd.data.plate,"DEFAULT") != 0){
			insertAvailable(receive, toAdd.data);
			printf("Transfering a car from the repair list to the available-for-rent list...\n");
		}else{
			printf("Could not find car from repair list! \n");
		}
		break;
		default:
		break;
	}

}





