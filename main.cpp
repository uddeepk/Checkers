using namespace std;
#include <iostream>
#include <vector>
#include <string>
void displayErrMsg() {
    cout << "Please press enter to continue!" <<endl;
    cin.clear(); //clears error flag on cin
    cin.ignore(1000,'\n'); //ignores 1000 characters until \n character
    string temp;
    getline(cin , temp);
}


#include "CheckersPiece.h"
#include "CheckersBoard.h"

int main() {
    // Create board and place pieces
    // Better to create the pointers here or from the CheckersBoard.h ?
    auto board = getBoard() ;
    //displayBoard(board);
    int n = 0; //move counter. also denote whose move.
    //Loop while win condition not fulfilled i.e (one color piece left or player unable to move their piece)
    vector <vector<int>> jumpSources ;
    //cout << !checkLoss( board , n, jumpSources) << endl;
    while ( !checkLoss( board , n, jumpSources) ) { //maybe I can combine them ?
        displayBoard(board); // Display board
        cout << whoseTurn ( n ) << " moves " << endl; // notice that I can call the method listed in board. Is this ok ?
        int sourceRow, sourceRowInput, sourceColumn, destinationRow, destinationRowInput, destinationColumn;
        char sourceColumnLetter, destinationColumnLetter;
        //Take input as position of source piece
        cout << "Enter position of piece you want to move, and destination ( eg. a 2 b 3) :" <<endl;
        if ( (cin >> sourceColumnLetter>>  sourceRowInput  >> destinationColumnLetter >> destinationRowInput )  &&
        checkValidMove( n , board , 8-sourceRowInput , sourceColumnLetter-'a', 8-destinationRowInput, destinationColumnLetter-'a' )) {
            // Fine
        }
        else {
            cout << "Please enter proper input!" <<endl;
            displayErrMsg();
            continue;
        }
        sourceRow = 8-sourceRowInput;
        destinationRow = 8 - destinationRowInput;
        sourceColumn = sourceColumnLetter - 'a';
        destinationColumn = destinationColumnLetter-'a';
        // Jumps are priority, and mandatory
        CheckersPiece *selectedPiece = board[sourceRow][sourceColumn]; //how to use ?
        if (!jumpSources.empty() ) {

            if(jumpsAvailable( board , n , board[sourceRow][sourceColumn])) { //Inefficient ?
                int jumps = 0;
                while ( jumpsAvailable( board, n , board[sourceRow][sourceColumn] ) ) {
                    if(jumps >0) {
                        //cout << "Successful Jump!" <<endl;
                        displayBoard(board);
                        cout <<"Now only enter the destination for your piece " ;
                        char dL ='a'+board[sourceRow][sourceColumn]->column;
                        cout << dL << 8-board[sourceRow][sourceColumn]->row <<endl;
                        while(!(cin>> destinationColumnLetter >> destinationRowInput )) {
                            cout <<"Enter proper position!" << endl;
                            char dL ='a'+board[sourceRow][sourceColumn]->column;
                            cout << "Enter where to move the piece at " << dL <<  " " <<  8-board[sourceRow][sourceColumn]->row
                                 << " : " <<endl;
                            displayErrMsg();
                        }
                        destinationRow = 8-destinationRowInput;
                        destinationColumn = destinationColumnLetter-'a';
                    }
                    if (board[sourceRow][sourceColumn]->isJump(destinationRow, destinationColumn, board)) {
                        // move;
                        jumpPiece( board , board[sourceRow][sourceColumn] , destinationRow, destinationColumn);
                        // update piece with move/ jump
                        sourceRow = destinationRow;
                        sourceColumn = destinationColumn;
                        jumps++;
                    }
                    else {
                        cout << "Enter proper jump destination for your piece" << endl;
                        displayErrMsg();
                        displayBoard(board);
                        char dL ='a'+board[sourceRow][sourceColumn]->column;
                        cout << "Enter where to move the piece at " << dL <<  " " <<  8-board[sourceRow][sourceColumn]->row
                        << " : " <<endl;
                        while(!(cin>> destinationColumnLetter >> destinationRowInput )) {
                            cout <<"Enter proper position!" << endl;
                            char dL ='a'+board[sourceRow][sourceColumn]->column;
                            cout << "Enter where to move the piece at " << dL <<  " " <<  8-board[sourceRow][sourceColumn]->row
                                 << " : " <<endl;
                            displayErrMsg();
                        }
                        destinationRow = 8-destinationRowInput;
                        destinationColumn = destinationColumnLetter-'a';
                    }


                }
                //jumpSources.clear() ; // clears vector
            }
            else {
                cout <<"Select one of the pieces with jump available" <<endl;
                //Print the pieces with jump available from vector jumpSources
                for(auto i: jumpSources) {
                    char dL = 'a'+i[1];
                    cout << dL << " " << 8-i[0] <<endl;
                }
                displayErrMsg();
                continue;
            }

        }
        else if ( board[sourceRow][sourceColumn] != nullptr && board[sourceRow][sourceColumn]->isMove(destinationRow, destinationColumn , board)) {
            movePiece (board , board[sourceRow][sourceColumn] , destinationRow, destinationColumn);
        }
        else {
            displayErrMsg();
            continue;
        }
        // Can only move one piece at a time, even when jumps available for multiple pieces.

        //
        n++;
    }


    return 0;
}
