/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 03/24/2020
 * 
 * Chapter 20_01
 * If you haven't already, do all Try this exercises in the chapter.
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <new>
#include <vector>
#include <string>
#include <cstring>
#include <list>
#include <stdexcept>
#include <sstream>
using namespace std;

#define CHAR_SIZE (100)
#define INT_SIZE (5)

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


void try_this_main(void){ // Name was not intentional.
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

void char_array_test(char *_string, int length){
    cout << "Passed array:\n";
    for (int i = 0; i < length; i++)
		cout << _string[i] << "";
    cout << "\n";
    
    cout << "Is \"" << _string << "\" the same as \"Hello\" ? "
		 << (strncmp(_string, "Hello", 5))
		 << "\n";

}

void string_test(string str){
    cout << "Passed String: " << str << "\n";
    cout << "Is \"" << str << "\" the same as \"Hello\" ? : "
		 << (str == "Hello") << "\n";
}


void list_string_test(list<char> list){
    cout << "Passed list<string>:\n";
    for (auto &i : list)
		cout << i;
    cout << endl;
    
    std::list<char> check;
    check.push_back('H');
    check.push_back('e');
    check.push_back('l');
    check.push_back('l');
    check.push_back('o');

    cout << "Is the list " << "the same as \"Hello\"? ";
    bool test = true;

    if (list.size() != check.size())
		test = false;

    // Now check each character.
    std::list<char>::iterator it = check.begin();    
    for (auto &i : list){
		if (i != *it){
			test = false;
			break;
		}
		it++;
    }
    
    cout << boolalpha << test << endl;
    
}

void vector_test(vector<char> list){
    cout << "Passed vector:\n";
    for (char &i : list)
		cout << i;
    cout << endl;
    
    vector<char> check = {'H', 'e', 'l', 'l', 'o'};

    cout << "Is the vector the same as \"Hello\"?: ";
    bool test = true;
    
    if (list.size() != check.size())
		test = false;

    vector<char>::iterator it = check.begin();
    for (auto &i : list){
		if (i != *it){
			test = false;
			break;
		}
	
		it++;
    }

    cout << test << endl;

}


void string_main(void){
	cout << boolalpha;
    char char_string[CHAR_SIZE] = "Hello";
    string string_string = "Hello";
    list<char> list_string;

    list_string.push_back(char_string[0]);
    list_string.push_back(char_string[1]);
    list_string.push_back(char_string[2]);
    list_string.push_back(char_string[3]);
    list_string.push_back(char_string[4]);
    

    vector<char> vector_string;
    vector_string.push_back(char_string[0]);
    vector_string.push_back(char_string[1]);
    vector_string.push_back(char_string[2]);
    vector_string.push_back(char_string[3]);
    vector_string.push_back(char_string[4]);
    

    char_array_test(char_string, strlen(char_string));
    cout << endl;
    string_test(string_string);
    cout << endl;
    list_string_test(list_string);
    cout << endl;
    vector_test(vector_string);
    cout << endl;
}

// Do the previous Try this for an array of int , vector<int> , and list<int> each
// with the value { 1, 2, 3, 4, 5 } .

void check_int_array(int *array, int length){
    if (length < INT_SIZE){
		ostringstream os;
		os << "Length parameter should be at least " << INT_SIZE << "\n";
		throw runtime_error(os.str());
    }
    
    cout << "Passed Raw array:\n";
    for (int i = 0; i < length; i++)
		cout << array[i] << " ";
    cout << endl;

    
    cout << "Checking values from 1 to " << INT_SIZE << "\n";
    bool check{true};
    for (int i = 0; i < INT_SIZE; i++)
		if (array[i] != (i + 1))
			check = false;
    
    cout << "Result: " << check << endl;
}

void check_vector_array(vector<int> v){
    if (v.size() < INT_SIZE){
		ostringstream os;
		os << "Vector size should be at least " << INT_SIZE << "\n";
		throw runtime_error(os.str());
    }
    
    cout << "Passed Vector:\n";
    for (int &i : v)
		cout << i << " ";
    cout << endl;
    
    cout << "Checking values from 1 to " << INT_SIZE << "\n";
    bool check{true};
    for (int i = 0; i < INT_SIZE; i++)
		if (v[i] != (i + 1))
			check = false;

    cout << "Result: " << check << endl;
}


void check_list_array(list<int> l){
    if (l.empty() || l.size() < INT_SIZE){
		ostringstream os;
		os << "List size should be at least " << INT_SIZE << "\n";
		throw runtime_error(os.str());
    }

    cout << "Passed List:\n";
    for (auto &i: l)
		cout << i << " ";
    cout << endl;

    cout << "Checking values from 1 to " << INT_SIZE << "\n";
    bool check{true};
    list<int>::iterator it = l.begin();
    
    for (int i = 0; i < INT_SIZE; i++, it++){
		if (*it != (i + 1))
			check = false;
    }
    
    cout << "Result: " << check << endl;
}




void int_main(void){
    cout << boolalpha;
    int raw_array[INT_SIZE] = {1, 2, 3, 4, 5};
    vector<int> int_vec = {1, 2, 3, 4, 5};
    list<int> int_list = {1, 2, 3, 4, 5};
            


}


int main(void){
    
 
}
