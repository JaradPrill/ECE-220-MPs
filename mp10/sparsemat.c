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
    tuples->nz = 0;
    tuples->tuples_head=NULL;
    //read tuples and build linked list
    double c;
    while (feof(file)==0)  {
        fscanf(file, "%d %d %lf", &a, &b, &c); 
        set_tuples(tuples, a, b, c);
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

    //Matrix is empty
    if(current == NULL) return;

    //Head node should be deleted
        if(current->row == row && current->col == col){
            free(current);
            mat_t->nz --;
            mat_t->tuples_head = NULL;
            return;
        }

    while(current != NULL){   
        //Break if we are on the tail node
        if(current->next == NULL) break;

        //None head touple found that needs to be deleted
        if(current->next->row == row && current->next->col == col){
            sp_tuples_node *temp = current->next;
            current->next = temp->next;
            free(temp);
            mat_t->nz = mat_t->nz- 1;
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

    //Set new node members based on input
    new->col = col;
    new->row = row;
    new->value = value;


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
    FILE * file = NULL;
    file = fopen(file_name, "w");

    //print row and col values
    fprintf(file, "%d %d\n", mat_t->m, mat_t->n);

    //print tuples into file
    int i;
    sp_tuples_node *current = mat_t->tuples_head;
    for(i=0; i<mat_t->nz; i++){
        fprintf(file, "%d %d %lf\n", current->row, current->col, current->value);
        current = current->next;
    }


    fclose(file);
	return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){
    sp_tuples *matC = malloc(sizeof(sp_tuples));
    matC->m = matA->m;
    matC->nz = 0;
    matC->n = matA->n;

    sp_tuples_node *current = matA->tuples_head;

    while(current != NULL){
        set_tuples(matC, current->row, current->col, current->value);
        current = current->next;
    }

    current = matB->tuples_head;

    while(current != NULL){
        set_tuples(matC, current->row, current->col, gv_tuples(matC, current->row, current->col)+current->value);
        current = current->next;
    }

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
    //int i, j;
    sp_tuples_node *currentA = matA->tuples_head;
    sp_tuples_node *currentB = matB->tuples_head;

    // create new matrix matC
    sp_tuples * matC = malloc(sizeof(sp_tuples));
    //initiate matrix C with the size mAxnB and nz = 0
    matC->m = matA->m;
    matC->n = matB->n;
    matC->nz = 0;

    // pointer to head, create access to the link list for matC
    //sp_tuples_node *currentC = matC->tuples_head;

    while(currentA != NULL)//FOR every non-zero entry in A 
    { 
        while(currentB != NULL) //FOR every non-zero element in B
        {
            // every element in B where the row is equal to the column of the element in A
            if (currentB->row == currentA->col)
            {
                set_tuples(matC, currentA->row, currentB->col, gv_tuples(matC, currentA->row, currentB->col)+currentA->value*currentB->value);
            }
            currentB = currentB->next; //check next in matB
        }
        currentA = currentA->next; //check next in matA
        // need to reset head pointer for B ?
        currentB = matB->tuples_head; //not sure about this
    }


    return matC;

}

/*
* INPUT: Matrix mat_t
* Iterates through matrix and frees each member,
* then frees the matrix struct as well
* OUTPUT: void
*/
	
void destroy_tuples(sp_tuples * mat_t){
    sp_tuples_node *curr = mat_t->tuples_head;
    sp_tuples_node *temp = NULL;
    while(curr != NULL){
        temp = curr->next;
        free(curr);
        curr = temp;

    }
    free(mat_t);	
    return;
}  






