#ifndef gridclass
#define gridclass 251113L

#include "./std_lib_facilities.h"

class Grid{
private:
    char spaceChar = 176;
    char lineChar = 186;
    struct position
    {
        int row;
        int column;
    }; 
    vector<char> line;
    vector<vector<char>> grid;
       
    position W;
    position B;

    vector<position> nextPositionW;
    vector<position> nextPositionB;


    void nextPositionsCalc(vector<position>& nextPos, position P){
        nextPos.clear();
        int nextRow = 0;
        int nextCol = 0;
        for (int i=-1; i<=1; i=i+2){
            for (int j=-2; j<=2; j=j+4){
                nextRow = P.row+i;
                nextCol = P.column+j;
                if (nextRow >= 0 && nextCol >= 0 && nextRow <= 7 && nextCol <= 7)
                    if (isEmpty(nextRow,nextCol)) nextPos.push_back({nextRow,nextCol});
                nextRow = P.row+j;
                nextCol = P.column+i;
                if (nextRow >= 0 && nextCol >= 0 && nextRow <= 7 && nextCol <= 7)
                    if (isEmpty(nextRow,nextCol)) nextPos.push_back({nextRow,nextCol});
            }
        }
    }
    void updateNextPositions(){
        nextPositionsCalc(nextPositionW, W);
        nextPositionsCalc(nextPositionB, B);
    }    
    
public:
    Grid(){
        initialize();
    }

    void initialize(){          
        nextPositionW.clear();
        nextPositionB.clear();
        line.clear();
        grid.clear();

        for (int i = 0; i < 8; i++) line.push_back(spaceChar);
        for (int i = 0; i < 8; i++) grid.push_back(line);
        W.row = 0; W.column = 0;
        B.row = 7; B.column = 7;
        grid[W.row][W.column] = 'W';
        grid[B.row][B.column] = 'B';
        updateNextPositions();
    }
    
    void move(char turn, position p){
        if (turn == 'W'){
            grid[W.row][W.column] = '-';
            W.row = p.row;
            W.column = p.column;
            grid[W.row][W.column] = 'W';
        } else
        {
           grid[B.row][B.column] = '-';
            B.row = p.row;
            B.column = p.column;
            grid[B.row][B.column] = 'B';
        }
         updateNextPositions();
        
       
    }

    bool isEmpty(int r, int c) {
        if (grid[r][c] == spaceChar) return true;
        else return false;        
    }

    position positionW(){
        return W;
    }

    position positionB(){
        return B;
    }

    vector<position> getNextPosition(char turn){
        if (turn == 'W'){
            return nextPositionW;
        } else
        {
            return nextPositionB;
        }
        
        
    }

    void addNextPosOnGrid(char turn){
        int i = 49;
        if (turn == 'W') {
            for (auto e:nextPositionW){
                grid[e.row][e.column] = i;
                i=i+1;
            }
        }
        else {
            for (auto e:nextPositionB){
                grid[e.row][e.column] = i;
                i=i+1;
            }
        }
    }

    void delNextPosOnGrid(char turn){
        if (turn == 'W') {
            for (auto e:nextPositionW) grid[e.row][e.column] = spaceChar;
        }
        else {
            for (auto e:nextPositionB) grid[e.row][e.column] = spaceChar;
        }
    }

    bool isGameEnd(){
        if (nextPositionW.empty() || nextPositionB.empty()) return true;
        else return false;
    }

    void printOut(){
    vector<int> topl = {201,205,205,205,203,205,205,205,203,205,205,205,203,205,205,205,203,205,205,205,203,205,205,205,203,205,205,205,203,205,205,205,187};
    vector<int> midl = {204,205,205,205,206,205,205,205,206,205,205,205,206,205,205,205,206,205,205,205,206,205,205,205,206,205,205,205,206,205,205,205,185};
    vector<int> bottoml ={200,205,205,205,202,205,205,205,202,205,205,205,202,205,205,205,202,205,205,205,202,205,205,205,202,205,205,205,202,205,205,205,188};

        cout << "   ";
        for (int i = 1; i <= 8; i++) cout << "  "<< i << " ";
        cout << "\n";
        char myChar = 'a';

        cout << "   ";
        for (auto i: topl) cout<<char(i);
        cout << endl;

        for (auto v: grid){
            cout << myChar << "  ";  myChar++;
            for (auto h: v) cout << lineChar << " " <<  h << " ";
            cout << lineChar <<"\n   ";

            if (v == grid[7]) for (auto i: bottoml) cout<< char(i);
            else for (auto i: midl) cout<< char(i);
            cout << endl;
        }
        cout << "\n";
    }

    
};



#endif 
