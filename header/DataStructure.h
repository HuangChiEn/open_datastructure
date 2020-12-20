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
using std::cerr;
using std::endl;

#include<cassert>   // should design exception handler..

#include<cmath>
using std::sqrt;

#include<climits>
#include<cstdint>
using std::uint32_t;

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


// Numerical Setting :
namespace num_setting{
	typedef unsigned long long uint; 
}
using namespace num_setting;


namespace default_setting{

	template<typename T>
	short defau_cmp(T, T);

	typedef uint (*hash_func) (uint);
		
}
using namespace default_setting;


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
		// Constructor -
		Smart_stack();
		Smart_stack(T);

		// Operation -
		T top();  // "copy return" to ensure the security.
		void push(T);
		T pop();
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
		// Constructor -
		Smart_queue();
		Smart_queue(T);

		// Opertion - 
		T top();      // "copy return" to ensure the security.
		void push(T);
		T pop();
		bool is_empty();
};



// < Array type DS alias
template<class T>
using Sm_arr = Smart_array<T>;

template<class T>
using Sm_stk = Smart_stack<T>;

template<class T>
using Sm_que = Smart_queue<T>;
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
		// Search - 
		bool find_val(T);
		int find_idx(T);

		// View -
		void print();
};
// List type DS alias -
template<class T>
using DouLst = Double_linked_list<T>;


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
		class Node{  // update name BST_Node.
			public:
				T val;
				Node* left;
				Node* right;
				Node* parent; 
				// Node Constructor -
				Node(T);
				Node();
		};
		short (*cmp_func)(T, T);

	private:
		Node* root;
		// Utility -
		void add_child(Node*, Node*);
		Node* find_node(T);
		void splice(Node*);
		void ord_recur(Order, Node*);
		void prnt_spac_with_depth(); 

	public:
		// Constructor -
		Binary_search_tree();
		Binary_search_tree(short (*)(T, T));
		
		// Operation - 
		void insert(T);
		void remove(T);

		// View -
		void order_traversal(Order);
		void BF_print();

};


template<typename T>
class AVL_tree : public Binary_search_tree<T>{
	private:
		class AVL_Node : public Node{
			public:
				short int balance_factor;

				// Node Constructor -
				AVL_Node(short int balance_factor):Node(), balance_factor{balance_factor}{}
				AVL_node(T val, short int balance_factor):Node(val), balance_factor{balance_factor}{}
		}; 

		AVL_Node* root;

	public:
		AVL_tree():root{nullptr}, cmp_func{&defau_cmp<T>}{};

		AVL_tree(short (*def_cmp_func)(T, T)):root{nullptr}, cmp_func{def_cmp_func}{}

		void insert(T val){
			Binary_search_tree<T>::insert(val);
			AVL_tree* new_nd = Binary_search_tree<T>::find_node(val);
			chk_balance();
			rotate();
		}

		void remove(T val){

		}
};

/*
template<typename T>
class Dictionary_tree: public AVL_tree<T>{
	private:

	public:	

};
*/
 
// alias Tree type DS -
template<class T>
using BST = Binary_search_tree<T>;
template<class T>
using AVLT = AVL_tree<T>;
/*
template<class T>
using Dict_tree = Dictionary_tree<T>;
*/

// Map type DS -
template<typename T>
class Chained_Hash_Table{
	private:
		DouLst<T>* hash_tab;

		// bucket = 16 = 2^p, and p = 4
		int bukt_bit;        // bukt_bit = p = 4

		uint elm_cnt;
		float load_density;  // ld_density := elm_cnt / bucket.  
		const float density_lim;
		
		bool chk_ld_density(){
			const uint32_t& bucket = (1UL << bukt_bit);
			return (static_cast<float>(elm_cnt / bucket) > density_lim) ? true : false;
		}

		uint32_t knuth_multi_hash(const int& key) {
			assert(bukt_bit >= 0 && bukt_bit <= 32);  // bukt_bit less then word
			float tmp = sqrt(5) - 1;
			// Hard-code knuth_num -> 
			//  const float& gloden_ratio = 0.5*(tmp);
			//  const uint32_t& knuth_num = floor(gloden_ratio * (1ULL << 32)); 
			const uint32_t& knuth_num = 2654435769;
			return (key * knuth_num) >> (32 - bukt_bit);
		}

		void extend_hash_table(){
			
			return;
		}

		void shrink_hash_table(){

			return ;
		}

	public:
		Chained_Hash_Table():density_lim{0.75}, bukt_bit{4}{ hash_tab = new DouLst<T>[(1UL << bukt_bit)]; }

		void add(T val){
			const int& int_val = static_cast<int>(val);
			const uint32_t& hash_idx = knuth_multi_hash(int_val);
			hash_tab[hash_idx].add_front(val);
			++elm_cnt;
			if(chk_ld_density())
				extend_hash_table();
		}

		void remove(T val){
			int& int_val = static_cast<int>(val);
			const uint32_t& hash_idx = knuth_multi_hash(int_val);
			hash_tab[hash_idx].remove_value(val);
			--elm_cnt;
			if(chk_ld_density())
				shrink_hash_table();
		}

		bool find_key(T val){
			const int& int_val = static_cast<int>(val);
			const uint32_t& hash_idx = knuth_multi_hash(int_val);
			return hash_tab[hash_idx].find_val(val);
		}

};
template<class T>
using CH_Tab = Chained_Hash_Table<T>;


// Graph type DS.



/* TODO : 
* 1. Hash Table (dict implement).
* 2. AVL-tree, RB+-tree.
* 3. B-tree.
*/
