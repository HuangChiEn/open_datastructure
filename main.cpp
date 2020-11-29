#include<iostream>
using std::cout;
#include<ctime>
#include<cstdlib>
#include<string>

#include"header/DataStructure.h"
#include"source/DataStructure.cpp"

#define MAXLEN 5
#define DIGRNG 100

int main(){
	
	srand(time(NULL));
	BST<int> tree;
	for(int idx=0 ; idx < MAXLEN ; ++idx){
		int tmp = rand()%DIGRNG + 1;
		cout << " tmp : " << tmp << " ; ";
		tree.insert(tmp);
	}

	tree.order_traversal(tree.Order::in_order);	
	return 0;
}

// TODO list -
/***************************************
 * 1. Set the code runner customer command for include path, and remove the relative path of .cpp.
 * 2. BST tree simple test (not unit test).
 * 3. Split the BST definition and implementation into .h, .cpp respectively.
 * 4. Design the abstract interface for each type of DS (e.g. lst type have same interface).
 * 5. Design unit test class for the "container".
****************************************/