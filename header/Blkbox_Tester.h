#pragma once
#include<cstdint>
#include<ctime>
#include<cstdlib>

template<typename T>
bool no_duplicate_cmp(T* container, const T& val, const uint32_t& seris_len){
    for(uint32_t idx=0 ; idx < seris_len ; ++idx){
        if(container[idx] == val)
            return false;
    }
    return true;
}

int32_t* num_data_gen(uint32_t seris_len, int32_t num_rng){
    if(seris_len == 0) // trivial condition.
        return 0; 
    srand(time(0));
    
    int32_t* container = new int32_t [seris_len];
    for(uint32_t idx=0 ; idx < seris_len ; ++idx)
        container[idx] = rand()%num_rng + 1;
    return container;
}

int32_t* uniform_data_gen(uint32_t seris_len, int32_t num_rng){
    if(seris_len == 0) // trivial condition.
        return 0; 
    srand(time(0));
    
    int32_t* container = new int32_t [seris_len];
    
    for(uint32_t idx=0 ; idx < seris_len ; ){
        const int32_t& tmp_val = rand()%num_rng + 1;
        if(no_duplicate_cmp<int32_t>(container, tmp_val, idx)){
            container[idx] = tmp_val;
            ++idx;
        }
            
    }
         
    return container;
}

