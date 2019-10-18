#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
  int col;
  for(col = 0; col < 9; col++){
    if(sudoku[i][col] == val) return 1;
  }
  
  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  int row;
  for(row = 0; row < 9; row++){
    if(sudoku[row][j] == val) return 1;
  }

  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  
  // BEG TODO
  int row, col;
  int row_grid = i/3;
  int col_grid = j/3;
  for(row = 0; row < 3; row++){
    for(col = 0; col < 3; col++){
      int rowloc = row_grid*3 +row;
      int colloc = col_grid*3 +col;
      if(sudoku[rowloc][colloc] == val) return true;
    }
  }
  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  if(is_val_in_3x3_zone(val, i, j, sudoku) || is_val_in_col(val, j, sudoku) || is_val_in_row(val, i, sudoku)){
    return 0;
  }
  return 1;
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
  int i,j, unfilled_flag;
  unfilled_flag = 0;
  for(i = 0; i < 9; i++){
    for(j = 0; j < 9; j++){
      if(sudoku[i][j] == 0) {
        unfilled_flag = 1;
        break;
      }
    }
    if(unfilled_flag == 1) break;
  }
  if(unfilled_flag == 0) return true;
  
  // i, j hold a value of an unfilled location
  //printf("testing values at %d + %d \n", i, j);
  int num;
  for(num = 1; num <= 9; num++){
    if(is_val_valid(num, i, j, sudoku)){
      sudoku[i][j] = num;
      //printf("found valid number %d\n", num);
      if(solve_sudoku(sudoku)) return true;
      else {
        //printf("No solutions found for this number\n");
        sudoku[i][j] = 0;
      }
    }
  }

  return false;
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}





