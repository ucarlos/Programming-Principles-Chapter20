/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 03/25/2020 at 08:54 PM
 * 
 * Chapter20_04.cc
 * Find and fix the errors in the Jack-and-Jill example from §20.3.1 by using
 * STL techniques throughout.
 *
 * NOTICE:
 * The code for get_from_jack and get_from_jill are imported from
 * Chapter20_02.cc
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <vector>
#include <new>
#include <fstream>
#include <stdexcept>
#include <experimental/filesystem>
#include <memory>
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

template<typename Iterator> Iterator high(Iterator first, Iterator last){
    // Return an iterator to the element in [First : last) that has the
    // highest value
    Iterator high = first;
    for (Iterator p = first; p != last; p++){
		if (*(high) < *(p)) high = p;
    }

    return high;
}


void get_from_jill(vector<double> &vec){
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

    double *list = new double[*count];
    
    *count = (*count + 1);
    is.clear();
    is.seekg(0);

    double multiplier = 1.05;
    
    for (int i = 0; is >> val && i < *count; i++)
		list[i] = multiplier * val;
    
    
    return list;
}



void fct(void){
    int count = 0;
    unique_ptr<double[]> jack_data {get_from_jack(&count)};
    vector<double> jill_data;
    get_from_jill(jill_data);

    double *jack_high = high(jack_data.get(), jack_data.get() + count);
    double *jill_high = (&jill_data[0], &jill_data[0] + jill_data.size());

    cout << "Jill's High: " << *jill_high << "\nJack's High: " <<  *jack_high
		 << "\n";
    
}

int main(void){
    fct();
    
}
