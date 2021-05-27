#include"../header/DataStructure.h"
#include"../source/DataStructure.cpp"

#include"Blkbox_Tester.h"

class data_structure_tester{
    public:
        void static test_sm_arr(){
            // data generation phase
            const uint32_t MAXLEN = 25;
            const int32_t DIGRNG = 100;

            srand(time(NULL));
            int32_t* arr = uniform_data_gen(MAXLEN, DIGRNG);
            
            Smart_array<int32_t> sm_arr, tmp_arr;
            // add elements
            for(int idx=0 ; idx < MAXLEN ; ++idx){
                sm_arr.add(arr[idx]);
                cout << " Elem : " << sm_arr[idx] << " ; len : " << sm_arr.get_siz();
            }
            tmp_arr = sm_arr;
            cout << "\n\n After assignment : \n\n" ;
            
            // remove elements
            for(int idx=MAXLEN ; idx > 0 ; --idx){
                tmp_arr.remove(idx);
                cout << " Elem : " << tmp_arr[idx-1] << " ; len : " << tmp_arr.get_siz();
            }
        }




};
