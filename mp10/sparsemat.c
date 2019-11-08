#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>





sp_tuples * load_tuples(char* input_file)
{//use set_tuples to sort list as it is created

    //open file for processing
    FILE *file;
    file = fopen(input_file, "r");

    //allocate memory
    sp_tuples * tuples = malloc(sizeof(sp_tuples));

    //read matrix size into sp_tuples
    int a, b;
    fscanf(file, "%d %d", &a, &b);
    tuples->m = a;
    tuples->n = b;

    //read tuples and build linked list
    int check;
    double c;
    do {
        check = fscanf(file, "%d %d %f", &a, &b, &c); //ret 0 if nothing read
        if (check!=0){
            tuples->nz++;
            set_tuples(sp_tuples, a, b, c);
        }
    } while (check!=0);
    
    fclose(file);
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
    sp_tuples_node *current = mat_t->tuples_head;
    while(current != NULL){
        //Head node should be deleted
        if(current->row == row && current->col == col){
            free(current);
            mat_t->nz --;
            mat_t->tuples_head = NULL;
            return;
        }
        //Break if we are on the tail node
        if(current->next == NULL) break;

        //None head touple found that needs to be deleted
        if(current->next->row == row && current->next->col == col){
            sp_tuples_node *temp = current->next;
            current->next = temp->next;
            free(temp);
            mat_t->nz--;
            return;
        }
        //Iterate to next node
        current = current->next;
    }

    //Reached end of list with no Node found
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
    //open file for writing
    FILE * file;
    file = fopen(file_name, "w")

    //print row and col values
    fprintf(file, "%d %d\n", mat_t->n, mat_t->m);

    //print tuples into file
    int i;
    for(i=0; i<mat_t->nz, i++){
        fprintf(file, "%d, %d, %f\n", mat_t->(tuples_head+i)->row,mat_t->(tuples_head+i)->col,mat_t->(tuples_head+i)->value);
    }


    fclose(file);
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






