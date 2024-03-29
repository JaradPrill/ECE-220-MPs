#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

/*
Intro Paragraph:
In this program we create a maze data structure from an input text file, then using depth first search, solve the maze.
We use 4 functions to accompish this goal:
    1. createMaze: In this we take in the file, extract the maze dimensions, and then build the maze in the cells
        element of the maze data structure. While creating the cells element and the larger maze struct, we 
        use malloc to allocate memory for these structs.
    2. destroyMaze: This function simply frees up all the allocated memory once the maze has been solved.
        This is done by first freeing the smaller, 1-D arrays that are pointed to by the values that compose
        the "cells" 1-D array. 
    3. printMaze: this functions uses two iterarative loops to print out the the entire maze in a visualization of a 
        2-D array.
    3. solveMazeDFS: this function uses recursion and backtracking to find a valid route to the end. we guess our path
        through each location in the maze by fnding the empty spots and mark the empty spots as a pathway. when all the
        check for all four directions fails, we will make the current location as visited back track to make changes to 
        previous decisions.

partners: Kamatar2, Bozhaoj2, jaradjp2
*/

/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
    //Create file pointer to fileName given
    FILE *file;

    //Open the text file containing maze structure
    file = fopen(fileName, "r");

    //Create maze pointer and allocate memory
    maze_t * maze = malloc(sizeof(maze_t));
    // assign width and hight from file to maze struct
    int m, n;
    char c;
    fscanf(file, "%d %d", &m, &n);
    maze->width = n;
    maze->height = m;   

    //Allocate memory for cells row pointer 
    maze->cells = malloc(sizeof(maze->cells)*(maze->height)); 
    
    //Allocate memory for the size of a row
    int i,j;
    for(i = 0; i < maze->height; i++){
        maze->cells[i] = malloc(sizeof(maze->cells[i]) * maze->width);
        // if(maze->cells[i] == NULL) printf("Didn't assign memory\n");
    }
    // printf("allocated memory in each char arrary\n");

    fscanf(file, "%c", &c);//Discard unneeded newline char

    //Populate each element of cells
    for(i = 0; i < maze->height; i++){
        for(j = 0; j < maze->width; j++){
            fscanf(file, "%c", &c);
            //printf("Scanned: %c at lcoation [%d][%d]\n", m, i, j);
            maze->cells[i][j] = c;
            //printf("stored char in [%d][%d]\n", i, j);
            if(maze->cells[i][j] == 'S'){//assign variables to struct
                maze->startRow = i;
                maze->startColumn = j;
            }
            if(maze->cells[i][j] == 'E'){//assign variables to struct
                maze->endRow = i;
                maze->endColumn = j;
            }
        }
        fscanf(file, "%c", &c);//discard newline character after each row    
    }
    fclose(file);
    return maze;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    //free cells memory
    int i;
    for(i=0;i<maze->height;i++){
        free(maze->cells[i]);
    }

    //frees entire struct
    free(maze->cells);
    free(maze);
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here
    int row = maze->height;
    int col = maze->width;
    int i,j;
    for (i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            printf("%c",maze->cells[i][j]);
        }
        //if (i<row-1) //do not print new line for last row
            printf("\n"); 
    }

}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.
    if (col<0 || row<0 || row>=maze->height || col>=maze->width){ //check if outside of range
        return 0;
    }
    if (maze->cells[row][col]!='S' && maze->cells[row][col]!='E'){ //check if we at the start or the end
        if (maze->cells[row][col]!= ' '){ //return false if not empty
            return 0;
        }
    }

    if (maze->cells[row][col]=='E'){ //if we have reached the end, we done
        maze->cells[maze->startRow][maze->startColumn]='S';//restore starting position
        return 1;
    }

    maze->cells[row][col]='*'; //mark location as part of solution
    
    

    if (solveMazeDFS(maze, col-1, row)){
        return 1;
    }
    if (solveMazeDFS(maze, col+1, row)){
        return 1;
    }
    if (solveMazeDFS(maze, col, row+1)){
        return 1;
    }
    if (solveMazeDFS(maze, col, row-1)){
        return 1;
    }
    
    maze->cells[row][col]='~'; //mark as visited
    
    
    return 0;
}
