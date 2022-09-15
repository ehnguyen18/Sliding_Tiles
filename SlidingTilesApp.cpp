//Main program

#include <iostream>
#include <iostream>
#include <string>

using namespace std;
#include "slidingTiles.h"

using namespace std;

int main() {
	srand(time(0));
	slidingTiles board;
	char x;
	cout<<"Welcome to the sliding tiles game!"<<endl;
	cout<<"The goal of the game is to move the tiles to the right order."<<endl;
	cout<<"The tiles are numbered 1-7"<<endl<<"'B' for Black, 'W' for White and 'S' for space."<<endl;
	cout<<"____________________________________________________________________________________"<<endl;
	for (int i=0; i<7; i++){
		while(true)
		{
			cout<<endl<<"Enter a character for tile "<<i+1<<": ";
			cin>>x;
			x=toupper(x);
			if (x=='B' && board.B<3){
				board.tiles[i]=x;
				board.B++;
				break;
			}
			else if (x=='W' && board.W<3){
				board.tiles[i]=x;
				board.W++;
				break;
			}
			else if (x=='S' && board.space==-1){
				board.space=i;
				break;
			}
			else{
				cout<<"Invalid input. Please try again."<<endl;
			}
		}
	}
	cout<<"____________________________________________________________________________________"<<endl;
	cout<<endl<<"Initial state: "<<endl;
	board.displayBoard();
	
	board.solve();
	
	system("pause");
	return 0;
}
