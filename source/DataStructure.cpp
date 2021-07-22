#include"../header/DataStructure.h"

// Disable the assert statement.
//#define NDEBUG

// NameSpace :
//    @ Memory_Manager -
// Note : C++ automatically ignore the nullptr delete.
template<typename T>
void Mem_manger::safe_del_ptr(T* del_ptr){
    delete del_ptr;
    del_ptr = nullptr;
}

template<typename T>
void Mem_manger::safe_del_doub_ptr(T** del_ptr){
    delete *del_ptr;
    *del_ptr = nullptr;
}

template<typename T>
void Mem_manger::safe_del_ref_ptr(T*& del_ptr){
    delete del_ptr;
    del_ptr = nullptr;
}

template<typename T>
void Mem_manger::safe_del_all_ref_ptr(T*& del_ptr){
    delete [] del_ptr;
    del_ptr = nullptr;
}

//    @ Default_Setting -
template<typename T>
short default_setting::defau_cmp(T x, T y){  
    if(x > y)
        return 1;
    else if(x < y)
        return 0; 
    else // triple compare function for no duplicate element.
        return -1;
 }



// Array type DS :

// @ Smart_Array =
//  Constructor -
template<typename T>
Smart_array<T>::Smart_array():arr{nullptr}, ptr{0}, siz{1}{}

template<typename T>
Smart_array<T>::Smart_array(uint alloc_siz):arr{nullptr}, ptr{alloc_siz}, siz{alloc_siz}{ arr = new T [siz]; }

template<typename T>
Smart_array<T>::Smart_array(T val):arr{nullptr}, ptr{1}, siz{4}{ arr = new T [siz]{val}; }

template<typename T>
Smart_array<T>::Smart_array(const initializer_list<T>& lst):Smart_array(){ for(auto elem : lst) add(elem); }

//  Utility -
template<typename T>
bool Smart_array<T>::chk_bnd(const int &idx){ return (idx <= ptr && idx >=0) ? true : false; }

template<typename T>
void Smart_array<T>::shrink_arr(){
    T *tmp = arr;
    arr = new T[siz/=2];
    for(int idx=0; idx < ptr; ++idx)
        arr[idx] = tmp[idx];
}

// Getter for the assign operator - 
template<typename T>
T* Smart_array<T>::get_arr(){ return this->arr; }

template<typename T>
int Smart_array<T>::get_ptr(){ return this->ptr; }

template<typename T>
int Smart_array<T>::get_siz(){ return this->siz; }

//  Operator -
template<typename T>
T& Smart_array<T>::operator[](int idx){
    assert(chk_bnd(idx));
    return arr[idx];
}

template<typename T>
void Smart_array<T>::operator=(Smart_array<T>& tmp_arr) {
    if(arr != nullptr)
        delete [] arr;
    
    this->siz = tmp_arr.get_siz();
    this->ptr = tmp_arr.get_ptr();
    this->arr = tmp_arr.get_arr();
}

// Operation -
template<typename T>
void Smart_array<T>::add(T val){
    // increase size.
    if(ptr+1 >= siz/2){
        T* tmp = arr;
        arr = new T[ siz*=2 ];  // try-catch, return false.
        for(int idx=0 ; idx < ptr ; ++ idx)
            arr[idx] = tmp[idx];
    }
    arr[ptr++] = val;
}

template<typename T>
void Smart_array<T>::remove_bk(){
    // decrease size.
    if(ptr-1 <= siz/4)
        shrink_arr();
    --ptr;
}

template<typename T>
void Smart_array<T>::remove(const int& rmv_idx){
    if(chk_bnd(rmv_idx)){
        if(ptr-1 <= siz/4)
            shrink_arr();
        for(int idx=rmv_idx; idx < ptr; ++idx)
            arr[idx] = arr[idx+1];
        --ptr;
    }
}
// end of Smart_Array @


// @ Smart_Stack =
//  Constructor -
template<typename T>
Smart_stack<T>::Smart_stack():arr(), curr_ptr{-1}{};

template<typename T>
Smart_stack<T>::Smart_stack(T val):arr(val), curr_ptr{-1}{};

// Operation -
template<typename T>
T Smart_stack<T>::top(){ return arr[curr_ptr]; }

template<typename T>
void Smart_stack<T>::push(T val){
    arr.add(val);
	++curr_ptr;
}

template<typename T>
T Smart_stack<T>::pop(){
    T& tmp_val = top();
    arr.remove(curr_ptr--);
    return tmp_val;
}

template<typename T>
bool Smart_stack<T>::is_empty(){ return (curr_ptr == -1) ? true : false; }
// end of Smart_Stack @


// @ Smart_Queue =
//  Constructor -
template<typename T>
Smart_queue<T>::Smart_queue():arr(), curr_ptr{-1}{};

template<typename T>
Smart_queue<T>::Smart_queue(T val):arr(val), curr_ptr{0}{};

// Operation -
template<typename T>
T Smart_queue<T>::top(){ return arr[0]; }  // "copy return" to ensure the security.

template<typename T>
void Smart_queue<T>::push(T val){
    arr.add(val);
    ++curr_ptr;
}

template<typename T>
T Smart_queue<T>::pop(){
    T tmp_val = top();
    arr.remove(0);
    --curr_ptr;
    return tmp_val;
}

template<typename T>
bool Smart_queue<T>::is_empty(){ return (curr_ptr == -1) ? true : false; }
// end of Smart_Queue @


// List type DS :

// @ Double_linked_list =
//   @Composite object -
//      Node Constructor -
template<typename T>
Double_linked_list<T>::Node::Node():val{}, next{nullptr}, prev{nullptr}{}

template<typename T>
Double_linked_list<T>::Node::Node(const T& val):val{val}, next{nullptr}, prev{nullptr}{}

//  Constructor -
template<typename T>
Double_linked_list<T>::Double_linked_list():dummy(), siz{0}{ 
    this->dummy.next = this->dummy.prev = &this->dummy; 
}

//  Utility -
template<typename T>
typename Double_linked_list<T>::Node* Double_linked_list<T>::find_prev_node(const int& idx){
    assert(idx <= siz && idx >= 0);

    Node* tmp_ptr = &this->dummy;
    for(int jdx=0 ; jdx < idx ; ++jdx)
        tmp_ptr = tmp_ptr->next;
    return tmp_ptr;
}

//  Operation -
//      add type -
template<typename T>
void Double_linked_list<T>::insert_bk(int idx, T val){
    Node* prev_nd = find_prev_node(idx);
    Node* new_nd = new Node(val);

    // update new_nd ptr first
    new_nd->prev = prev_nd;
    new_nd->next = prev_nd->next;

    // update prev_nd ptr
    prev_nd->next->prev = new_nd;
    prev_nd->next = new_nd;
    ++siz; // add the size.
}

template<typename T>
void Double_linked_list<T>::add_front(T val){ insert_bk(0, val); }

template<typename T>
void Double_linked_list<T>::append_back(T val){ insert_bk(siz, val); }

//     remove type -
template<typename T>
void Double_linked_list<T>::remove_idx_bk(int idx){
    Node* prev_nd = find_prev_node(idx);
    Node* del_nd_ptr = prev_nd->next;
    // Update the ptr of corresponding nodes.
    prev_nd->next = prev_nd->next->next;
    prev_nd->next->prev = prev_nd;
    // delete the node.
    safe_del_ptr<Node>(del_nd_ptr);
    --siz;
}

template<typename T>
void Double_linked_list<T>::remove_value(T val){
    Node* tmp_ptr = this->dummy.next;
    Node* prev_nd = nullptr;
    for(int idx=0 ; (idx <= siz) ; ++idx){
        if(tmp_ptr->val == val){
            prev_nd = tmp_ptr;
            break;
        }
        tmp_ptr = tmp_ptr->next;
    }

    // check the value in the list.  
    if(prev_nd == nullptr){
        cout << "Value not found.";
        return;
    }

    Node* del_nd_ptr = prev_nd->next;
    // Update the ptr of corresponding nodes.
    prev_nd->next = prev_nd->next->next;
    prev_nd->next->prev = prev_nd;
    // delete the node.
    safe_del_ptr<Node>(del_nd_ptr);
    --siz;
}

// Search -
template<typename T>
bool Double_linked_list<T>::find_val(T val){
    Node* tmp_ptr = this->dummy.next;
    for(int idx=0 ; idx < siz ; ++idx){
        if(tmp_ptr->val == val)
            return true;
        tmp_ptr = tmp_ptr->next;
    }
    return false;
}

template<typename T>
int Double_linked_list<T>::find_idx(T val){
    Node* tmp_ptr = this->dummy.next;
    for(int idx=0 ; idx < siz ; ++idx){
        if(tmp_ptr->val == val)
            return idx;
        tmp_ptr = tmp_ptr->next;
    }
    return -1;
}

//  View -
template<typename T>
void Double_linked_list<T>::print(){
    Node* tmp_ptr = this->dummy.next;
    for(int idx=0 ; idx < siz ; ++idx){
        cout << tmp_ptr->val << " ";
        tmp_ptr = tmp_ptr->next;
    }
    cout << "\n" ;
}
// end of Double_linked_list@


// Tree type DS :

// @ Binary_Search_Tree =
//   @Composite object -
//      Node Constructor -
template<typename T>
Binary_search_tree<T>::Node::Node():val{}, left{nullptr}, right{nullptr}, parent{nullptr}{}

template<typename T>
Binary_search_tree<T>::Node::Node(T val):val{val}, left{nullptr}, right{nullptr}, parent{nullptr}{}

//  Constructor -
template<typename T>
Binary_search_tree<T>::Binary_search_tree():root{nullptr}, cmp_func{&defau_cmp<T>}{}

template<typename T>
Binary_search_tree<T>::Binary_search_tree(short (*def_cmp_func)(T, T)):root{nullptr}, cmp_func{def_cmp_func}{}


//  Utility -
template<typename T>
typename Binary_search_tree<T>::Node* Binary_search_tree<T>::find_node(T val){
    Node* prev_ptr = nullptr;
    for(Node* tmp_ptr = this->root ; tmp_ptr != nullptr ; ){
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
    // in case of 'not found the node', return their parent node ptr.
    return prev_ptr;
}

template<typename T>
void Binary_search_tree<T>::add_child(Node* prev_nd, Node* chd_nd){
    if(prev_nd == nullptr){
        this->root = chd_nd;
    }else{
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
        // update child pointer.
        chd_nd->parent = prev_nd;
    }
}

template<typename T>
void Binary_search_tree<T>::splice(Node* ptr_nd){
    /* remove node confirm that the ptr_nd have successor in single side.
                                                      Case 1.   ;    Case 2.   */
    Node* succsor_nd = (ptr_nd->left != nullptr) ? ptr_nd->left : ptr_nd->right;
    
    if(ptr_nd == this->root){  // for remove the root.
        this->root = succsor_nd;
    }else{              
        Node* par_nd = ptr_nd->parent;
        if(par_nd->left == ptr_nd)
            par_nd->left = succsor_nd;
        else
            par_nd->right = succsor_nd;

        if(succsor_nd != nullptr) succsor_nd->parent = par_nd;
    }
}

template<typename T>
void Binary_search_tree<T>::ord_recur(Order ord, Node* tmp_ptr){
    if(tmp_ptr == nullptr)
        return;

    switch(ord){
        case Order::pre_order :
            cout << tmp_ptr->val << " ";
            ord_recur(ord, tmp_ptr->left);
            ord_recur(ord, tmp_ptr->right);
            break;
        case Order::post_order :
            ord_recur(ord, tmp_ptr->left);
            ord_recur(ord, tmp_ptr->right);
            cout << tmp_ptr->val << " ";
            break;
        case Order::in_order :
            ord_recur(ord, tmp_ptr->left);
            cout << tmp_ptr->val << " ";
            ord_recur(ord, tmp_ptr->right);
            break;
    }
}

template<typename T>
uint32_t Binary_search_tree<T>::get_depth(Node* node){
    assert(node != nullptr);  // prevent nullptr. 
    uint32_t depth = 0;
    for( ; node != this->root ; node = node->parent){ ++depth; }
    return depth;
}

template<typename T>
uint32_t Binary_search_tree<T>::recur_get_height(Node* ptr_nd){
    if(ptr_nd == nullptr)
        return 0;
    const uint32_t& lft_hei = recur_get_height(ptr_nd->left) + 1;
    const uint32_t& rgt_hei = recur_get_height(ptr_nd->right) + 1;
    return (lft_hei >= rgt_hei) ? lft_hei : rgt_hei;
}

template<typename T>
uint32_t Binary_search_tree<T>::get_height(Node* ptr_nd){
    assert(ptr_nd != nullptr);
    return max(recur_get_height(ptr_nd->left), recur_get_height(ptr_nd->right)); 
}

// Operation -
template<typename T>
void Binary_search_tree<T>::insert(T val){
    Node* prev_nd = find_node(val);  // the find_node will return prev node when not found.
    Node* chd_nd = new Node(val);
    add_child(prev_nd, chd_nd);
}

template<typename T>
void Binary_search_tree<T>::remove(T val){
    Node* ptr_nd = find_node(val);
    if(ptr_nd == nullptr || ptr_nd->val != val){
        cerr << "ERROR_MESSAGE : The removed node have not found." << endl;
        return;
    }
    // Case 1. Single-side is nullptr, then the simple splice is execute.
    if(ptr_nd->left == nullptr || ptr_nd->right == nullptr){
        splice(ptr_nd);
        safe_del_ptr<Node>(ptr_nd);
    }else{  // Case 2. Both side have node.
        Node* replce_nd = ptr_nd->right;
        // find the smallest node, which greate then ptr_nd in right sub-tree.
        while(replce_nd->left != nullptr){replce_nd = replce_nd->left;}
        ptr_nd->val = replce_nd->val;
        splice(replce_nd);
        safe_del_ptr<Node>(replce_nd);
    }
       
}

// View -
template<typename T>
void Binary_search_tree<T>::order_traversal(Order ord){ ord_recur(ord, this->root); }

template<typename T>
void Binary_search_tree<T>::BF_print(){
    Smart_queue<Node*> nd_que(this->root);
    while(!nd_que.is_empty()){
        Node* tmp_ptr = nd_que.pop();
        if(tmp_ptr == nullptr)
            continue;

        cout << tmp_ptr->val << " ";
        nd_que.push(tmp_ptr->left);
        nd_que.push(tmp_ptr->right);
    }
}
// end of Binary_Search_Tree@




