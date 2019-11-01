#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    //Create file pointer to fileName given
    FILE *file;

    //Open the text file containing maze structure
    file = fopen(fileName, "r");
    if(file == NULL) printf("did not find file\n");

    //Create maze pointer and allocate memory
    maze_t * maze = malloc(sizeof(maze_t));
    printf("successfully allocated maze structure\n");

    int m, n;
    fscanf(file, "%d %d", &m, &n);
    printf("Width: %d Height: %d\n", n,m);

    maze->width = n;
    maze->height = m;
    printf("assigned width and height %d\n", maze->height);

    //Allocate memory for cells row pointer 
    maze->cells = malloc(sizeof(maze->cells)*(maze->height)); 
    printf("allocated cell pointer array memory\n");
    
    
    //Allocate memory for the size of a row
    int i,j;
    for(i = 0; i < maze->height; i++){
        maze->cells[i] = malloc(sizeof(maze->cells[i]) * maze->width);
        if(maze->cells[i] == NULL) printf("Didn't assign memory\n");
    }
    printf("allocated memory in each char arrary\n");

    //Discard unneeded newline
    fscanf(file, "%c", &m);
    

    //Populate each element of cells
    for(i = 0; i < maze->height; i++){
        for(j = 0; j < maze->width; j++){
            fscanf(file, "%c", &m);
            printf("Scanned: %c at lcoation [%d][%d]\n", m, i, j);
            maze->cells[i][j] = m;
            printf("stored char in [%d][%d]\n", i, j);
            
            if(maze->cells[i][j] == 'S'){
                maze->startRow = i;
                maze->startColumn = j;
            }
            if(maze->cells[i][j] == 'E'){
                maze->endRow = i;
                maze->endColumn = j;
            }
            
        }
        fscanf(file, "%c", &m);    

    }
    

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
    // Your code here.
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
    // Your code here.
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
    return 0;
}
