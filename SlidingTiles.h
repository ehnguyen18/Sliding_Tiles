#ifndef SLIDINGTILES_H_
#define SLIDINGTILES_H_
//SlidingTiles Header file
#include <iostream>
#include <iomanip>
#include <set>
#include <unordered_map>
#include <queue>
#include <stack>
using namespace std;
class slidingTiles
{ 
public:

	vector<char> tiles;
	int B=0;
	int W=0;
	int space=-1;
	int cost = 0;
	slidingTiles(const slidingTiles& cboard) {
		tiles = cboard.tiles;
		B = cboard.B;
		W = cboard.W;
		space = cboard.space;
		cost = cboard.cost;
	}

	void displayBoard() const;
	//Function to print the board.

	bool gameStatus();
	//Function to determine the current status of the game.

	void solve();
	//Solve the puzzle

	slidingTiles()
	{
		for (int i=0; i<7; i++){
			tiles.push_back(' ');
		}
	}
	//Default constructor.
	//Postcondition: Initializes the board to an empty state.
	bool operator==(const slidingTiles& lhs) 
	{ /* do actual comparison */
		return  equal(tiles.begin(), tiles.end(), lhs.tiles.begin());

	}

	bool operator!=(const slidingTiles& lhs) 
	{ /* do actual comparison */
		return tiles != lhs.tiles;	

	}

	void operator=(const slidingTiles& lhs) 
	{ /* do actual comparison */
		tiles = lhs.tiles;	
		B = lhs.B;
		W = lhs.W;
		space = lhs.space;
		cost = lhs.cost;
		//return true;

	}

	bool operator<(const slidingTiles& rhs) const
        {
            return cost < rhs.cost;
        }
};

void slidingTiles::displayBoard() const {
	cout<< endl << "   1    2    3    4    5    6    7" << endl << endl;


	for (int col = 0; col < 7; col++) {
		cout << "   "<<tiles[col]<<" ";

		// if (col != 6)
		// 	cout << "  |";
	}

	cout << endl;
	cout << " ____|____|____|____|____|____|____" << endl ;

	cout << endl;
}


bool slidingTiles::gameStatus() {
	if (tiles[0]=='W' && tiles[2]=='W' && tiles[1]=='W')
		return true;
	
	switch (space){
		case 0:
			if (tiles[1]=='W' && tiles[2]=='W' && tiles[3]=='W')
			{
				return true;
			}
			else{
				return false;
			}
		case 1:
			if (tiles[0]=='W' && tiles[2]=='W' && tiles[3]=='W')
			{
				return true;
			}
			else{
				return false;
			}
		case 2:
			if (tiles[0]=='W' && tiles[1]=='W' && tiles[3]=='W')
			{
				return true;
			}
			else{
				return false;
			}
		default:
			return false;
	}
	return false;
}

void slidingTiles::solve() {
	
	slidingTiles node,child;			
	node = *this;

	set<vector<char>> explored;
	priority_queue<pair<int,pair<int,slidingTiles>>> frontier; //cost ,pair<blank_index, board>
	vector<pair<slidingTiles, slidingTiles>> parent;
	vector<char>dummy; //Empty vector
	stack<slidingTiles> path;

	frontier.push({0,{space,node}});
	explored.insert(tiles);
	parent.push_back(make_pair(child,node));
	
	while(true){	
		if(frontier.empty())
		{
			cout<<"No solution found"<<endl;
			return;
		}
		
		node = frontier.top().second.second;
		node.space = frontier.top().second.first;
		node.cost = -frontier.top().first;
		frontier.pop();

		//Reach goal state
		if(node.gameStatus())
		{
			cout<<"____________________________________________________________________________________"<<endl;
			cout << "Solution found!" << endl;
			cout << "Cost: " << node.cost << endl;
			path.push(node);
			while(node.B>0)
			{
				for(int i=0; i<parent.size(); i++)
				{
					if(parent[i].second == node)
					{
						path.push(parent[i].first);
						node = parent[i].first;
						break;
					}
				}
			}
			path.pop();

			while (!path.empty())
			{
				path.top().displayBoard();
				path.pop();
			}
			return;
		}
		// Expand the state
		int cost = 0;
		for (int i=0; i<7; i++)
		{
			if (i == node.space)
				continue;
			cost = abs(node.space - i) - 1;
			child = node;
			
			if (cost>2)
				continue;
			if (cost<=1)
				cost=1;
			
			//Swap the space, make the child
			child.tiles[node.space] = child.tiles[i];
			child.tiles[i] = ' ';
			child.space = i;
			child.cost += cost;

			int size = explored.size();
			explored.insert(child.tiles);

			if (explored.size()>size)//If not explored, then the size of the set will change
			{
				frontier.push({-child.cost, {child.space, child}});
				parent.push_back(make_pair(node,child));
			}
			else //If explored
			{
				for(int i=0; i<parent.size(); i++)
				{
					if(parent[i].second == child)
					{
						if(parent[i].first.cost > child.cost)
						{
							parent[i].first = child;
						}
						break;
					}
				}
			}
		}
	}
}
#endif