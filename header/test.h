template<typename T>
T data_gen(){
    smart_array<char> sm;
	smart_array<char> sm2;
	
	for(int idx=0; idx < MAXLEN ; ++idx){
		int tmp = (rand()%DIGRNG) + 97;
		char chr = static_cast<char>(tmp);
		cout << "outer : " << chr << " ; ";
		sm.add(chr);
		sm2.add(chr);
	}
    return T;
}

