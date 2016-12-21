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
int queryContinue();
void simulateField(const int rows, const int cols, cell field[rows][cols]);
void updateField(const int rows, const int cols, cell field[rows][cols]);
int countNeighbours(const int rows, const int cols, const int r, const int c ,cell field[rows][cols]);


/* Function:    main
 * Description: Start and run games, interact with the user.
 * Input:       About what initial structure and whether to step or exit.
 * Output:      Information to the user, and the game field in each step.
 */

int main(void) {
    cell field[ROWS][COLUMNS];          //Decleare variable for field with dimensions defined by ROWS and COLUMNS.
    initField(ROWS, COLUMNS, field);    //Initiate and populate field according to user choice
    
    do {    //Loop program while user wishes to continue simulate.
        printField(ROWS, COLUMNS, field);       //Print field to user.
        simulateField(ROWS, COLUMNS, field);    //Simulate the cells for one generation
        updateField(ROWS, COLUMNS, field);      //Update state from future generation to be current generation.
    } while ( queryContinue() );    //Ask the user if another generation should be simulated. Enter key for continue, exit with any other key.
    
    return 0;   //End of program.
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
    srand(time(NULL));      //Seed the random number generator.
    for (int r = 0 ; r < rows ; r++){       //Interates through all cells in field with nested for-loops.
        for (int c = 0 ; c < cols ; c++){
            if ( rand() % 2) {                  //Get binary random state (1 or 0)
                field[r][c].current = ALIVE;    //Set cell as alive if 1.
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
 * Description: Displays the passed field to user via terminal.
 * Input:       The field array and its size.
 * Output:      None
 */

void printField(const int rows, const int cols, cell field[rows][cols]){
    
    for (int r = 0; r < rows ; r++){        //Interates through all cells in field with nested for-loops.
        for (int c = 0 ; c < cols ; c++){
            
            if (c == (cols-1)) {                        //If printing has reached the rightmost egde of a line, print the state of the cell and a newline.   
                printf("%c\n", field[r][c].current);
            } else {                                    //Otherwise print the state of the cell and a space.,
                printf("%c ", field[r][c].current);
            }
        }
    }
}


/* Function:    queryContinue
 * Description: Queries user as to if another generation of 
 *              game of life should be compited and displayed.
 *              Continue if keypress is enter, otherwise exit.
 * Input:       None
 * Output:      Integer functioning as boolean.
 */

int queryContinue(){
    printf("Select one of the following options:\n");
    printf("(enter) Step\n");
    printf("(any) Exit\n");
    return (getchar() == '\n');
}


/* Function:    simulateField
 * Description: Simulates one generation of game of life from state of 
 *              field[][].current and writes result to field[][].next
 * Input:       The field array and its size.
 * Output:      The field array is updated.
 */

void simulateField(const int rows, const int cols, cell field[rows][cols]){
    
    for (int r = 0; r < rows ; r++){        //Interates through all cells in field with nested for-loops.
        for (int c = 0; c < cols ; c++){
            
            
            if (field[r][c].current == ALIVE) {                                 //If the current cell is alive and...
                if (countNeighbours(rows, cols, r, c, field) >= 4) {            //If it has 4 or more neighbours, kill it in the next generation.
                    field[r][c].next = DEAD;
                } else if ( countNeighbours(rows, cols, r, c, field) <= 1 ){    //If it has 1 or 0 neighbours, kill it in the next generation.
                    field[r][c].next = DEAD;
                } else {                                                        //Otherwise let it live
                    field[r][c].next = ALIVE;
                }
            
            } else if (field[r][c].current == DEAD) {                           //If the current cell is dead and...
                if ( countNeighbours(rows, cols, r, c, field) == 3) {           //If it has exactly 3 neighbours, resurrect it in the next generation.
                    field[r][c].next = ALIVE;
                } else {                                                        //Otherwise leave it dead.
                    field[r][c].next = DEAD;
                }
            }
        }
            
    }
    
    
    
}


/* Function:    updateField
 * Description: Updates field[][].current with state from field[][].next
 * Input:       The field array and its size.
 * Output:      The field array is updated.
 */

void updateField(const int rows, const int cols, cell field[rows][cols]){
    for (int r = 0; r < rows ; r++){        //Interates through all cells in field with nested for-loops.
        for (int c = 0; c < cols ; c++){
                                                    //Applies the state from field[r][c].next to field[r][c].current
            if (field[r][c].next == ALIVE) {        //(Used IFs due to repeated segfaults in directly assigning next to current.)
                field[r][c].current = ALIVE;
            } else if (field[r][c].next == DEAD) {
                field[r][c].current = DEAD;
            }
        }
            
    }
}

/* Function:    countNeighbours
 * Description: Calculates the number of alive neighbours of a single cell.
 * Input:       The field array, its size and location of a single cell.
 * Output:      The number of alive neighbours of passed cell.
 */

int countNeighbours(const int rows, const int cols, const int r, const int c ,cell field[rows][cols]){
    int neighbourSum = 0;       //Number of neighbours
    
    int rowUpperBound = r + 1;  //The Bounds variables defines the sides of a 3x3 square 
    int rowLowerBound = r - 1;  //centered on the passed cell containing all adjacent cells.
    int colUpperBound = c + 1;
    int colLowerBound = c - 1;
    
    if (r >= ( rows - 1 ) ) {   //If the square is completly or partially outside the field bounderies,
        rowUpperBound = rows-1; //decrease the square to a rectangle as to be contained in the field.
    }                           //This is done for all four Bounds.
    if (r <= 0){
        rowLowerBound = 0;
    }
    if (c >= ( cols - 1 ) ) {
        colUpperBound = cols-1;
    }
    if (c <= 0){
        colLowerBound = 0;
    }
    
    for (int i = rowLowerBound ; i <= rowUpperBound ; i++){         //Iterate through all cells in the square (or rectangle) with nested for-loops defined by the Bounds-variables.
        for (int j = colLowerBound ; j <= colUpperBound ; j++){
            if ( (field[i][j].current == ALIVE) && ( (i != r ) || ( j != c) ) ){    //If a cell in the square is alive and not the central cell that is examined,
                neighbourSum++;                                                     //Increment the number of neighbours by one.
            }
        }
    }
    return neighbourSum;    //Return number of neighbours.
}