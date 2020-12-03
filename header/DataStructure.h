/* Open Data Structure project :
*
*
*  Data Structure Type - 
#  		1. Linked List {douLst, cycLst} 
#		2. Tree {BST, AVL, RBT}
#		3. Buffer based {Stack, Queue}
***********************************/
#pragma once  // compiler support macro. 

// stl include : 
#include<iostream>
using std::cout;

#include<cassert>   // should design exception handler..
#include<climits>

// Memory Manager : 
namespace Mem_manger{

	template<typename T>
	void safe_del_ptr(T*);

	template<typename T>
	void safe_del_doub_ptr(T**);

	template<typename T>
	void safe_del_ref_ptr(T*&);

	template<typename T>
	void safe_del_all_ref_ptr(T*&);

}
using namespace Mem_manger;

namespace default_setting{

	template<typename T>
	bool defau_cmp(T, T);
		
}
using namespace default_setting;

// Numerical Setting :
namespace num_setting{
	typedef unsigned long long uint; 
}
using namespace num_setting;


// Array type DS -
template<typename T>
class Smart_array{  // very basic DS, we can fully enter the low-level of this DS..
	private:
		T* arr;
		int ptr;
		int siz;
		
		// Utility function
		bool chk_bnd(const int &);
		void shrink_arr();
	
	public:
		// Constructor -
		Smart_array();
		Smart_array(T);
		
		// Getter for the assign operator - 
		T* get_arr();
		int get_ptr();
		int get_siz();

		// Operator -
		T& operator[](int);
		void operator=(Smart_array<T>&); // "assign" the Smart_array<T> to this arr.
		
		// Operation -
		void add(T);
		void remove_bk();
		void remove(const int&);
		
};

template<typename T>
class Smart_stack{
	private:
		Smart_array<T> arr;
		int curr_ptr;

	public:
		Smart_stack():arr(), curr_ptr{-1}{};
		Smart_stack(T val):arr(val), curr_ptr{0}{};

		// "copy return" to ensure the security.
		T top(){ return arr[curr_ptr]; }

		void push(T val){
			arr.add(val);
			++curr_ptr;
		}

		T pop(){
			T& tmp_val = top();
			arr.remove(curr_ptr--);
			return tmp_val;
		}

};

/*
*	 [0]  ->  [1]  ->  [2]  ->  [3]  -> ...
*     9        7       13      curr_ptr. -> pop (9, 7)
*
*    [0]  ->  [1]  ->  [2]  ->  [3]  -> ...
*    13    curr_ptr
*/
template<typename T>
class Smart_queue{
	private:
		Smart_array<T> arr;
		int curr_ptr;
	
	public:
		Smart_queue():arr(), curr_ptr{-1}{};

		Smart_queue(T val):arr(val), curr_ptr{0}{};

		// "copy return" to ensure the security.
		T top(){ return arr[0]; }

		void push(T val){
			arr.add(val);
			++curr_ptr;
		}

		T pop(){
			T tmp_val = top();
			arr.remove(0);
			--curr_ptr;
			return tmp_val;
		}

		bool is_empty(){ return (curr_ptr == -1) ? true : false; }
};



// < Array type DS alias
template<class T>
using sm_arr = Smart_array<T>;

template<class T>
using sm_stk = Smart_stack<T>;

template<class T>
using sm_que = Smart_queue<T>;
//  end_of_alias


// List type DS -
//  Direction definition :
/*  prev_ptr :  
*   	dummy <- head <- node_1 <- ... <- node_n <- (dummy, loop)
*	next_ptr :  
*		dummy -> node_1 -> ... -> node_n -> tail -> (dummy, loop)
*/
template<typename T>
class Double_linked_list{
	private:
		struct Node{
			T val;
			Node* next;
			Node* prev;
			// Node Constructor -
			Node();
			Node(const T&);  
		};
		Node dummy;
		int siz;
		
		// Utility -
		Node* find_prev_node(const int&);
	
	public:
		// Constructor -
		Double_linked_list();
		
		// Operation - add type
		void insert_bk(int, T);
		void add_front(T);
		void append_back(T);
		// Operation - remove type
		void remove_idx_bk(int);
		void remove_value(T);

		// View -
		void print();
};
// List type DS alias -
template<class T>
using douLst = Double_linked_list<T>;


// Tree type DS -
template<typename T>
class Binary_search_tree{
	public:
		enum Order{
			pre_order,
			post_order,
			in_order
		};

	private:
		class Node{
			public:
				T val;
				Node* left;
				Node* right; 
				Node* parent;
				// Node Constructor -
				Node(T);
				Node();
		};
		
		Node* root;
		int siz;
		bool (*cmp_func)(T, T);

		// Utility -
		Node* find_parent(T);
		void add_child(Node*, Node*);
		void ord_recur(Order, Node*);
		void prnt_spac_with_depth(); 

	public:
		// Constructor -
		Binary_search_tree();
		
		// Operation - add type
		void insert(T);

		// View -
		void order_traversal(Order);
		void BF_print();

		// Self-def -
		void set_cmp_func(bool (*)(T, T));
};
// alias Tree type DS -
template<class T>
using BST = Binary_search_tree<T>;




/* TODO : 
* 1. 
* 2.
*/
