#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>





sp_tuples * load_tuples(char* input_file)
{

    return NULL;
}



double gv_tuples(sp_tuples * mat_t,int row,int col)

{
    //Potential check if entries are out of bounds
    //if(row < 0 || col < 0 || row >= mat_t->m || col >= mat_t->n) return -1;

    //Create a pointer to the current touple node
    sp_tuples_node *current = mat_t->tuples_head;

    //Iterate until we reach tail Node
    while(current != NULL){   
        if(current->row == row && current->col == col) return current->value;
        else current = current->next;
    }
    return 0;
}

//Helper function delete node
void delete_node(sp_tuples * mat_t, int row, int col){
    
    return;

}


void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    if(value == 0) delete_node(mat_t, row, col);
    mat_t->nz += 1;
    sp_tuples_node *new = malloc(sizeof(sp_tuples_node));
    new->col = col;
    new->row = row;
    new->value = value;
    sp_tuples_node *current = mat_t->tuples_head;


    while(current != NULL){
        //A current node is found and value needs to be replaced
        if(current->row == row && current->col == col){
            current->value = value;
            free(new);
            return;
        }
        //Node needs to be inserted at HEAD
        if(current->row > row || (current->row == row && current->col > col)){
            new->next = current;
            mat_t->tuples_head = new;
            return;
        }
        //Check if we are at tail before calling members of next
        if(current->next == NULL) break;
        //Found non head location in list where node should be inserted
        if(current->next->row >row || (current->next->row == row && current->next->col > col)){
            new->next = current->next;
            current->next = new;
            return;

        }
        current = current->next;

    }

    //If list is empty or tail is reached
    current->next = new;
    new->next = NULL;

    return;
}





void save_tuples(char * file_name, sp_tuples * mat_t)
{

	return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){

	return NULL;
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 
    return NULL;

}


	
void destroy_tuples(sp_tuples * mat_t){
	
    return;
}  






