//
// Created by uddeepk on 12/3/20.
//

#ifndef CHECKERS_OBJ_CHECKERSPIECE_H
#define CHECKERS_OBJ_CHECKERSPIECE_H
#include <string>

class CheckersPiece {
    //The data for the particular checkers piece
    public:
        int row;
        int column;
        bool king;
        std::string color;
        CheckersPiece(int r , int c , int clr);
        char displayPiece ();
        //char displayPiece(void);
        bool isJump(int rD, int cD , vector<vector<CheckersPiece*>> b);
        bool isMove(int rD, int cD , vector<vector<CheckersPiece*>> b);
        void place(int r , int c);
        void move() {
            // Is king or not ? because kings can move in any direction

            // Color I

            //
        }
    };
    CheckersPiece::CheckersPiece(int r , int c , int clr) {
        //Constructor to initiate a CheckersPiece
        row = r;
        column = c;
        switch (clr) { //Uses the value from the board array
            case 1:
                color = "Black";
                break;
            case -1:
                color = "White";
                break;
            default:
                break;
        }
        king = false;
    }
    //Display method for piece
    char CheckersPiece::displayPiece () {
        return (king ? color[0] : color[0] + 32);
    }
    bool CheckersPiece::isJump(int rD, int cD , vector<vector<CheckersPiece* > > b) {
        if( rD >= 0 && cD>= 0 && rD<b.size() && cD <b[0].size()) {
            if(b[rD][cD] != nullptr) { // is not empty
                return false;
            }
            int rM = rD - row;
            int cM = cD - column;
            if( king) {
                // can move any diagonal direction
                if(( abs(rM) == 2 && abs(cM) == 2) &&
                ( b [row + rM/2][column + cM/2] !=nullptr)) {
                    return (b [row + rM/2][column + cM/2]  -> color != color); //can't jump over own color
                }

            }
            else {
                if (color == "Black") {
                    if(rM == -2 && abs(cM) == 2 && b[row+rM/2][column + cM/2] != nullptr) {
                        return b [row + rM/2][column + cM/2]->color != color;
                    }
                }
                else {  // color = "White"
                    if(rM == 2 && abs(cM) == 2 && b[row+rM/2][column + cM/2] != nullptr) {
                        return b [row + rM/2][column + cM/2]->color != color;
                    }
                }
            }
        }
        return false;

    }
    bool CheckersPiece::isMove(int rD, int cD , vector<vector<CheckersPiece*>> b) {
        //check if coordinates are good.
        if( rD >= 0 && cD>= 0 && rD<b.size() && cD <b[0].size()) {
            if (b[rD][cD] != nullptr) { // is not empty
                return false;
            }
            int rM = rD - row;
            int cM = cD - column;
            if(king) { // KIngs move any diagonal dir.
                return (abs(rM )== 1 && abs(cM) == 1);
            }
            else {
                if (color == "Black") {
                    return (rM == -1 && abs(cM) == 1);
                } else { // color == "White"
                    return (rM == 1 && abs(cM) == 1);
                }
            }
        }
        return false;
    }
    //Methods for moving the checkers piece or just check for valid moves ??
    void CheckersPiece::place(int r , int c) {
        row = r;
        column = c;
        if (( color == "Black" && row == 0) || (color == "White" && row == 7)) {
            king = true;
        }
    }


#endif //CHECKERS_OBJ_CHECKERSPIECE_H
