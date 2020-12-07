/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 03/25/2020 at 06:43 PM
 * 
 * Chapter20_03.cc
 * Look at the palindrome examples (§18.7); redo the Jack-and-Jill example
 * from §20.1.2 using that variety of techniques.
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <vector>
#include <new>
#include <stdexcept>
using namespace std;

double* high(double list[], int length);
double* high(double *begin, double *end);

double* high(double list[], int length){
    return (length <= 0)? &list[0] : high(list, list + length);
}


double* high(double *begin, double *end){
    if (begin == end) return begin;
    
    double *val = begin;
    for (double *i = begin + 1; i != end; i++){
		if ((*i) > (*val))
			val = i;
    }

    return val;
}

double* high(vector<double> &vec){
    if (vec.empty())
		throw runtime_error("Empty Vector passed to high()");
    
    double *val = &vec[0];

    for (double &i : vec){
		if (i > (*val))
			*val = i;
    }
    
    return val;

}


int main(void){
    int length = 6;
    double raw_array[] = {2, 2.7, 2.71, 2.718, 2.7182, 2.71828};
    double *raw_result = high(raw_array, length);
    vector<double> list = {3, 3.1, 3.14, 3.141, 3.1415, 3.14159};
    double *vector_result = high(list);
    cout << "Highest value in raw array: " << *raw_result << endl;
    cout << "Highest value in vector: " << *vector_result << endl;
    
    

}
