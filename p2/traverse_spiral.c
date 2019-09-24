////////////////////////////////////////////////////////////////////////////////
// Main File:        traverse_spiral.c
// This File:        traverse_spiral.c
// Other Files:
// Semester:         CS 354 Fall 2018
//
// Author:           Kendra Raczek
// Email:            raczek@wisc.edu
// CS Login:         raczek
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//
// Persons:
//
// Online sources:   TutorialsPoint - for information on how to read an parse
//					 input from file
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *COMMA = ","; 

// Structure representing Matrix
// size: Dimension of the square (size*size)
// array: 2D array of integers
typedef struct _Square {  
    int size;
    int **array;
} Square;

/* TODO:
 * Retrieves from the first line of the input file,
 * the size of the square matrix.
 * 
 * fp: file pointer for input file
 * size: pointer to size of the square matrix
 */
void get_dimensions(FILE *fp, int *size) {
	char *line = NULL;
	size_t length = 0;
	if (getline(&line, &length, fp) == -1) {
		printf("Error in get dimensions.\n");
		exit(1);
	}
	char *token = NULL;
	token = strtok(line, COMMA);
	*size = atoi(token);
}

/* PARTIALLY COMPLETED:
 * Traverses a given layer from the square matrix
 * 
 * array: Heap allocated 2D square matrix
 * rows: pointer to size of square
 * layer: layer number to be traversed
 * op: pointer to the output file
 */
void traverse_layer(int **array, int size, int layer, FILE *op) {       
	int row_num, col_num;

	//corner case: size is odd & the layer is last so only one entry to print
        if(size % 2 == 1 && layer == (size + 1) / 2 - 1){
            fprintf(op, "%d\n", *(*(array + layer) + layer));
                return;
        }

	// Traverse upper row from left to right with appropriate bounds
	row_num = layer;
	for(int j = row_num; j <= size - 1 - row_num; j++) {
       fprintf(op, "%d ", *(*(array + row_num) + j));
	}

	// Traverse right column from top to bottom with appropriate bounds
	col_num = size-layer-1;
	for(int i = layer + 1; i <= col_num; i++) {
	    fprintf(op, "%d ", *(*(array + i) + col_num));
	}

	// Traverse lower row from right to left with appropriate bounds
	row_num = size-layer-1;
	for(int j = row_num-1; j >= layer; j--) {
		fprintf(op, "%d ", *(*(array + row_num) + j));
	}

	// Traverse left column from bottom to top with appropriate bounds
	col_num = layer;
	for(int i = size - col_num - 2; i >= col_num + 1; i--) {
        fprintf(op, "%d ", *(*(array + i) + col_num));
	}
}

/* COMPLETED:
 * Traverses the square matrix spirally
 * 
 * square: pointer to a structure that contains 2D square matrix
 * op: pointer to the output file
 */
void traverse_spirally(Square *square, FILE *op) {       
	int size = square->size; 
	int num_layers = 0;   
	num_layers = size/2; 
	if(size%2 == 1) {
		num_layers++;
	}
	 
	int i;
	for(i = 0; i < num_layers; i++) {
		traverse_layer(square->array, size, i, op);
	}
}

/* PARTIALLY COMPLETED:
 * This program reads a square matrix from the input file
 * and outputs its spiral order traversal to the output file
 *
 * argc: CLA count
 * argv: CLA value
 */
int main(int argc, char *argv[]) {                  

	// Check if number of arguments is correct
	if (argc != 3) {
		printf("Incorrect number of command-line arguments\n");
		exit(1);
	}
	
	// Open the file and check if it opened successfully
	FILE *fp = fopen(*(argv + 1), "r");
	if (fp == NULL) {
		printf("Cannot open file for reading.\n");
		fclose(fp);
		exit(1);
	}

	// Call the function get_dimensions to retrieve size of the square matrix
	int size;
	get_dimensions(fp, &size);

	// Dynamically allocate a 2D array as per the retrieved dimensions
	int **board;
	board = malloc(sizeof(int*) * size);

	if (board != NULL) {
		for (int i = 0; i < size; i++) {
			(*(board + i)) = malloc(sizeof(int) * size);
		}
	}
	else {
		printf("Memory allocation failed.\n");
		exit(1);
	}

	// Read the file line by line by using the function getline as used in get_dimensions
	// Tokenize each line wrt comma to store the values in the square matrix
    char *line = NULL;
    size_t length = 0;
    char *token = NULL;
    for (int i = 0; i < size; i++) {

        if (getline(&line, &length, fp) == -1) {
            printf("Error while reading the file.\n");
            exit(1);
        }

        token = strtok(line, COMMA);
        for (int j = 0; j < size; j++) {
            (*(*(board + i) + j)) = atoi(token);
            token = strtok(NULL, COMMA);
        }
    }

	// Create a structure and initialize its size and array fields appropriately
    Square sq = {size, board};
    Square *sqptr = malloc(sizeof(Square));
    if (sqptr == NULL) {
    	printf("Structure malloc error.\n");
    	exit(1);
    }
    *sqptr = sq;

	// Open the output file
	FILE *op = fopen(*(argv + 2), "w");
	if (op == NULL) {
		printf("Cannot open file for writing.\n");
		fclose(op);
		fclose(fp);
		exit(1);
	}

	// Call the function traverse_spirally
	traverse_spirally(sqptr, op);

	// Free the dynamically allocated memory
    for (int i = 0; i < size; i++) {
        free(*(sqptr -> array + i));
    }
    free(sqptr -> array);
    sqptr -> array = NULL;
    sqptr = NULL;

	// Close the input file
    fclose(fp);
	// Close the output file
	fclose(op);

	return 0; 
}