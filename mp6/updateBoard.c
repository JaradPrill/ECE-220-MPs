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
    for(i = (row-1); i <= (row+1); i++){
        if(i >= 0 && i < boardRowSize){
            for(j = (col-1); j <= (col+1); j++){
                if(j>=0 && j<boardColSize){
                    if(i != row && j != col){
                        liveNeigbors += *(board+ (i*(boardColSize-1)) + j);
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
    int oldBoard[boardRowSize*boardRowSize];
    int i;
    for(i = 0; i < boardColSize*boardRowSize; i++){
        oldBoard[i] = board[i];
    }
    for(i = 0; i < boardRowSize*boardColSize; i++){
        liveNeigbors = countLiveNeighbor(oldBoard, boardRowSize, boardColSize, i/boardColSize, i%boardColSize);
        if(liveNeigbors < 2 || liveNeigbors >3) board[i] = 0;
        else if(liveNeigbors == 3) board[i] = 1;

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
    int newBoard[boardRowSize*boardColSize];
    int i;
    for(i = 0; i < boardColSize*boardRowSize; i++){
        newBoard[i] = board[i];
    }
    updateBoard(newBoard, boardRowSize, boardColSize);
    for(i = 0; i < boardColSize*boardRowSize; i++){
        if(board[i] != newBoard[i]) return 0;
    }
    return 1;
}

				
				
			

