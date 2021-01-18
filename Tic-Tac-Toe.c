#include <stdio.h> 

void InitializeBoard(int m, int n, char board[][n]);    

void PrintBoard(int m, int n, char board[][n]);     

void CreateBoard(int m, int n, char board[][n]);    

int IsValidBoard(int m, int n, char board[][n]);   

void ListWinningCells(int m, int n, char board[][n]);    
/*NOTE:
For this function, I used a bunch of if statements for every case
since it was never specified on the method to program the function,
there's probably a better way to do it, but I couldn't think of 
another way and this way still works.
*/ 

char WhoIsWinner(int m, int n, char board[3][3]);    
/*NOTE:
This function was implimented in a way where if the game is won, 
then the game will end automatically. It was never specified on
how this function should be inserted into main, so I chose to
do it like that.
*/

int main (void) {

    int rows=3;
    int columns=3;  
    char board[3][3];
    char Player_Menu_Option;

    InitializeBoard(rows, columns, board);

    do {
        /*Menu Display*/
        puts("press 'p' to print the tic-tac-toe board");
        puts("press 'c' to create a tic-tac-toe board with some X and O cells");
        puts("press 't' to test if a tic-tac-toe board is valid or invalid board");
        puts("press 'w' to predict winning cell for player X or O");
        puts("press 'e' to Exit");
        puts("press 'W' for check for a winner"); //Added this option to check if anyone won, since it was never specified in the assignment on how to impliment the WhoIsWinner function into the menu or game overall 

        scanf(" %c", &Player_Menu_Option);

        if (Player_Menu_Option == 'e') {
            break;
        }
        
        else {

            switch(Player_Menu_Option) {
    
                case 'p':   PrintBoard(rows, columns, board);
                            break;

                case 'c':   CreateBoard(rows, columns, board);
                            break;

                case 't':   
                            if (IsValidBoard(rows, columns, board) == 1) {
                                puts("");
                                puts("Board is valid");
                                puts("");
                            }
                            else {
                                puts("");
                                puts("Board is invalid");
                                puts("");
                            }
                            break;

                case 'w':   puts("");
                            ListWinningCells(rows, columns, board);
                            puts("");
                            break;

                default:    puts("You have entered an invalid option, please try again");
                            break;  
            }
        }

        /*It will check if there is a winner after every time the player does anything*/

        if (WhoIsWinner(2,2,board) == 'D') {    //If there is no winner, the function returns 'D', in this case nothing extra happens

        }
        else {  //Else, there is a winner, and it will print that 
            puts("\n");
            printf("Player %c is the winner!\n", WhoIsWinner(2, 2, board));
            PrintBoard(rows, columns, board);   //This will print the board so the player can see how they won
            break;  //and then the program breaks out of the while loop to end the game 
        }  

    } while(1);
} 

void InitializeBoard(int m, int n, char board[][n]) {             
    int c =1;                                                       
    for (int i = 0; i<m; i++) {
        for (int j=0; j<n; j++) {
            board[i][j] = c+'0';                                                
            c++;
        }
    }
/*
Initializes the following board

     |     |     
  1  |  2  |  3  
_____|_____|_____
     |     |     
  4  |  5  |  6   
_____|_____|_____
     |     |  
  7  |  8  |  9  
     |     |

*/
}

void PrintBoard(int m, int n, char board[][n]) {    

    int i;

    puts("");

    puts("     |     |     ");
    for (i=0; i<n; i++) {

        if (i == n-1) {
            printf("  %c   \n", board[0][i]);
        }
        else {
            printf("  %c  |", board[0][i]);
        }
    }
    puts("_____|_____|_____");
    puts("     |     |     ");

    for (i=0; i<n; i++) {

        if (i == n-1) {
            printf("  %c   \n", board[1][i]);
        }
        else {
        printf("  %c  |", board[1][i]);
        }
    }
    puts("_____|_____|_____");
    puts("     |     |     ");

    for (i=0; i<n; i++) {

        if (i == n-1) {
            printf("  %c   \n", board[2][i]);
        }
        else {
        printf("  %c  |", board[2][i]);
        }
    }
    puts("     |     |     \n");
}

void CreateBoard(int m, int n, char board[][n]) {   

    char Cell_Input;    //For the input from the player of their cell selection
    char XO_Input = 0;     //For the input of X or O from the player

    puts("Enter the number of the cell where you want to insert X or O, or enter 'E' to exit");
    do {
        scanf(" %c", &Cell_Input);

        if ( (Cell_Input > '9' && Cell_Input < '0') && (Cell_Input != 'E') ) { //Fail safe in case they don't type a character in range of 1-9
           puts("You have entered an invalid space, please try again (between 1-9");
           continue;
        }
        else {
            break;
        }
    } while (1);

    if (Cell_Input == 'E') {    //If they entered 'E', then exits out of the function
        return;
    }

    puts("Type X or O");
    do {
        scanf(" %c", &XO_Input);

        if (XO_Input != 88) {  //Fail safe in case player doesn't type X or O 
            if (XO_Input != 79) {   //ASCII: 'X' = 88 , 'O' = 79 (for reference)
                puts("You have entered an invalid character, please enter either X or O");
                continue;
            }
            else {
                break;
            }
        }
        else { 
            break;
        }
    } while(1);

    //This part inserts either X or O into the slot the player choses
    for (int i=0; i<m; i++) {  
        for (int j=0; j<n; j++) {

            if (board[i][j] == Cell_Input) {
                board[i][j] = XO_Input;
            }
        }
    }
}
    
int IsValidBoard(int m, int n, char board[][n]) {  

    int Number_of_X = 0; //Used to count the # of X's on board
    int Number_of_O = 0; //Used to count the # of O's on board
    int Validity_Check = 0; //Used to check the validity of the board based on the previous two variables

    for (int i=0;i<m;i++) { //Nested loops through every element in the board
        for (int j=0; j<n;j++) {

            if (board[i][j] == 'X') {   //If the particular element is an X, it will increase it's count
                Number_of_X++;
            }
            if (board[i][j] == 'O') {   //If the particular element is an O, it will increase it's count
                Number_of_O++;
            }
        }
    }

    if (Number_of_X > Number_of_O) {
        Validity_Check = Number_of_X - Number_of_O;
    }

    if (Number_of_O > Number_of_X) {
        Validity_Check = Number_of_O - Number_of_X;
    }

    if (Validity_Check > 1) {
        //Board is not valid
        return 0;
    }
    else {
        //Board is valid
        return 1;
    }
}

    
void ListWinningCells(int m, int n, char board[][n]) {

    int MessageCheck = 0; //Checks if there was a possible win message printed, if so, will not print "no winning cells"

    //Column 1 for O's
    if (board[0][0] == 'O') {
        if (board[1][0] == 'O') {
            if (board[2][0] == 'X') {
            }
            else {
                puts("Cell 7 is a winning cell for player O");
                MessageCheck++;
            }  
        }
    }
    if (board[0][0] == 'O') {
        if (board[2][0] == 'O') {
            if (board[1][0] == 'X') {
            }
            else {
                puts("Cell 4 is a winning cell for player O");
                MessageCheck++;
            }
        }
    }
    if (board[1][0] == 'O') {
        if (board[2][0] == 'O') {
            if (board[0][0] == 'X') {
            }
            else {
                puts("Cell 1 is a winning cell for player O");
                MessageCheck++;
            }
        }
    }

    //Column 1 for X's
    if (board[0][0] == 'X') {
        if (board[1][0] == 'X') {
            if (board[2][0] == 'O') {
            }
            else {
                puts("Cell 7 is a winning cell for player X");
                MessageCheck++;
            }  
        }
    }
    if (board[0][0] == 'X') {
        if (board[2][0] == 'X') {
            if (board[1][0] == 'O') {
            }
            else {
                puts("Cell 4 is a winning cell for player X");
                MessageCheck++;
            }
        }
    }
    if (board[1][0] == 'X') {
        if (board[2][0] == 'X') {
            if (board[0][0] == 'O') {
            }
            else {
                puts("Cell 1 is a winning cell for player X");
                MessageCheck++;
            }
        }
    }


    //Column 2 for O's
    if (board[0][1] == 'O') {
        if (board[1][1] == 'O') {
            if (board[2][1] == 'X') {
            }
            else {
                puts("Cell 8 is a winning cell for player O");
                MessageCheck++;
            }  
        }
    }
    if (board[0][1] == 'O') {
        if (board[2][1] == 'O') {
            if (board[1][1] == 'X') {
            }
            else {
                puts("Cell 5 is a winning cell for player O");
                MessageCheck++;
            }
        }
    }
    if (board[1][1] == 'O') {
        if (board[2][1] == 'O') {
            if (board[0][1] == 'X') {
            }
            else {
                puts("Cell 2 is a winning cell for player O");
                MessageCheck++;
            }
        }
    }

    //Column 2 for X's
    if (board[0][1] == 'X') {
        if (board[1][1] == 'X') {
            if (board[2][1] == 'O') {
            }
            else {
                puts("Cell 8 is a winning cell for player X");
                MessageCheck++;
            }  
        }
    }
    if (board[0][1] == 'X') {
        if (board[2][1] == 'X') {
            if (board[1][1] == 'O') {
            }
            else {
                puts("Cell 5 is a winning cell for player X");
                MessageCheck++;
            }
        }
    }
    if (board[1][1] == 'X') {
        if (board[2][1] == 'X') {
            if (board[0][1] == 'O') {
            }
            else {
                puts("Cell 2 is a winning cell for player X");
                MessageCheck++;
            }
        }
    }

    //Column 3 for O's
    if (board[0][2] == 'O') {
        if (board[1][2] == 'O') {
            if (board[2][2] == 'X') {
            }
            else {
                puts("Cell 9 is a winning cell for player O");
                MessageCheck++;
            }  
        }
    }
    if (board[0][2] == 'O') {
        if (board[2][2] == 'O') {
            if (board[1][2] == 'X') {
            }
            else {
                puts("Cell 6 is a winning cell for player O");
                MessageCheck++;
            }
        }
    }
    if (board[1][2] == 'O') {
        if (board[2][2] == 'O') {
            if (board[0][2] == 'X') {
            }
            else {
                puts("Cell 3 is a winning cell for player O");
                MessageCheck++;
            }
        }
    }

    //Column 3 for X's
    if (board[0][2] == 'X') {
        if (board[1][2] == 'X') {
            if (board[2][2] == 'O') {
            }
            else {
                puts("Cell 9 is a winning cell for player X");
                MessageCheck++;
            }  
        }
    }
    if (board[0][2] == 'X') {
        if (board[2][2] == 'X') {
            if (board[1][2] == 'O') {
            }
            else {
                puts("Cell 6 is a winning cell for player X");
                MessageCheck++;
            }
        }
    }
    if (board[1][2] == 'X') {
        if (board[2][2] == 'X') {
            if (board[0][2] == 'O') {
            }
            else {
                puts("Cell 3 is a winning cell for player X");
                MessageCheck++;
            }
        }
    }

    //Row 1 for O's 
    if (board[0][0] == 'O') {
        if (board[0][1] == 'O') {
            if (board[0][2] == 'X') {
            }
            else {
                puts("Cell 3 is a winning cell for player O");
                MessageCheck++;
            }  
        }
    }
    if (board[0][1] == 'O') {
        if (board[0][2] == 'O') {
            if (board[0][0] == 'X') {
            }
            else {
                puts("Cell 1 is a winning cell for player O");
                MessageCheck++;
            }
        }
    }
    if (board[0][0] == 'O') {
        if (board[0][2] == 'O') {
            if (board[0][1] == 'X') {
            }
            else {
                puts("Cell 2 is a winning cell for player O");
                MessageCheck++;
            }
        }
    }

    //Row 1 for X's
    if (board[0][0] == 'X') {
        if (board[0][1] == 'X') {
            if (board[0][2] == 'O') {
            }
            else {
                puts("Cell 3 is a winning cell for player X");
                MessageCheck++;
            }  
        }
    }
    if (board[0][1] == 'X') {
        if (board[0][2] == 'X') {
            if (board[0][0] == 'O') {
            }
            else {
                puts("Cell 1 is a winning cell for player X");
                MessageCheck++;
            }
        }
    }
    if (board[0][0] == 'X') {
        if (board[0][2] == 'X') {
            if (board[0][1] == 'O') {
            }
            else {
                puts("Cell 2 is a winning cell for player X");
                MessageCheck++;
            }
        }
    }

    //Row 2 for O's
    if (board[1][0] == 'O') {
        if (board[1][1] == 'O') {
            if (board[1][2] == 'X') {
            }
            else {
                puts("Cell 6 is a winning cell for player O");
                MessageCheck++;
            }  
        }
    }
    if (board[1][1] == 'O') {
        if (board[1][2] == 'O') {
            if (board[1][0] == 'X') {
            }
            else {
                puts("Cell 4 is a winning cell for player O");
                MessageCheck++;
            }
        }
    }
    if (board[1][0] == 'O') {
        if (board[1][2] == 'O') {
            if (board[1][1] == 'X') {
            }
            else {
                puts("Cell 5 is a winning cell for player O");
                MessageCheck++;
            }
        }
    }

    //Row 2 for X's
    if (board[1][0] == 'X') {
        if (board[1][1] == 'X') {
            if (board[1][2] == 'O') {
            }
            else {
                puts("Cell 6 is a winning cell for player X");
                MessageCheck++;
            }  
        }
    }
    if (board[1][1] == 'X') {
        if (board[1][2] == 'X') {
            if (board[1][0] == 'O') {
            }
            else {
                puts("Cell 4 is a winning cell for player X");
                MessageCheck++;
            }
        }
    }
    if (board[1][0] == 'X') {
        if (board[1][2] == 'X') {
            if (board[1][1] == 'O') {
            }
            else {
                puts("Cell 5 is a winning cell for player X");
                MessageCheck++;
            }
        }
    }

    //Row 3 for O's
    if (board[2][0] == 'O') {
        if (board[2][1] == 'O') {
            if (board[2][2] == 'X') {
            }
            else {
                puts("Cell 9 is a winning cell for player O");
                MessageCheck++;
            }  
        }
    }
    if (board[2][1] == 'O') {
        if (board[2][2] == 'O') {
            if (board[2][0] == 'X') {
            }
            else {
                puts("Cell 7 is a winning cell for player O");
                MessageCheck++;
            }
        }
    }
    if (board[2][0] == 'O') {
        if (board[2][2] == 'O') {
            if (board[2][1] == 'X') {
            }
            else {
                puts("Cell 8 is a winning cell for player O");
                MessageCheck++;
            }
        }
    }

    //Row 3 for X's 
    if (board[2][0] == 'X') {
        if (board[2][1] == 'X') {
            if (board[2][2] == 'O') {
            }
            else {
                puts("Cell 9 is a winning cell for player X");
                MessageCheck++;
            }  
        }
    }
    if (board[2][1] == 'X') {
        if (board[2][2] == 'X') {
            if (board[2][0] == 'O') {
            }
            else {
                puts("Cell 7 is a winning cell for player X");
                MessageCheck++;
            }
        }
    }
    if (board[2][0] == 'X') {
        if (board[2][2] == 'X') {
            if (board[2][1] == 'O') {
            }
            else {
                puts("Cell 8 is a winning cell for player X");
                MessageCheck++;
            }
        }
    }

    //Diagonal 1 (left to right) for O's
    if (board[0][0] == 'O') {
        if (board[1][1] == 'O') {
            if (board[2][2] == 'X') {
            }
            else {
                puts("Cell 9 is a winning cell for player O");
                MessageCheck++;
            }  
        }
    }
    if (board[1][1] == 'O') {
        if (board[2][2] == 'O') {
            if (board[0][0] == 'X') {
            }
            else {
                puts("Cell 1 is a winning cell for player O");
                MessageCheck++;
            }
        }
    }
    if (board[0][0] == 'O') {
        if (board[2][2] == 'O') {
            if (board[1][1] == 'X') {
            }
            else {
                puts("Cell 5 is a winning cell for player O");
                MessageCheck++;
            }
        }
    }

    //Diagonal 1 (left to right) for X's
    if (board[0][0] == 'X') {
        if (board[1][1] == 'X') {
            if (board[2][2] == 'O') {
            }
            else {
                puts("Cell 9 is a winning cell for player X");
                MessageCheck++;
            }  
        }
    }
    if (board[1][1] == 'X') {
        if (board[2][2] == 'X') {
            if (board[0][0] == 'O') {
            }
            else {
                puts("Cell 1 is a winning cell for player X");
                MessageCheck++;
            }
        }
    }
    if (board[0][0] == 'X') {
        if (board[2][2] == 'X') {
            if (board[1][1] == 'O') {
            }
            else {
                puts("Cell 5 is a winning cell for player X");
                MessageCheck++;
            }
        }
    }

    //Diagonal 2 (right to left) for O's
    if (board[0][2] == 'O') {
        if (board[1][1] == 'O') {
            if (board[2][0] == 'X') {
            }
            else {
                puts("Cell 7 is a winning cell for player O");
                MessageCheck++;
            }  
        }
    }
    if (board[2][0] == 'O') {
        if (board[1][1] == 'O') {
            if (board[0][2] == 'X') {
            }
            else {
                puts("Cell 3 is a winning cell for player O");
                MessageCheck++;
            }
        }
    }
    if (board[2][0] == 'O') {
        if (board[0][2] == 'O') {
            if (board[1][1] == 'X') {
            }
            else {
                puts("Cell 5 is a winning cell for player O");
                MessageCheck++;
            }
        }
    }

    //Diagonal 2 (right to left) for X's
    if (board[0][2] == 'X') {
        if (board[1][1] == 'X') {
            if (board[2][0] == 'O') {
            }
            else {
                puts("Cell 7 is a winning cell for player X");
                MessageCheck++;
            }  
        }
    }
    if (board[2][0] == 'X') {
        if (board[1][1] == 'X') {
            if (board[0][2] == 'O') {
            }
            else {
                puts("Cell 3 is a winning cell for player X");
                MessageCheck++;
            }
        }
    }
    if (board[2][0] == 'X') {
        if (board[0][2] == 'X') {
            if (board[1][1] == 'O') {
            }
            else {
                puts("Cell 5 is a winning cell for player X");
                MessageCheck++;
            }
        }
    }

    if (MessageCheck == 0) {        //If no winning messages were printed, this if statement will run
        puts("No winning cells");
    }
}

char WhoIsWinner(int m, int n, char board[3][3]) { 

    if ( (m >= 0) && (n >= 0) ) { //If n and m are equal to -1, then there is no winner 
    
        if( (board[m][0] == board[m][1]) && (board[m][0] == board[m][2]) ) {    //Checks rows
            return board[m][0];
        }
        else if ( (board[0][n] == board[1][n]) && (board[0][n] == board[2][n]) ){   //Checks columns
            return board[0][n];
        }
        else if ( (board[0][0] == board[1][1]) && (board[0][0] == board[2][2]) ) {  //Checks Diagonal (left to right)
            return board[0][0]; 
        }
        else if ( (board[0][2] == board[1][1]) && (board[0][2] == board[2][0]) ) {  //Checks Diagonal (right to left)
            return board[0][2]; 
        }
        else {
            return WhoIsWinner(m-1,n-1,board);  //If nothing checks out, will run through with m-1 and n-1 
        }
    }
    else {
        return 'D';
    }

}