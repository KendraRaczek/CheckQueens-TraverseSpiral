////////////////////////////////////////////////////////////////////////////////
// Main File:        check_queens.c
// This File:        check_queens.c
// Other Files:
// Semester:         CS 354 Fall 2018
//
// Author:           Kendra Raczek
// Email:            raczek@wisc.edu
// CS Login:         raczek
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:
//
// Online sources:   StackOverflow: quick questions about c language definitions
//
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h> 
#include <stdlib.h>  
#include <string.h>   

char *COMMA = ",";

/* COMPLETED:
 * Retrieves from the first line of the input file,
 * the number of rows and columns for the board.
 * 
 * fp: file pointer for input file
 * rows: pointer to number of rows
 * cols: pointer to number of columns
 */
void get_dimensions(FILE *fp, int *rows, int *cols) {
	char *line = NULL; 
	size_t len = 0;
	if (getline(&line, &len, fp) == -1) { 
		printf("Error in reading the file\n");
		exit(1); 
	}

	char *token = NULL; 
	token = strtok(line, COMMA);
	*rows = atoi(token); 

	token = strtok(NULL, COMMA); 
	*cols = atoi(token);
}      

/* Returns 1 if and only if there exists at least one pair
 * of queens that can attack each other.
 * Otherwise returns 0.
 * 
 * board: heap allocated 2D board
 * rows: number of rows
 * cols: number of columns
 */
int check_queens(int **board, int rows, int cols) {           

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			// there is a queen in this position
			if( *(*(board + i) +j) == 1) {

				// check for attacking queens

				// check for queens in column
				for (int n = i + 1; n < rows; n++) {
					if ( *(*(board + n) +j) == 1) {
						return 1;
					}
				}

				// check for queens in row
				for (int m = j + 1; m < cols; m++) {
					if ( *(*(board + i) +m) == 1) {
						return 1;
					}
				}

				// check for queens in diagonal

				// left diagonal
                int p = 1;
				int r = 1;
				while (((i + p) < rows) && ((j-r) >= 0)) {
				    if ( *(*(board + (i+p)) +(j-r)) == 1) {
				        return 1;
				    }
				    p++;
				    r++;
				}
				// right diagonal
                p = 1;
				r = 1;
				while(((i + p)  < rows) && ((j+r) < cols)) {
				    if (*(*(board + (i+p)) +(j+r)) == 1) {
				        return 1;
				    }
				    p++;
				    r++;
				}
			}
		}
	}
	return 0;
}     

/* PARTIALLY COMPLETED:
 * This program prints true if the input file has any pair
 * of queens that can attack each other, and false otherwise
 * 
 * argc: CLA count
 * argv: CLA value 
 */
int main(int argc, char *argv[]) {                

		if (argc != 2) {
			printf("Incorrect number of command-line arguments\n");
			exit(1);
		}

	//Open the file and check if it opened successfully.
	FILE *fp = fopen(*(argv + 1), "r");
	if (fp == NULL) {
		printf("Cannot open file for reading\n");
		exit(1);
	}

        //Declare local variables.
        int rows, cols;
		get_dimensions(fp, &rows, &cols);

        // pointer to 2D array of chess board
        int **boardptr;
        boardptr = malloc(sizeof(int*) * rows);

        if (boardptr != NULL) {
            for (int i = 0; i < rows; i++) {
                (*(boardptr + i)) = malloc(sizeof(int) * cols);
            }
        }
        else {
            printf("memory allocation failed\n");
        }

	//Read the file line by line.
	//Tokenize each line wrt comma to store the values in your 2D array.
	char *line = NULL;
	size_t len = 0;
	char *token = NULL;
	for (int i = 0; i < rows; i++) {

		if (getline(&line, &len, fp) == -1) {
			printf("Error while reading the file\n");
			exit(1);	
		}

		token = strtok(line, COMMA);
		for (int j = 0; j < cols; j++) {
            (*(*(boardptr + i) + j)) = atoi(token);
			token = strtok(NULL, COMMA);	
		}
	}

	int result = check_queens(boardptr, rows, cols);
	// there aren't any queens in attacking position
	if (result == 0) {
        printf("false\n");
	}
	// there is a queen in attacking position
	else if (result == 1) {
	    printf("true\n");
	}
	else {
	    printf("error\n");
	    exit(1);
	}

    for (int i = 0; i < rows; i++) {
        free(*(boardptr + i));
    }
    free(boardptr);
    boardptr = NULL;

	//Close the file.
	if (fclose(fp) != 0) {
		printf("Error while closing the file\n");
		exit(1);	
	}

	return 0;
}