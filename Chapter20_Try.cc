/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 03/07/2020
 * 
 * Chapter20_Try
 * 
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <new>
#include <string>

// Write a function void copy(int* f1, int* e1, int* f2) that copies the elements
// of an array of int s defined by [ f1 : e1 ) into another [ f2 : f2+(e1–f1) ). Use only
// the iterator operations mentioned above (not subscripting).
void copy(int *f1, int *e1, int *f2){
    // If *f1 and *e1 are not in the same array,
    // then this function will crash.
    int *p = f1;
    for (p; p != e1; p++)
		*(f2 + (p - f1)) = *p;

}


template<typename Iter> void advance (Iter &p, int n){
    if (!n) return; // Return if n is zero
    else if (n < 0){ // If n is negative.
		for (int i = 0; i > n; i--)
			p--;

    }
    else { // If n is positive
		for (int i = 0; i < n; i++)
			p++;
    }
	
}

void print_list(int *list, int list_length){
    for (int i = 0; i < list_length; i++)
		std::cout << list[i] << " ";
    std::cout << "\n";

}

int main(void){
    int size = 5;
    int *list = new int[size]{1, 2, 3, 4, 5};
    int *new_list = new int[size]{0};

    std::cout << "Contents of new_list (Before):\n";
    print_list(new_list, size);    

    copy(list, &list[5], new_list);
    
    std::cout << "Contents of new_list (After):\n";
    print_list(new_list, size);    

    delete[] list;
    delete[] new_list;


}
