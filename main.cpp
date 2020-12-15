#include<iostream>
using std::cout;
#include<ctime>
#include<cstdlib>
#include<cstdint>
#include<string>

#include"header/DataStructure.h"
#include"header/Blkbox_Tester.h"
#include"source/DataStructure.cpp"

#define MAXLEN 20
#define DIGRNG 100

//typedef int DATATYPE;

int main(){
	
	srand(time(NULL));
	
	BST<int32_t> bst_tree;
	int32_t* arr = uniform_data_gen(MAXLEN, DIGRNG);
	cout << "Non duplicate series : \n";
	for(int idx=0 ; idx < MAXLEN ; ++idx){
		cout << arr[idx] << " ";
		bst_tree.insert(arr[idx]);
	}
	cout << "\nBF print\n";
	bst_tree.BF_print();

	cout << "\nRemoving elements :\n";
	for(int idx=0 ; idx < MAXLEN-10 ; ++idx){
		cout << arr[idx] << " ";
		bst_tree.remove(arr[idx]);
	}
		
	cout << "\nBF print 2 :\n";
	bst_tree.BF_print();

	cout << "done";
	return 0;
}

// TODO list -
/***************************************
 * 0. Implement the remove function to the BST.
 * 1. Test the adaptive extension & shrink function of hash_table.
 * 2. Split the Hash_table definition and implementation into .h, .cpp respectively.
 * 3. Design the abstract interface for each type of DS (e.g. lst type have same interface).
 * 4. Design unit test class for the "container".
****************************************/