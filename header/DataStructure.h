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

#include<initializer_list>
using std::initializer_list;

#include<cmath>
using std::sqrt;
using std::max;

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
		Smart_array(uint);
		Smart_array(const initializer_list<T>&);  // copy constructor

		
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
		bool is_empty();
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
class Disjoint_set{
	private:
		struct Set{
			Set* set_ptr;
			T data;
		};
		Set* root;

	public:
		Disjoint_set():root{nullptr}{}

		Disjoint_set(T data):root{nullptr}{ this->root = new Set{nullptr, data}; }
		
};



template<typename T>
class Binary_search_tree{
	private:
		class Node{  // update name BST_Node.
			public:
				T val;
				Node* left;
				Node* right;
				Node* parent; 
				// Node Constructor -
				Node();
				Node(T);
		};
		Node* root;

		short (*cmp_func)(T, T);
		
		// Utility -
		void add_child(Node*, Node*);

		Node* find_node(T);

		void splice(Node*);

		uint32_t get_height(Node*);


	public:
		enum Order{  // for the order traversal.
			pre_order,
			post_order,
			in_order
		};

		// Constructor -
		Binary_search_tree();
		Binary_search_tree(short (*)(T, T));
		
		// Operation - 
		void insert(T);
		void remove(T);

		// View -
		void order_traversal(Order);
		void BF_print();

		// Utility -
		void ord_recur(Order, Node*);
		uint32_t recur_get_height(Node* ptr_nd);
		uint32_t get_depth(Node*);

};


template<typename T>
class AVL_tree{
	private:
		class AVL_Node{  // update name BST_Node.
			public:
				T val;
				AVL_Node* left;
				AVL_Node* right;
				AVL_Node* parent; 
				int height;
				
				// Node Constructor -
				AVL_Node():left{nullptr}, right{nullptr}, parent{nullptr}, val{}, height{0}{}
				AVL_Node(T val): left{nullptr}, right{nullptr}, parent{nullptr}, height{0}, val{val}{}
		};
		AVL_Node* root;

		short (*cmp_func)(T, T);
		
		// Utility -
		void add_child(AVL_Node* prev_nd, AVL_Node* chd_nd){
			if(prev_nd == nullptr){
				this->root = chd_nd;
				return;
			}
				
			// update parent pointer first.
			switch(cmp_func(chd_nd->val, prev_nd->val)){
				case 1:
					prev_nd->right = chd_nd;
					break;
				case 0:
					prev_nd->left = chd_nd;
					break;
				case -1:
					cerr << "Warning : The element should not be duplicate." << endl;
					return;
				default:
					cerr << "ERROR_MESSAGE : The self-defin compare func should return triple value (1, 0, -1)." << endl;
					return;
			}

			// update parent pointer of child node
			chd_nd->parent = prev_nd;
		}

		AVL_Node* find_node(T val){
			AVL_Node* prev_ptr = nullptr;
			for(AVL_Node* tmp_ptr = this->root ; tmp_ptr != nullptr ; ){
				prev_ptr = tmp_ptr;
				switch(cmp_func(val, tmp_ptr->val)){
					case 1:
						tmp_ptr = tmp_ptr->right;
						break;
					case 0:
						tmp_ptr = tmp_ptr->left;
						break;
					case -1:
						return prev_ptr;
				}
			}
			// for not find the node, return their parent node.
			return prev_ptr;
		}

		int get_max(int a, int b){ return (a >= b) ? a : b; }

		int get_height(AVL_Node* ptr_nd){
			if(ptr_nd == nullptr)
				return -1;

			return ptr_nd->height;
		}

		int cal_balance(AVL_Node* nd_ptr){ return get_height(nd_ptr->left) - get_height(nd_ptr->right); }

		AVL_Node* Right_rotate(AVL_Node* curr_nd){
			AVL_Node* lft_chd = curr_nd->left;
			AVL_Node* rgt_suc = lft_chd->right;

			// Perform rotation
			lft_chd->right = curr_nd;
			curr_nd->left = rgt_suc;

			// update parent pointer of current pointed node and child node 
			lft_chd->parent = curr_nd->parent;
			curr_nd->parent = lft_chd;
			if(rgt_suc != nullptr)
				rgt_suc->parent = curr_nd;
		
			// Update heights
			lft_chd->height = get_max(get_height(lft_chd->left), get_height(lft_chd->right)) + 1;
			curr_nd->height = get_max(get_height(curr_nd->left), get_height(curr_nd->right)) + 1;

			return lft_chd;
		}

		AVL_Node* Left_rotate(AVL_Node* curr_nd){
			AVL_Node* rgt_chd =  curr_nd->right;
			AVL_Node* lft_suc = rgt_chd->left;
		
			// Perform rotation
			rgt_chd->left = curr_nd;
			curr_nd->right = lft_suc;

			// update parent pointer of current pointed node and child node 
			rgt_chd->parent = curr_nd->parent;
			curr_nd->parent = rgt_chd;
			if(lft_suc != nullptr)
				lft_suc->parent = curr_nd;

			// Update heights
			rgt_chd->height = get_max(get_height(rgt_chd->left), get_height(rgt_chd->right)) + 1;
			curr_nd->height = get_max(get_height(curr_nd->left), get_height(curr_nd->right)) + 1;

			return rgt_chd;
		}

		void splice(AVL_Node* ptr_nd){
			/* remove node confirm that the ptr_nd have successor in single side.
															       Case 1.   ;    Case 2.   */
			AVL_Node* succsor_nd = (ptr_nd->left != nullptr) ? ptr_nd->left : ptr_nd->right;
			
			if(ptr_nd == this->root){  // for remove the root.
				this->root = succsor_nd;
			}else{              
				AVL_Node* par_nd = ptr_nd->parent;
				if(par_nd->left == ptr_nd)
					par_nd->left = succsor_nd;
				else
					par_nd->right = succsor_nd;

				if(succsor_nd != nullptr) succsor_nd->parent = par_nd;
			}
		}

	public:
		enum Order{  // for the order traversal.
			pre_order,
			post_order,
			in_order
		};

		// Constructor -
		AVL_tree():root{nullptr}, cmp_func{&defau_cmp<T>}{}
		AVL_tree(short (*def_cmp_func)(T, T)):root{nullptr}, cmp_func{def_cmp_func}{}
		
		// Operation - 
		void insert(T val){
			// BST insertion operation
			AVL_Node* prev_nd = find_node(val);  
			AVL_Node* chd_nd = new AVL_Node(val);
			add_child(prev_nd, chd_nd);
			
			// Balance the tree
			for(AVL_Node* nd_ptr = prev_nd ; nd_ptr != nullptr ; nd_ptr = nd_ptr->parent){
				const int& bf = cal_balance(nd_ptr);
				
				// Left bias unbalance
				if( bf > 1 ){		
					if(val > nd_ptr->left->val)
						nd_ptr->left = Left_rotate(nd_ptr->left);

					// update parent's pointer
					AVL_Node* par_ptr = nd_ptr->parent;
					if(par_ptr != nullptr && par_ptr->right == nd_ptr)
						par_ptr->right = Right_rotate(nd_ptr);
					else if(par_ptr != nullptr && par_ptr->left == nd_ptr)
						par_ptr->left = Right_rotate(nd_ptr);
					else
						Right_rotate(nd_ptr);
					
				// Right bias unbalance
				}else if(bf < -1){		
					if(val < nd_ptr->right->val)
						nd_ptr->right = Right_rotate(nd_ptr->right);

					// update parent's pointer
					AVL_Node* par_ptr = nd_ptr->parent;
					if(par_ptr != nullptr && par_ptr->right == nd_ptr)
						par_ptr->right = Left_rotate(nd_ptr);
					else if(par_ptr != nullptr && par_ptr->left == nd_ptr)
						par_ptr->left = Left_rotate(nd_ptr);
					else  // nd_ptr equal root 
						Left_rotate(nd_ptr);

				// else, the sub-tree is already balanced
				}else{  
					nd_ptr->height = get_max(get_height(nd_ptr->left), get_height(nd_ptr->right)) + 1;
				} 

				// finally update the new root pointer 
				if(nd_ptr->parent == nullptr)
					this->root = nd_ptr;
			}
		}


		void remove(T val){
			// BST remove operation
			AVL_Node* ptr_nd = find_node(val);
			if(ptr_nd == nullptr || ptr_nd->val != val){
				cerr << "ERROR_MESSAGE : The removed node have not found." << endl;
				return;
			}

			// Case 1. Single-side is nullptr, then the simple splice is execute.
			AVL_Node* tmp = ptr_nd->parent;
			if(ptr_nd->left == nullptr || ptr_nd->right == nullptr){
				splice(ptr_nd);
				safe_del_ptr<AVL_Node>(ptr_nd);
			
			// Case 2. Both side have node.
			}else{  
				AVL_Node* replce_nd = ptr_nd->right;
				// find the smallest node, which greate then ptr_nd in right sub-tree.
				while(replce_nd->left != nullptr){replce_nd = replce_nd->left;}
				ptr_nd->val = replce_nd->val;
				splice(replce_nd);
				safe_del_ptr<AVL_Node>(replce_nd);
			}
			
			// early return for root
			if (this->root == nullptr) 
    			return;

			// Balance the tree
			for(AVL_Node* nd_ptr = tmp ; nd_ptr != nullptr ; nd_ptr = nd_ptr->parent){
				const int& bf = cal_balance(nd_ptr);
				
				// Left bias unbalance
				if( bf > 1 ){		
					if( cal_balance(nd_ptr->left) >= 0 )
						nd_ptr->left = Left_rotate(nd_ptr->left);

					// update parent's pointer
					AVL_Node* par_ptr = nd_ptr->parent;
					if(par_ptr != nullptr && par_ptr->right == nd_ptr)
						par_ptr->right = Right_rotate(nd_ptr);
					else if(par_ptr != nullptr && par_ptr->left == nd_ptr)
						par_ptr->left = Right_rotate(nd_ptr);
					else
						Right_rotate(nd_ptr);
					
				// Right bias unbalance
				}else if(bf < -1){		
					if( cal_balance(nd_ptr->right) <= 0 )
						nd_ptr->right = Right_rotate(nd_ptr->right);

					// update parent's pointer
					AVL_Node* par_ptr = nd_ptr->parent;
					if(par_ptr != nullptr && par_ptr->right == nd_ptr)
						par_ptr->right = Left_rotate(nd_ptr);
					else if(par_ptr != nullptr && par_ptr->left == nd_ptr)
						par_ptr->left = Left_rotate(nd_ptr);
					else  // nd_ptr equal root 
						Left_rotate(nd_ptr);

				// else, the sub-tree is already balanced
				}else{  
					nd_ptr->height = get_max(get_height(nd_ptr->left), get_height(nd_ptr->right)) + 1;
				} 

				// finally update the new root pointer 
				if(nd_ptr->parent == nullptr)
					this->root = nd_ptr;
			}

			
		}

		void BF_print(){
			Smart_queue<AVL_Node*> nd_que(this->root);
			while(!nd_que.is_empty()){
				AVL_Node* tmp_ptr = nd_que.pop();
				if(tmp_ptr == nullptr)
					continue;

				cout << tmp_ptr->val << " ";
				nd_que.push(tmp_ptr->left);
				nd_que.push(tmp_ptr->right);
			}
		}

};

// alias Tree type DS -
template<class T>
using BST = Binary_search_tree<T>;
template<class T>
using AVL = AVL_tree<T>;


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
