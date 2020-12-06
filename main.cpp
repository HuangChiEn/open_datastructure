#include<iostream>
using std::cout;
#include<ctime>
#include<cstdlib>
#include<string>

#include"header/DataStructure.h"
#include"source/DataStructure.cpp"

#define MAXLEN 5
#define DIGRNG 100

typedef int DATATYPE;

int main(){
	
	srand(time(NULL));
	
	CH_Tab<int> hsh_tab;
	for(int idx=0 ; idx < MAXLEN ; ++idx){
		int tmp = rand()%DIGRNG + 1;
		cout << " tmp : " << tmp << " ; ";
		hsh_tab.add(tmp);
		cout << "found : " << hsh_tab.find_key(tmp);
	}

	return 0;
}

// TODO list -
/***************************************
 * 1. Test the adaptive extension & shrink function of hash_table.
 * 2. Split the Hash_table definition and implementation into .h, .cpp respectively.
 * 3. Design the abstract interface for each type of DS (e.g. lst type have same interface).
 * 4. Design unit test class for the "container".
****************************************/