// It is an implementation of A* Algorithm
// The below shows the shortest path from the start node to the destination given a board pattern
// Used different priority queue and hash table for implementation
// Get cool implementations like this in www.github.com/jarvisp99


#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#define DIM1 10
#define DIM2 10

struct Board {

	// The Basic Board pattern includes start , destination and some hindrances
	//	Start		= 2
	//  Dest		= 3
	//	Hind		= 0
	//	Non Hind	= 1

	std::pair<int, int> Start;
	std::pair<int, int> Dest;
	std::vector<int*> boardPattern;
}board;

// Priority queue
struct _open {

	std::pair<int, int> list;
	int f = 0;
	int g = 0;
	std::pair<int, int> parent;

	_open* next = NULL;
	_open* prev = NULL;

	void enque(std::pair<int, int>& coord, const int& f, std::pair<int, int>& par, const int& g) {
		_open* temp = new _open;
		temp->list = coord;
		temp->f = f;
		temp->parent = par;
		temp->g = g;

		if (start == NULL) {
			temp->next = NULL;
			temp->prev = NULL;
			start = rear = temp;
		}
		else
		{
			_open* trav = rear;
			_open* del = NULL;
			while (trav != NULL) {
				if (temp->list == trav->list) {
					if (temp->f > trav->f) {
						break;
					}
					else if (temp->f == trav->f && temp->g > trav->g)
					{
						break;
					}
					else
						del = trav;
				}
				if (temp->f > trav->f) {
					if (temp->f == trav->f && temp->g > trav->g)
					{
						trav = trav->prev;
						continue;
					}
					temp->prev = trav;
					temp->next = trav->next;
					if (trav->next == NULL) {
						rear = temp;
					}
					else
					{
						trav->next->prev = temp;
					}
					trav->next = temp;
					if (del != NULL) {
						if (del->prev != NULL)
							del->prev->next = del->next;
						else
							start = del->next;

						if (del->next != NULL)
							del->next->prev = del->prev;
						else
							rear = del->prev;
						delete del;
					}
					break;
				}
				trav = trav->prev;
			}
			if (trav == NULL) {
				temp->next = start;
				start->prev = temp;
				temp->prev = NULL;
				start = temp;
				if (del != NULL) {
					if (del->prev != NULL)
						del->prev->next = del->next;
					else
						start = del->next;

					if (del->next != NULL)
						del->next->prev = del->prev;
					else
						rear = del->prev;
					delete del;
				}
			}
		}
	}
	_open deque() {
		if (start != NULL)
		{
			_open* temp = start;
			if (temp->next != NULL)
			{
				temp->next->prev = NULL;
				start = temp->next;
			}

			else
			{
				start = rear = NULL;
			}
			return *temp;
		}
		else
			std::cout << "\nError while dequeuing....\n";
	}
	void display() {
		_open* temp = start;
		std::cout << "\n";
		while (temp != NULL) {
			std::cout << temp->list.first << "," << temp->list.second << "  f = " << temp->f << " " << temp->parent.first << "," << temp->parent.second << " " << temp->g << "\n";
			temp = temp->next;
		}
	}
}*start = NULL, * rear = NULL;

struct _closed {

	std::pair<int, int>* list = new std::pair<int, int>[DIM1 * DIM2];
	int* fValue = new int[DIM1 * DIM2];
	std::pair<int, int>* parent = new std::pair<int, int>[DIM1 * DIM2];
};

//initialization



void print(Board & board) {
	std::cout << "\n";
	for (int i = 0; i < DIM1; i++) {
		for (int j = 0; j < DIM2; j++) {
			std::cout << board.boardPattern[i][j] << " ";
		}
		std::cout << "\n";
	}
}

//Euclidean Distance for both the values
int hValue(std::pair<int, int> & dist, std::pair<int, int> & dest) {
	return 10 * sqrt((dist.first - dest.first) * (dist.first - dest.first) + (dist.second - dest.second) * (dist.second - dest.second));
}

int gValue(std::pair<int, int> & dist, std::pair<int, int> & start) {
	return 10 * sqrt((dist.first - start.first) * (dist.first - start.first) + (dist.second - start.second) * (dist.second - start.second));
}


int main() {
	// Let Suppose the map is 10 x 10 big
	// You are suppose to create an (a*) algorithm to reach the destination
	// Add starting point 
	// Destination and hurdles


	// Default Board Pattern check
	int choose;
	std::cout << "Want To use default Board Pattern (Press 1) Or Manual Enter : ";
	std::cin >> choose;
	if (choose == 1) {
		board.boardPattern.emplace_back(new int[10]{ 2 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 });
		board.boardPattern.emplace_back(new int[10]{ 1 , 1 , 1 , 1 , 0 , 1 , 1 , 1 , 1 , 1 });
		board.boardPattern.emplace_back(new int[10]{ 1 , 1 , 1 , 1 , 0 , 1 , 1 , 1 , 1 , 1 });
		board.boardPattern.emplace_back(new int[10]{ 1 , 1 , 1 , 1 , 1 , 1 , 0 , 1 , 1 , 1 });
		board.boardPattern.emplace_back(new int[10]{ 1 , 1 , 1 , 1 , 1 , 1 , 0 , 1 , 1 , 1 });
		board.boardPattern.emplace_back(new int[10]{ 0 , 1 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 });
		board.boardPattern.emplace_back(new int[10]{ 1 , 1 , 1 , 0 , 0 , 1 , 0 , 1 , 1 , 1 });
		board.boardPattern.emplace_back(new int[10]{ 1 , 1 , 0 , 0 , 3 , 1 , 0 , 1 , 1 , 1 });
		board.boardPattern.emplace_back(new int[10]{ 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 });
		board.boardPattern.emplace_back(new int[10]{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 });
		board.Start.first = 0;
		board.Start.second = 0;
		board.Dest.first = 7;
		board.Dest.second = 4;
	}
	else
	{
		std::cout << "Enter Initial Board Pattern: ";
		for (int i = 0; i < DIM1; i++) {
			int* arr = new int[DIM2];
			for (int j = 0; j < DIM2; j++) {
				std::cin >> arr[j];
				if (arr[j] == 2) {
					board.Start.first = i;
					board.Start.second = j;
				}
				else if (arr[j] == 3) {
					board.Dest.first = i;
					board.Dest.second = j;
				}
			}
			board.boardPattern.emplace_back(arr);
		}
	}

	print(board);

	//Open list binding
	// Open list is actually a priority queue with low f value is the highest priority
	_open open;

	// Closed list binding
	// Closed List is actually a hash table
	_closed closed;
	for (int i = 0; i < DIM1 * DIM2; i++) {
		closed.fValue[i] = -1;
	}
	//std::pair<int, int> parent;

	_open parent;
	parent.list = board.Start;
	parent.f = 0;
	parent.parent = { -1, -1 };
	parent.g = 0;

	open.enque(parent.list, parent.f, parent.parent, parent.g);
	int isReached = 0;

	// Till the Priority queue is empty or we have reached the destination
	// The below loop will execute
	while (start != NULL && isReached == 0) {
		for (int i = 0; i < 8; i++) {
			std::pair<int, int> successor;

			//For Checking Every successor in all 8 directions
			switch (i) {
			case 0: // East direction
				if (parent.list.second + 1 < DIM2) {
					successor.first = parent.list.first;
					successor.second = parent.list.second + 1;
					int hashValue = (10 * successor.first + successor.second) % (DIM1 * DIM2);
					if (board.boardPattern[successor.first][successor.second] != 0 && closed.fValue[hashValue] == -1) {
						if (successor == board.Dest) {
							isReached = 1;
							closed.list[hashValue] = successor;
							closed.parent[hashValue] = parent.list;
							closed.fValue[hashValue] = 0;
							break;
						}
						int g = gValue(successor, parent.list) + parent.g;
						int f = hValue(successor, board.Dest) + g;
						open.enque(successor, f, parent.list, g);
					}
				}
				break;
			case 1:	// South East Direction
				if (parent.list.first + 1 < DIM1 && parent.list.second + 1 < DIM2) {
					successor.first = parent.list.first + 1;
					successor.second = parent.list.second + 1;
					int hashValue = (10 * successor.first + successor.second) % (DIM1 * DIM2);
					if (board.boardPattern[successor.first][successor.second] != 0 && closed.fValue[hashValue] == -1) {
						if (successor == board.Dest) {
							isReached = 1;
							closed.list[hashValue] = successor;
							closed.parent[hashValue] = parent.list;
							closed.fValue[hashValue] = 0;
							break;
						}
						int g = gValue(successor, parent.list) + parent.g;
						int f = hValue(successor, board.Dest) + gValue(successor, board.Start);
						open.enque(successor, f, parent.list, g);
					}
				}
				break;
			case 2:	// South Direction
				if (parent.list.first + 1 < DIM1) {
					successor.first = parent.list.first + 1;
					successor.second = parent.list.second;
					int hashValue = (10 * successor.first + successor.second) % (DIM1 * DIM2);
					if (board.boardPattern[successor.first][successor.second] != 0 && closed.fValue[hashValue] == -1) {
						if (successor == board.Dest) {
							isReached = 1;
							closed.list[hashValue] = successor;
							closed.parent[hashValue] = parent.list;
							closed.fValue[hashValue] = 0;
							break;
						}
						int g = gValue(successor, parent.list) + parent.g;
						int f = hValue(successor, board.Dest) + gValue(successor, board.Start);
						open.enque(successor, f, parent.list, g);
					}
				}
				break;
			case 3: // South West Direction
				if (parent.list.first + 1 < DIM1 && parent.list.second - 1 > -1) {
					successor.first = parent.list.first + 1;
					successor.second = parent.list.second - 1;
					int hashValue = (10 * successor.first + successor.second) % (DIM1 * DIM2);
					if (board.boardPattern[successor.first][successor.second] != 0 && closed.fValue[hashValue] == -1) {
						if (successor == board.Dest) {
							isReached = 1;
							closed.list[hashValue] = successor;
							closed.parent[hashValue] = parent.list;
							closed.fValue[hashValue] = 0;
							break;
						}
						int g = gValue(successor, parent.list) + parent.g;
						int f = hValue(successor, board.Dest) + gValue(successor, board.Start);
						open.enque(successor, f, parent.list, g);
					}
				}
				break;
			case 4: // West Direction
				if (parent.list.second - 1 > -1) {
					successor.first = parent.list.first;
					successor.second = parent.list.second - 1;
					int hashValue = (10 * successor.first + successor.second) % (DIM1 * DIM2);
					if (board.boardPattern[successor.first][successor.second] != 0 && closed.fValue[hashValue] == -1) {
						if (successor == board.Dest) {
							isReached = 1;
							closed.list[hashValue] = successor;
							closed.parent[hashValue] = parent.list;
							closed.fValue[hashValue] = 0;
							break;
						}
						int g = gValue(successor, parent.list) + parent.g;
						int f = hValue(successor, board.Dest) + gValue(successor, board.Start);
						open.enque(successor, f, parent.list, g);
					}
				}
				break;
			case 5:	// North West Direction
				if (parent.list.first - 1 > -1 && parent.list.second - 1 > -1) {
					successor.first = parent.list.first - 1;
					successor.second = parent.list.second - 1;
					int hashValue = (10 * successor.first + successor.second) % (DIM1 * DIM2);
					if (board.boardPattern[successor.first][successor.second] != 0 && closed.fValue[hashValue] == -1) {
						if (successor == board.Dest) {
							isReached = 1;
							closed.list[hashValue] = successor;
							closed.parent[hashValue] = parent.list;
							closed.fValue[hashValue] = 0;
							break;
						}

						int g = gValue(successor, parent.list) + parent.g;
						int f = hValue(successor, board.Dest) + gValue(successor, board.Start);
						open.enque(successor, f, parent.list, g);
					}
				}
				break;
			case 6:	// North Direction
				if (parent.list.first - 1 > -1) {
					successor.first = parent.list.first - 1;
					successor.second = parent.list.second;
					int hashValue = (10 * successor.first + successor.second) % (DIM1 * DIM2);
					if (board.boardPattern[successor.first][successor.second] != 0 && closed.fValue[hashValue] == -1) {
						if (successor == board.Dest) {
							isReached = 1;
							closed.list[hashValue] = successor;
							closed.parent[hashValue] = parent.list;
							closed.fValue[hashValue] = 0;
							break;
						}
						int g = gValue(successor, parent.list) + parent.g;
						int f = hValue(successor, board.Dest) + gValue(successor, board.Start);
						open.enque(successor, f, parent.list, g);
					}
				}
				break;
			case 7:	// North East Direction
				if (parent.list.first - 1 > -1 && parent.list.second + 1 < DIM2) {
					successor.first = parent.list.first - 1;
					successor.second = parent.list.second + 1;
					int hashValue = (10 * successor.first + successor.second) % (DIM1 * DIM2);
					if (board.boardPattern[successor.first][successor.second] != 0 && closed.fValue[hashValue] == -1) {
						if (successor == board.Dest) {
							isReached = 1;
							closed.list[hashValue] = successor;
							closed.parent[hashValue] = parent.list;
							closed.fValue[hashValue] = 0;
							break;
						}
						int g = gValue(successor, parent.list) + parent.g;
						int f = hValue(successor, board.Dest) + gValue(successor, board.Start);
						open.enque(successor, f, parent.list, g);
					}
				}
				break;
			}
		}

		//Storing it to closed list 
		//Assigning dequed one to be new parent and so on

		int hashValue = (10 * parent.list.first + parent.list.second) % (DIM1 * DIM2);
		closed.list[hashValue] = parent.list;
		closed.parent[hashValue] = parent.parent;
		closed.fValue[hashValue] = parent.f;
		_open temp = open.deque();
		parent.list = temp.list;
		parent.f = temp.f;
		parent.parent = temp.parent;
		parent.g = temp.g;

	}
	if (isReached == 1) {
		// To Print The Path if Found
		std::cout << "\n";
		std::cout << "Optimum Path for End to Start : \n";
		std::pair<int, int> temp = board.Dest;
		while (temp.first != -1 && temp.second != -1) {
			int hashValue = (10 * temp.first + temp.second) % (DIM1 * DIM2);
			std::cout << closed.list[hashValue].first << "," << closed.list[hashValue].second << "\n";
			temp = closed.parent[hashValue];
		}

		//Check the traversing path with the board pattern
		std::cout << "\n";
		print(board);
	}
	else
		std::cout << "\nPath Not Found\n";


}