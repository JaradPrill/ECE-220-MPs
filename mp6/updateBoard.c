/*
Intro Paragraph:
In this program we have three functions:

1. countLiveNeighbor
    Counts the amount of neighboring cells that are alive. This is done by 
    looping through the nearby rows and columns using two for loops. We also
    check if the row or column is valid before moving on. This prevents us from checking
    excessive cells for corner or edge cases.
2. updateBoard
    First we store the current board into oldBoard and then we use the countLiveNeighbor
    function on the oldBoard to find what the new value for a particular location
    in board should be. This way we can update the board without new values altering
    the updated values of other cells.
3. aliveStable
    this checks if nothing has changes between two steps. If they have then we have
    reached a stable point and there is no point in continuing the process. This is done
    by finding the new board setup by calling updateBoard on a temp array called newBoard.
    Then we go through and compare the newBoard elements to the board elements, if any
    change is found we return 0. If no change is found then we return 1 and the program will end.s


partners: jaradjp2, kamatar2, bozhaoj2
*/


/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
    int liveNeigbors = 0;
    int i;
    int j;
    for(i = (row-1); i <= (row+1); i++){ //loop through neighoring rows
        if(i >= 0 && i < boardRowSize){ //check if the row is within the board boundaries
            for(j = (col-1); j <= (col+1); j++){ //loop though the neighboring columns
                if(j>=0 && j<boardColSize){ //check if the column is within bounds
                    if(i != row || j != col){ //don't check the current cell
                        liveNeigbors += *(board+ (i*(boardColSize)) + j); //add the value of the cell to counter (0 or 1)
                    }
                }
            }
        }
    }
    return liveNeigbors;
}
/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
    int liveNeigbors;
    int oldBoard[boardColSize*boardRowSize]; //int oldBoard as same size as board
    int i;
    for(i = 0; i < boardColSize*boardRowSize; i++){ //duplicate board into oldBoard
        oldBoard[i] = *(board+i);
    }
    for(i = 0; i < boardRowSize*boardColSize; i++){
        liveNeigbors = countLiveNeighbor(oldBoard, boardRowSize, boardColSize, i/boardColSize, i%boardColSize);
        if(liveNeigbors < 2 || liveNeigbors >3) *(board+i) = 0; //kills cell
        else if(liveNeigbors == 3) *(board+i) = 1; //births cell
        //else just retain whatever the cell value was
    }
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
    int newBoard[boardRowSize*boardColSize]; //int newBoard with same size as board
    int i;
    for(i = 0; i < boardColSize*boardRowSize; i++){ //duplicate board into newBoard
        newBoard[i] = *(board+i);
    }
    updateBoard(newBoard, boardRowSize, boardColSize); //newBoard updated to next tick
    for(i = 0; i < boardColSize*boardRowSize; i++){
        if(*(board+i) != newBoard[i]) { //goes through and compares each element of the next array and current array
            return 0; //if any change is detected, return 0
    }
    }
    return 1; //no difference so we return 1
}
