//
// Created by uddeepk on 12/3/20.
//

#ifndef CHECKERS_OBJ_CHECKERSBOARD_H
#define CHECKERS_OBJ_CHECKERSBOARD_H



//This creates to create an 2D array or vector of pointers of Checkers Pieces

//Each element pointer will either


// This method creates a new board, and returns it to the main method
// It does so by returning a 8x8 vector of pointers for CheckerPiece
// objs are initialized and set to pointers
// the empty spaces are init as nullptr

vector <vector<CheckersPiece *>> getBoard () {
    // Declaring an vector of empty pointers to keep the checkers objects.
    vector <vector < CheckersPiece * >> b;
    vector<vector <int>> t = {  //This was an easy way
        {  0, -1,  0, -1,  0, -1,  0, -1},
        { -1,  0, -1,  0, -1,  0, -1,  0},
        {  0, -1,  0, -1,  0, -1,  0, -1},
        {  0,  0,  0,  0,  0,  0,  0,  0},
        {  0,  0,  0,  0,  0,  0,  0,  0},
        {  1,  0,  1,  0,  1,  0,  1,  0},
        {  0,  1,  0,  1,  0,  1,  0,  1},
        {  1,  0,  1,  0,  1,  0,  1,  0}

    };

    for ( int i = 0 ; i < 8 ; ++i ) {
        vector < CheckersPiece*> temp;
        for ( int j = 0; j < 8 ; ++j) {
            switch (t[i][j]) {
                case -1:
                    temp.push_back( new CheckersPiece(i ,j, -1));
                    break;
                case 1:
                    temp.push_back( new CheckersPiece(i, j, 1));
                    break;
                default:
                    temp.push_back(nullptr);
                    break;
            }

        }
        b.push_back(temp);
    }
    return b;
}

// Method to display the board
void displayBoard( vector<vector<CheckersPiece *>> b) {
    cout<<endl;
    cout << " _________________________________" << endl;
    for(int i=0; i<8 ; i++) {

        cout<<" | ";
        for(int j = 0; j< 8; j++) {
            char c ;
            if(b[i][j] == nullptr) {
                c = ' ';
            }
            else {
                c = b[i][j]->displayPiece();
            }
            cout << c << " | " ;
        }
        cout<<"\n" << 8 - i<< "|";
        for(int j = 0 ; j < 8 ; j++) {
            cout<<"___|";
        }
        cout<<endl;
    }
    cout<<" ";
    for ( int j = 0 ; j<8 ;j++){
        char colon = 'a'+j;
        cout << "  " << colon << " " ;
    }
    cout <<endl;
}
string whoseTurn ( int n) {
    return ((n % 2 == 0) ? "Black" : "White" ) ;
}
bool checkMovesAvailable( CheckersPiece* cp , vector <vector<CheckersPiece*>> b ,vector<vector<int>> &jS) {
    int movesAvailable = 0;
    int jumpsAvailable = 0;
    vector <vector<int>> allPossibleMoves = {
            {1,  1},
            {1,  -1},
            {-1, 1},
            {-1, -1}
    },
            allPossibleJumps = { {2,2} , {2, -2} , {-2,2} , {-2, -2}
    };
    for(auto i: allPossibleJumps) {

        if(cp->isJump( cp->row+i[0] , cp->column+ i[1] , b) ) {

            jumpsAvailable++; //pieces with jumps available ; also maybe i can use boolean instead

            //jS.push_back(cp->rowi);

        }

    }
    for(auto i: allPossibleMoves) {

        if(cp->isMove( cp->row+i[0] , cp->column+ i[1] , b)) {

            movesAvailable++;
        }
    }
    if(jumpsAvailable>0)
        jS.push_back( { cp->row , cp->column});

    return (jumpsAvailable > 0 || movesAvailable > 0);
}
bool checkLoss ( vector<vector<CheckersPiece*>> b ,int n ,vector<vector<int>> &jS) {
    jS.clear();
    int pieces = 0;
    int movesAvailable = 0;
    for( auto i : b ) {
        for ( auto j: i) {
            if( j!= nullptr) {
                if( j->color == whoseTurn(n)) {

                    pieces++;

                    if (checkMovesAvailable(j , b , jS)) {
                        movesAvailable++;
                    }
                }
            }
        }
    }
    return (pieces == 0 || movesAvailable==0);
}
bool checkValidMove (int n , vector<vector<CheckersPiece *>> b , int rS , int cS , int rD, int cD) {
    if(rS >= 0 && rS<b.size() && cS>=0 &&cS< b[0].size() && rD>=0 && rD<b.size() && cD>=0 && cD<b[0].size()) {
        if (b[rS][cS] == nullptr) {
            cout << "No Piece in that position" << endl;
        return false;
        }
        if( b[rS][cS]->color == whoseTurn(n)) {
            return (b[rD][cD] == nullptr && (b[rS][cS]->isJump(rD, cD, b) || b[rS][cS]->isMove(rD, cD, b)));
        }
        else {
            cout << "not your piece" <<endl;
            displayErrMsg();
        }
    }
    else {
        cout << "value not in range " << endl;
        displayErrMsg();
    }
    return false;
}
bool jumpsAvailable( vector <vector<CheckersPiece*>> b, int n , CheckersPiece* cp ) {
    int jumpsAvailable = 0;
    vector <vector<int>> allPossibleJumps = { {2,2} , {2, -2} , {-2,2} , {-2, -2}
    };
    for(auto i: allPossibleJumps) {
        if(cp->isJump( cp->row+i[0] , cp->column+ i[1] , b) ) {
            jumpsAvailable++;
        }
    }
    return jumpsAvailable > 0;
}
void jumpPiece( vector<vector<CheckersPiece*>> &b, CheckersPiece* &cp, int rD, int cD) {
    int rS = cp->row;
    int cS = cp->column;
    int rM = rD - rS;
    int cM = cD-cS;

    cp->place(rD, cD) ;

    //delete b[rS + rM/2][cS + cM/2]; ??
    b[rD][cD] = cp;
    b[rS + rM/2][cS + cM/2] = nullptr;

    b[rS][cS] = nullptr;

}
void movePiece( vector<vector<CheckersPiece*>> &b, CheckersPiece* &cp, int rD, int cD) {
    int rS = cp->row;
    int cS = cp->column;

    cp->place(rD, cD);
    b[rD][cD] = cp;
    b[rS][cS] = nullptr;
}
#endif //CHECKERS_OBJ_CHECKERSBOARD_H