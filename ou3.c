/*
 * Programmeringsteknik med C och Matlab
 * Fall 15
 * Assignment 3

 * File:         ou3.c
 * Description:  A simple implementation of Conway's Game of Life.
 * Author:       Lukas Sjögren
 * CS username:  tm14lsn
 * Date:         2016-12-20
 * Input:        Choice of initial configuration and then instruction to step
 *               or exit.
 * Output:       Prints the game field in each step.
 * Limitations:  No validation of input.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Constants, representation of states */
#define ALIVE 'X'
#define DEAD '.'
#define ROWS 20
#define COLUMNS 20

/* Declaration of data structure */
typedef struct{
  char current;
  char next;
} cell;

/* Declaration of functions */
void initField(const int rows, const int cols, cell field[rows][cols]);
void loadGlider(const int rows, const int cols, cell field[rows][cols]);
void loadSemaphore(const int rows, const int cols, cell field[rows][cols]);
void loadRandom(const int rows, const int cols, cell field[rows][cols]);
void loadCustom(const int rows, const int cols, cell field[rows][cols]);

void printField(const int rows, const int cols, cell field[rows][cols]);
int menu();
void simulateField(const int rows, const int cols, cell field[rows][cols]);
void updateField(const int rows, const int cols, cell field[rows][cols]);
int countNeighbours(const int rows, const int cols, const int r, const int c ,cell field[rows][cols]);


/* Function:    main
 * Description: Start and run games, interact with the user.
 * Input:       About what initial structure and whether to step or exit.
 * Output:      Information to the user, and the game field in each step.
 */

int main(void) {
    cell field[ROWS][COLUMNS];
    int continueLoop;
    initField(ROWS, COLUMNS, field);
    
    do {
        printField(ROWS, COLUMNS, field);
        continueLoop = menu();
        
        simulateField(ROWS, COLUMNS, field);
        updateField(ROWS, COLUMNS, field);
        
    } while (continueLoop);
    
    return 0;
}


/* Function:    initField
 * Description: Initialize all the cells to dead, then asks the user about
 *              which structure to load, and finally load the structure.
 * Input:       The field array and its size.
 * Output:      The field array is updated.
 */

void initField(const int rows, const int cols, cell field[rows][cols]) {

    for (int r = 0 ; r < rows ; r++) {
        for (int c = 0 ; c < cols ; c++) {
            field[r][c].current = DEAD;
        }
    }

    printf("Select field spec to load ([G]lider, [S]emaphore, [R]andom ");
    printf("or [C]ustom): ");

    int ch = getchar();
    switch (ch) {
        case 'g':
        case 'G':
            loadGlider(rows, cols, field);
            break;
        case 's':
        case 'S':
            loadSemaphore(rows, cols, field);
            break;
        case 'r':
        case 'R':
            loadRandom(rows, cols, field);
            break;
        case 'c':
        case 'C':
        default:
            loadCustom(rows, cols, field);
            break;
    }

    /* Ignore following newline */
    if (ch != '\n') {
        getchar();
    }
}


/* Function:    loadGlider
 * Description: Inserts a glider into the field.
 * Input:       The field array and its size.
 * Output:      The field array is updated.
 */

void loadGlider(const int rows, const int cols, cell field[rows][cols]) {

    field[0][1].current = ALIVE;
    field[1][2].current = ALIVE;
    field[2][0].current = ALIVE;
    field[2][1].current = ALIVE;
    field[2][2].current = ALIVE;
}


/* Function:    loadSemaphore
 * Description: Inserts a semaphore into the field.
 * Input:       The field array and its size.
 * Output:      The field array is updated.
 */

void loadSemaphore(const int rows, const int cols, cell field[rows][cols]) {

    field[8][1].current = ALIVE;
    field[8][2].current = ALIVE;
    field[8][3].current = ALIVE;
}


/* Function:    loadRandom
 * Description: Inserts a random structure into the field.
 * Input:       The field array and its size.
 * Output:      The field array is updated. There is a 50 % chance that a cell
 *              is alive.
 */

void loadRandom(const int rows, const int cols, cell field[rows][cols]) {
    srand(time(NULL));
    for (int i = 0 ; i < rows ; i++){
        for (int j = 0 ; j < cols ; j++){
            if (rand() % 2){
                field[i][j].current = ALIVE;
            }
        }
    }
}


/* Function:    loadCustom
 * Description: Lets the user specify a structure that then is inserted into
 *              the field.
 * Input:       The field array and its size.
 * Output:      The field array is updated.
 */

void loadCustom(const int rows, const int cols, cell field[rows][cols]) {

    printf("Give custom format string: ");
    do {
        int r, c;
        scanf("%d,%d", &r, &c);
        field[r][c].current = ALIVE;
    } while (getchar() != '\n');
}


/* Function:    printField
 * Description: 
 * Input:       
 * Output:      
 */

void printField(const int rows, const int cols, cell field[rows][cols]){
    for (int i ; i < rows ; i++){
        for (int j ; j < cols ; j++){
            if (j == 0) {
                printf("\n%c", field[i][j].current);
            } else {
                printf(" %c", field[i][j].current);
            }
        }
    }
}


/* Function:    menu
 * Description: 
 * Input:       
 * Output:      
 */

int menu(){
    printf("(enter) Step");
    printf("(any) Exit");
    return (getchar() == 14);
}


/* Function:    simulateField
 * Description: 
 * Input:       
 * Output:      
 */

void simulateField(const int rows, const int cols, cell field[rows][cols]){
    
    int neighbourSum;
    for (int r ; r < rows ; r++){
        for (int c ; c < cols ; c++){
            neighbourSum = countNeighbours(rows, cols, r, c, field);
            
            if ( (field[r][c].current == ALIVE) && ( (neighbourSum >= 3) || (neighbourSum <= 1) ) ){
                field[r][c].next = DEAD;
            } else if ( (field[r][c].current == DEAD) && (neighbourSum == 3) ){
                field[r][c].next = ALIVE;
            }
            
            
        }
            
    }
    
    
    
}


/* Function:    updateField
 * Description: 
 * Input:       
 * Output:      
 */

void updateField(const int rows, const int cols, cell field[rows][cols]){
    for (int i ; i < rows ; i++){
        for (int j ; j < cols ; j++){
            field[i][j].current = field[i][j].next;
        }
            
    }
}

int countNeighbours(const int rows, const int cols, const int r, const int c ,cell field[rows][cols]){
    int neighbourSum = 0;
    int rowUpperBound = r + 1;
    int rowLowerBound = r - 1;
    int colUpperBound = c + 1;
    int colLowerBound = c - 1;
    
    if (r >= rows){
        rowUpperBound = rows;
    }
    if (r <= 0){
        rowLowerBound = 0;
    }
    if (c >= cols){
        colUpperBound = cols;
    }
    if (c <= 0){
        colLowerBound = 0;
    }
    
    for (int i = rowLowerBound ; i <= rowUpperBound ; i++){
        for (int j = colLowerBound ; j <= colUpperBound ; j++){
            if ( (field[i][j].current == ALIVE) && (i != r ) &&( j != c) ){
                neighbourSum++;
            }
        }
    }
    return neighbourSum;
}