#include "../std_lib_facilities.h"
#include <conio.h>

//<--------------------Class for Game------------------->

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
    
    void move(char turn, int r, int c){
        if (turn == 'W'){
            grid[W.row][W.column] = '-';
            W.row = r;
            W.column = c;
            grid[W.row][W.column] = 'W';
        } else
        {
           grid[B.row][B.column] = '-';
            B.row = r;
            B.column = c;
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
// <------------------------------------------------------------------>


//<-------------------------Game Logic--------------------------------->

struct position
    {
        int row;
        int column;
    };

void instructions(){
    cout << "\nThese are the instructions!";
}

void hlpl()
{
	cout << "             __    __   __      .______    __          __  \n";
	cout << "            |  |  |  | |  |     |   _  \\  |  |        /_ | \n";
	cout << "            |  |__|  | |  |     |  |_)  | |  |         | | \n";
	cout << "            |   __   | |  |     |   ___/  |  |         | | \n";
	cout << "            |  |  |  | |  `----.|  |      |  `----.    | | \n";
	cout << "            |__|  |__| |_______||__|      |_______|    |_| \n";
}

void menu()
{
	cout << "\n\n\t\t\t1 - Start Game\n\n";
	cout << "\t\t\t2 - Rules\n\n";
	cout << "\t\t\t3 - Quit\n\n";
}

int main(){
    position currentMove;
    int option;
    char alphaChar = 'a';
    char turn = 'W';
    char key;
    bool quitKey = false;

    Grid myGrid;       //creates an instance of Grid class

    system("cls");
    hlpl();
    menu();
    
    while (quitKey == false){
        key = _getch();

        switch (key){
        case '1':
            system("cls");
            myGrid.addNextPosOnGrid(turn);
            myGrid.printOut();
            myGrid.delNextPosOnGrid(turn);

            while(!myGrid.isGameEnd()){
                
                
                int i=0;
                
                if (turn == 'W') cout << "It is White Horse's turn!\n";
                else cout << "It is Black Horse's turn!\n";
                cout << "\nPossible values to move:\n";
                cout << "\n(Option 0): Skip turn!\n";
                for (auto e:myGrid.getNextPosition(turn)){
                    i=i+1;
                    cout <<"(Option "<<i<<"): Row = "<< char(alphaChar+e.row)<<e.column+1<<endl; 
                }
                cout << "Select an option from above: ";

                while (true){
                    cin >> option;
                    if (option > 0 and option <= myGrid.getNextPosition(turn).size()){ myGrid.move(turn,myGrid.getNextPosition(turn)[option-1].row,myGrid.getNextPosition(turn)[option-1].column);break;}
                    else if (option == 0) {break;}
                    else cout << "Please Enter a valid value: ";
                }

                if (turn == 'W') turn = 'B';
                else turn = 'W';

                system("cls");
                myGrid.addNextPosOnGrid(turn);
                myGrid.printOut();
                myGrid.delNextPosOnGrid(turn);
                        
            }


            cout << "\n\n++++++++++++++++++CONGRATS++++++++++++++++++++\n";
            if (myGrid.getNextPosition('W').empty()) cout << "      WINNER OF THIS GAME IS BLACK HORSE\n";
            else cout << "      WINNER OF THIS GAME IS WHITE HORSE\n";
            cout << "++++++++++++++++++++++++++++++++++++++++++++++";

            cout << "\n\nPress Q key to go back!";
            while(key = getch()){
                if (key == 'q') break;
            };
            
            system("cls");
            myGrid.initialize();
            hlpl();
            menu();
            break;
        
        case '2':
            system("cls");
            myGrid.printOut();
            instructions();

            cout << "\n\nPress any key to go back!";
            key = getch();

            system("cls");
            hlpl();
            menu();
            break;

        case '3':
            quitKey = true;
            break;
        
        default:
            cout << "\nPlease press a valid key!";
            break;
        }
        
    }
    
    return 0;
}


