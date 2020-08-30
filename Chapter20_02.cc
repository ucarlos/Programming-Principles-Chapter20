/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 03/25/2020
 * 
 * Chapter 20_02
 * Get the Jack-and-Jill example from §20.1.2 to work. Use input from a
 * couple of small files to test it.
 * If compiling with g++, link with -stdc++fs
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <vector>
#include <new>
#include <fstream>
#include <stdexcept>
#include <experimental/filesystem>
using namespace std;
string file_name = "../Chapter20_02.txt";
string alt_file_name = "./Chapter20_02.txt";


void handle_file(ifstream &is){
    // If file_name exists, then open it.
    if (experimental::filesystem::exists(file_name))
	is.open(file_name, ios_base::in);
    else if (experimental::filesystem::exists(alt_file_name))
	is.open(alt_file_name, ios_base::in);
    else{
	string error = "Could not find " + file_name +
	    " or " + alt_file_name + " . Exiting.";
	throw runtime_error(error);
    }
	     
}
double* high (double *begin, double *end){
    if (begin == end) return begin;
    
    double *val = begin;
    for (double *i = begin + 1; i != end; i++){
	if ((*i) > (*val))
	    val = i;
    }

    return val;
}

void read_from_file(vector<double> &vec){
    ifstream is;

    handle_file(is);

    for (double val; is >> val;){
	val *= 1.02;
	vec.push_back(val);
    }
    
}

double* get_from_jack(int *count){
    // Set count to zero if it isn't
    if (!(*count))
	*count = 0;

    ifstream is;
    
    handle_file(is);

    // Horrible inefficient code; open the file and find the count.
    double val;
    for (val; is >> val;){
	*count = (*count + 1);
    }

    if (!(*count)){
	string error = file_name + " is empty.";
	throw runtime_error(error);
    }

    // Otherwise
    *count = (*count + 1);
    double *list = new double[*count];

    is.clear();
    is.seekg(0);

    double multiplier = 1.05;
    
    for (int i = 0; is >> val && i < *count; i++)
	list[i] = multiplier * val;
    
    
    return list;
}

int main(void){
    vector<double> vec;
    read_from_file(vec);
    
    int count = 0;
    double *list = get_from_jack(&count);

    // cout << "Contents of vector:\n";
    // for (double &i : vec)
    // 	cout << i << " ";
    // cout << endl;

    // cout << "Contents of list:\n";
    
    // for (int i = 0; i < count - 1; i++)
    // 	cout << list[i] << " ";
    // cout << endl;

    double *vec_high = high(&vec[0], &vec[vec.size() - 1]);
    double *list_high = high(&list[0], &list[count - 1]);


    cout << "Highest value in vec_high: " << *vec_high << endl;
    cout << "Highest value in list_high: " << *list_high << endl;
    delete[] list;

    return 0;
}

