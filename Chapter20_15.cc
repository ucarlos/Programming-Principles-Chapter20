/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 08/25/2020 at 04:11 PM
 * 
 * Chapter20_15.cc
 * Define a pvector to be like a vector of pointers except that it contains
 * pointers to objects and its destructor delete s each object.
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <vector>


template<class T> class pvector{ // Requires that T is some form of pointer
public:
    pvector()=default;
    explicit pvector(int size){ vec = std::vector<T>(size); }
    
    ~pvector();
    void push_back(T val) { vec.push_back(val); }
    void push_front(T val) { vec.push_front(val); }
    
private:
    std::vector<T> vec{};

};


//------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------

template<class T> pvector<T>::~pvector(){
    for (auto &i : vec){
	std::cout << "Destroying element at address " << i << "\n";
	delete i;
    }

}


int main(void){
    pvector<double *> plist;

    for (int i = 0; i < 10; i++){
	double *val = new double{1.02 * i};
	std::cout << "Creating element at address " << val << "\n";
	plist.push_back(val);
    }
    std::cout << std::endl;
    // Now call its destructor at the end of the scope
    
}
