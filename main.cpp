#include<iostream>
using std::cout;

#include<ctime>
#include<cstdlib>
#include<cstdint>
#include<string>

// DS-include
#include"header/DataStructure.h"
#include"source/DataStructure.cpp"
#include"testing/Blkbox_Tester.h"


int main(){
	const uint32_t MAXLEN = 200;
	const int32_t DIGRNG = 300;

	srand(time(NULL));
	int32_t* arr = uniform_data_gen(MAXLEN, DIGRNG);
	//Sm_arr<int32_t> arr{11, 73, 21, 43, 85, 18, 26, 59, 10, 24};
	AVL<int32_t> avl_tree;
	//for(int idx=0 ; idx < MAXLEN ; ++idx)
	//	cout << " | " << arr[idx] << " ; ";
	
	//cout << "\n\n" ;

	for(int idx=0 ; idx < MAXLEN ; ++idx)
		avl_tree.insert(arr[idx]);

	avl_tree.BF_print();
	cout << "\n\n\n";

	avl_tree.remove(arr[0]);  
	avl_tree.remove(arr[2]);  
	avl_tree.remove(arr[4]);  
	
	//cout << "\n BFT Traversal \n " ;
	avl_tree.BF_print();
	cout << "done!";
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