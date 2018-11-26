#include "daryHeap.h"

// Just for debugging and testing
int main() {
	int numChildren, size;
	std::cout << ">>> D-ary Heap test <<<\n------------------------\n";
	std::cout << "Enter the number of children each node will have: ";
	std::cin >> numChildren;
	daryHeap<int> testHeap(numChildren);
	bool exit = false;
	do {
		std::cout << "\n__________________________________________________\nOperations:\n";
		std::cout << "\t1) Insert element in the heap\n";
		std::cout << "\t2) Delete element from the heap\n";
		std::cout << "\t3) Check empty heap\n";
		std::cout << "\t4) Print size\n";
		std::cout << "\t5) Print heap\n";
		std::cout << "\t6) Clear heap\n";
		std::cout << "\t7) Terminate the execution of the program\n";
		std::cout << "Select option: ";
		int choice;
		std::cin >> choice;
		std::cout << '\n';
		switch (choice){
			case 1: {
				std::cout << "Enter element to insert: ";
				int aux;
				std::cin >> aux;
				testHeap.push(aux);
				std::cout << "\nCurrent heap status ==> ";
				testHeap.print(std::cout);
				break;
			}
			case 2: {
				char answer;
				std::cout << "Do you want to delete the first element? [y/n]: ";
				std::cin >> answer;
				if (answer == 'y') {
					try {
						int deletion = testHeap.top();
						testHeap.pop();
						std::cout << "Successfully deleted " << deletion << '\n';
					}
					catch (std::domain_error e) {
						std::cout << e.what() << '\n';
					}
				}
				else {
					std::cout << "Enter delete position (1, ... , " << testHeap.size() << "): ";
					int pos;
					std::cin >> pos;
					try {
						int deletion = testHeap.deleteAt(pos-1);
						std::cout << "Successfully deleted " << deletion << '\n';
					}
					catch (std::domain_error e) {
						std::cout << e.what() << '\n';
					}
				}
				std::cout << "\nCurrent heap status ==> ";
				testHeap.print(std::cout);
				break;
			}
			case 3: {
				std::cout << "The heap is";
				if (!testHeap.empty()) {
					std::cout << " not";
				}
				std::cout << " empty\n";
				break;
			}
			case 4: {
				std::cout << "The size of the heap is " << testHeap.size() << '\n';
				break;
			}
			case 5: {
				testHeap.print(std::cout);
				break;
			}
			case 6: {
				testHeap.clear();
				std::cout << "The heap has been successfully cleared. All elements have been removed from the heap.\n";
				break;
			}
			case 7: {
				exit = true;
				break;
			}
			default: {
				std::cout << "Option out of range. Please, choose an option between 1 and 7.\n";
				break;
			}
		}
	} while (!exit);


	return 0;
}
