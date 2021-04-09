#include "./std_lib_facilities.h"
#include "./GridClass.h"
#include <conio.h>

struct position
    {
        int row;
        int column;
    };

void instructions(){
    cout << "\nThese are the instructions!";
}

void menu(bool &pause)
{
    system("cls");

    cout << "             __    __   __      .______    __          __  \n";
	cout << "            |  |  |  | |  |     |   _  \\  |  |        /_ | \n";
	cout << "            |  |__|  | |  |     |  |_)  | |  |         | | \n";
	cout << "            |   __   | |  |     |   ___/  |  |         | | \n";
	cout << "            |  |  |  | |  `----.|  |      |  `----.    | | \n";
	cout << "            |__|  |__| |_______||__|      |_______|    |_| \n";

    cout << "\n\n";
    if (pause) cout << "\t\t\t0 - Resume \n\n";
	cout << "\t\t\t1 - Start a new Game\n\n"; 
	cout << "\t\t\t2 - Rules\n\n";
	cout << "\t\t\t3 - Quit\n\n";
}

void print_instructions () {
  string line;
  ifstream myfile ("./instructions.txt");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      cout << line << '\n';
    }
    myfile.close();
  }

  else cout << "Unable to open file"; 
}

void gamePlay(Grid &myGrid,bool &pause){
    position currentMove;
    int option;
    char alphaChar = 'a';
    char turn = 'W';
    char key;

    pause = false;
    
    system("cls");
    myGrid.addNextPosOnGrid(turn);
    myGrid.printOut();
    myGrid.delNextPosOnGrid(turn);

    while(!myGrid.isGameEnd()){
        int i=0;
        
        if (turn == 'W') cout << "It is White Horse's turn!\n";
        else cout << "It is Black Horse's turn!\n";
        cout << "\nPossible values to move:\n";
        cout << "\n(Option 0): Pause the game\n";
        for (auto e:myGrid.getNextPosition(turn)){
            i=i+1;
            cout <<"(Option "<<i<<"): Row = "<< char(alphaChar+e.row)<<e.column+1<<endl; 
        }
        cout << "Select an option from above: ";

        while (true){
            cin >> option;
            if (option > 0 && option <= myGrid.getNextPosition(turn).size()){ myGrid.move(turn,myGrid.getNextPosition(turn)[option-1]);break;}
            else if (option == 0) {pause=true; break;}
            else cout << "Please Enter a valid value: ";
    }

    if (pause) break;
    
    if (turn == 'W') turn = 'B';
    else turn = 'W';

    system("cls");
    myGrid.addNextPosOnGrid(turn);
    myGrid.printOut();
    myGrid.delNextPosOnGrid(turn);
            
    }

    if (pause){
        menu(pause);
    }
    else {
        cout << "\n\n++++++++++++++++++CONGRATS++++++++++++++++++++\n";
        if (myGrid.getNextPosition('W').empty()) cout << "      WINNER OF THIS GAME IS BLACK HORSE\n";
        else cout << "      WINNER OF THIS GAME IS WHITE HORSE\n";
        cout << "++++++++++++++++++++++++++++++++++++++++++++++";

        cout << "\n\nPress Q key to go back!";
        while(key = getch()){
            if (key == 'q') break;
        };
        myGrid.initialize();
    }

     
    menu(pause);      
                        
}

int main(){
    char key;
    bool quitKey = false;
    bool pause = false;

    Grid myGrid;       //creates an instance of Grid class
    Grid insGrid;

    menu(pause);
    
    while (!quitKey){
        key = _getch();

        switch (key){
        case '0':
            gamePlay(myGrid,pause);
            break;

        case '1':
            myGrid.initialize();
            gamePlay(myGrid,pause);
            break;
        
        case '2':
            system("cls");
            insGrid.printOut();
            cout << "\n\n";
            print_instructions();
            cout << "\n\nPress any key to go back!";
            key = getch();

            menu(pause);
            break;

        case '3':
            system("cls");
            quitKey = true;
            break;
        
        default:
            cout << "\nPlease press a valid key!";
            break;
        }
        
    }
    
    return 0;
}


