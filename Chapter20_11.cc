/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 08/24/2020 at 11:17 PM
 * 
 * Chapter20_11.cc
 * Given a list<int> as a (by-reference) parameter, make a vector<double>
 * and copy the elements of the list into it. Verify that the copy was complete
 * and correct. Then print the elements sorted in order of increasing value.
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <vector>
#include <list>
using namespace std;

vector<double> make_vector(list<int> &l){
    vector<double> vec(l.size());
    auto list_it = l.begin();

    for (auto &i : vec)
	i = *list_it++;
    
    return vec;
}

int main(void){
    list<int> l = {1, 2, 4, 8, 16, 32, 64, 128, 256};
    cout << "Contents of list:\n";
    for (int &i : l)
	cout << i << " ";
    cout << endl;

    cout << "Now copying list into vector...\n";
    vector<double> vd = make_vector(l);
    cout << "Contents of vector:\n";
    
    for (auto it = vd.end() - 1; it >= vd.begin(); it--)
	cout << *it << " ";
    cout << "\n";
    
    cout << endl;
}
