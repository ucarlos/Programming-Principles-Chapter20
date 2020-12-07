/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 03/26/2020 at 01:21 AM
 * 
 * Chapter20_07.cc
 * Find the lexicographical last string in a unsorted vector<string>
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <experimental/filesystem>
using namespace std;

string file_name = "./Navy Seals Copypasta.txt";
string alt_file_name = "../Navy Seals Copypasta.txt";


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

template<typename Iter> Iter my_high(Iter first, Iter last){
    if (first == last)
		return last;
    Iter check = first;
    
    for (Iter it = ++first; it != last; it++){
		if (*(it) > (*check))
			check = it;
    }

    return check;
}

void read_from_file(vector<string> &vec){
    ifstream ifs;
    handle_file(ifs);

    for (string temp; ifs >> temp;){
		vec.push_back(temp);
    }

    ifs.close();
    
}

int main(void){
    vector<string> vec;
    read_from_file(vec);
    
    vector<string>::iterator it = my_high(vec.begin(), vec.end());
    if (it == vec.end())
		cout << "This file is empty. Please add some words!";
    else
		cout << "The lexicographical last string is " << *it << endl;

}
