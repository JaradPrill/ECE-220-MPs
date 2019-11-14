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
    double c;
    while (feof(file)==0)  {
        fscanf(file, "%d %d %lf", &a, &b, &c); 
        //printf("found nonzero value, storing now\n");
        set_tuples(tuples, a, b, c);
        //printf("successfully stored value\n");
    } 
    
    fclose(file);
    return tuples;
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
    //printf("entered set_touples fcn\n");

    //If value is 0 delete node instead of adding
    //Jump to helper function delete node
    if(value == 0){
        delete_node(mat_t, row, col);
        return;
    }
    //Adding a node - increment nonzero counter 
    mat_t->nz += 1;

    //Allocate memory for new node
    sp_tuples_node *new = malloc(sizeof(sp_tuples_node));
    //printf("successfully allocated new node memory\n");

    //Set new node members based on input
    new->col = col;
    new->row = row;
    new->value = value;
    //printf("successfullly stored members of set touples\n");


    sp_tuples_node *current = mat_t->tuples_head;

    //List is empty
    //Set head pointer to new
    //set new next to empty
    if(current==NULL){
        mat_t->tuples_head = new;
        new->next=NULL;
        return;
    }


    //Node needs to be inserted at HEAD
    //Set head pointer to new
    //set new next to the old HEAD
    if((current->row > row || (current->row == row && current->col > col))){
        new->next = current;
        mat_t->tuples_head = new;
        return;
    }

    //Iterate through linked list
    while(current!=NULL){ 

        //A current node is found and value needs to be replaced
        if(current->row == row && current->col == col){
            current->value = value;
            free(new);
            mat_t->nz--;
            return;
        }
        
        //Tail node is reached
        if(current->next==NULL){
            current->next = new;
            new->next = NULL;
            return;
        }


        //Found non head location in list where node should be inserted
        if(current->next->row > row || (current->next->row == row && current->next->col > col)){
            new->next = current->next;
            current->next = new;
            return;

        }

        //Iterate to next element of linked list
        current=current->next;
        
    }
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
    //printf("allocated new matrix memory\n");
    matC->n = 3;
    //printf("stored matC cols as %d\n", matC->n);
    matC->nz = 0;
    matC->m = 5;
    //printf("stored members of matrix C\n");

    sp_tuples_node *current = matA->tuples_head;
    //printf("created node pointer to first node\n");

    while(current != NULL){
        set_tuples(matC, current->row, current->col, current->value);
        current = current->next;
    }
    //printf("copied c into a\n");

    current = matB->tuples_head;

    while(current != NULL){
        set_tuples(matC, current->row, current->col, gv_tuples(matC, current->row, current->col)+current->value);
        current = current->next;
    }
    //printf("Completed addition of A and B\n");

	return matC;
}


/*
INPUT: matrix A with size mAxnA, and with matrix B size mBxnB 
INITIATE matrix C with the size mAxnB and nz = 0
FOR every non-zero entry in A 
    iA = row of current entry in A; jA = column of current entry in A
    FOR every non-zero element in B with row iB = jA                
        C_(iA,jB) = C_(iA,jB) + A_(iA,jA) * B_(iB,jB);              
*/
sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 
    // mak sure if the inputs are of valid size: n1 == m2
    if (matA->n != matB->m)
        return NULL;
    int i, j;
    sp_tuples_node *currentA = matA->tuples_head;
    sp_tuples_node *currentB = matB->tuples_head;

    // create new matrix matC
    sp_tuples * matC = malloc(sizeof(sp_tuples));
    //initiate matrix C with the size mAxnB and nz = 0
    matC->m = matA->m;
    matC->n = matB->n;
    matC->nz = 0;
    // populate matrix C
    for (i=0; i<matC->m; i++){
        for (j=0; j<matC->n; i++){
            set_tuples(matC, i, j, 0.0);
        }
    }

    // pointer to head, create access to the link list for matC
    sp_tuples_node *currentC = matC->tuples_head;

    while(current != NULL)//FOR every non-zero entry in A 
    { 
        for (j=0; j<=matB->nz; j++) //FOR every non-zero element in B
        {
            // every element in B where the row is equal to the column of the element in A
            if (currentB->row == currentA->col)
            {
                // accumulate value
                currentC->value += currentA->value * currentB->value;
                currentC = currentC->next; //get ready for next value
            }
            currentB = currentB->next; //check next in matB
        }
        currentA = currentA->next; //check next in matA
        // need to reset head pointer for B ?
        currentB = matB->tuples_head; //not sure about this
    }


    return matC;

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






