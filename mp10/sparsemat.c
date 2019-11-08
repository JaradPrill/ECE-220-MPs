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
        check = fscanf(file, "%d %d %lf", &a, &b, &c); //ret 0 if nothing read
        if (check!=0){
            printf("found nonzero value, storing now\n");
            tuples->nz++;
            set_tuples(tuples, a, b, c);
            printf("successfully stored value\n");
        }
    } while (feof(file));
    
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
    printf("entered set_touples fcn\n");

    if(value == 0) delete_node(mat_t, row, col);
    mat_t->nz += 1;
    sp_tuples_node *new = malloc(sizeof(sp_tuples_node));
    printf("successfully allocated new node memory\n");

    new->col = col;
    new->row = row;
    new->value = value;
    printf("successfullly stored members of set touples\n");


    sp_tuples_node *current = mat_t->tuples_head;


    do{
        //Node needs to be inserted at HEAD
        if(current == NULL || current->row > row || (current->row == row && current->col > col)){
            new->next = current;
            mat_t->tuples_head = new;
            return;
        }

        printf("entered while loop\n");
        //A current node is found and value needs to be replaced
        if(current->row == row && current->col == col){
            current->value = value;
            free(new);
            return;
        }
        
        
        //Found non head location in list where node should be inserted
        if(current->next != NULL && (current->next->row >row || (current->next->row == row && current->next->col > col))){
            new->next = current->next;
            current->next = new;
            return;

        }
        current = current->next;

    }while(current->next != NULL);

    //Tail node is reached
    printf("Not in while loop\n");
    current = new;
    new->next = NULL;

    return;
}





void save_tuples(char * file_name, sp_tuples * mat_t)
{
    //open file for writing
    FILE * file;
    file = fopen(file_name, "w");

    //print row and col values
    fprintf(file, "%d %d\n", mat_t->n, mat_t->m);

    //print tuples into file
    int i;
    sp_tuples_node *current = mat_t->tuples_head;
    for(i=0; i<mat_t->nz; i++){
        fprintf(file, "%d, %d, %lf\n", current->row, current->col, current->value);
        current = current->next;
    }


    fclose(file);
	return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){
    sp_tuples *matC = malloc(sizeof(sp_tuples));
    printf("allocated new matrix memory\n");
    matC->n = 3;
    printf("stored matC cols as %d\n", matC->n);
    matC->nz = 0;
    matC->m = 5;
    printf("stored members of matrix C\n");

    sp_tuples_node *current = matA->tuples_head;
    printf("created node pointer to first node\n");

    for(int i = 0; i < matA->nz; i++){
        set_tuples(matC, current->row, current->col, current->value);
        current = current->next;
    }
    printf("copied c into a\n");

    current = matB->tuples_head;
    for(int j = 0; j < matB->nz; j++){
        set_tuples(matC, current->row, current->col, gv_tuples(matC, current->row, current->col)+current->value);
        current = current->next;
    }

	return matC;
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 
    return NULL;

}


	
void destroy_tuples(sp_tuples * mat_t){
    sp_tuples_node *curr = mat_t->tuples_head;
    while(curr != NULL){
        sp_tuples_node *next = curr->next;
        free(curr);
        curr = next;
    }
	
    free(mat_t);
	
    return;
}  






