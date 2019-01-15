/*
Brayden Klemens
1000487
11/05/2018
Assignment 3
*/

#include "q2.h"

int main(int argc, char *argv[]){

	int nums[20][10];
	char *buffer = malloc(sizeof(char)*100);
	int *temp = malloc(sizeof(int)*10);
	char *token = malloc(sizeof(char)*3);

	//Open file for reading
	FILE *fp;
	fp = fopen(argv[1], "r");

	//check if file opened
	if(fp != NULL) {
		printf("file opened...\n\n");
	}else{
		printf("failed to open file...\n\n");
		exit(0);
	}

	//fill 2D array with data from file
	for(int i = 0; i < 20; i++){
		fgets(buffer,100,fp);
		token = strtok(buffer," ");
		for(int j = 0; j < 10; j++){
			temp[j] = atoi(token);
			token = strtok(NULL, " ");
			nums[i][j] = temp[j];
		}
	}
	fclose(fp); 

	//sort by downHeap
	downHeap(nums);

	//display the 20 X 10 table
	display(nums);


	return 0;
}

/*
- get parent and both children
- if parent is greater than child swap all data
- recursion because the loop needs to restart and check parent and child values
*/
void downHeap(int nums[20][10]){

	//vars
	int parent = 0, child1 = 0, child2 = 0;

	//first 10 are internal last 10 are not (each parent has 2 children except for last one) - loop 10 times
	for(int i = 0; i < 10; i++){
		//get the values of each 3 nodes to compare each time
		parent = nums[i][0] + nums[i][1] + nums[i][2];
		child1 = nums[(i * 2)][0] + nums[(i * 2)][1] + nums[(i * 2)][2];
		child2 = nums[(i * 2) + 1][0] + nums[(i * 2) + 1][1] + nums[(i * 2) + 1][2];

		//make heap swap if parent is larger
		if(parent > child1){

			//get all data and swap key
			swapC1(nums, i);
			//recursive call to restart after swapping
			downHeap(nums);
		}

		if(parent > child2){

			//get all data and swap key
			swapC2(nums,i);
			//recursive call to restart after swapping
			downHeap(nums);
		}
	}
}

void swapC1(int nums[20][10], int i){
	int *temp = malloc(sizeof(int)*10);
	for(int j = 0; j < 10; j++){
		temp[j] = nums[i][j];
		nums[i][j] = nums[(i * 2)][j];
		nums[(i * 2)][j] = temp[j]; 
	}
}

void swapC2(int nums[20][10], int i){
	int *temp = malloc(sizeof(int)*10);
	for(int j = 0; j < 10; j++){
		temp[j] = nums[i][j];
		nums[i][j] = nums[(i * 2) + 1][j];
		nums[(i * 2) + 1][j] = temp[j]; 
	}
}

//display the result of the heap
void display(int nums[20][10]){

	//go through entire new heap and print each value
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 10; j++){
			printf("%d ",nums[i][j]);
		}
		printf("\n");
	}
}












