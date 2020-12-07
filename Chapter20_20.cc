/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 08/25/2020 at 08:09 PM
 * 
 * Chapter20_20.cc
 * Run a small timing experiment to compare the cost of using vector and list.
 * You can find an explanation of how to time a program in §26.6.1. Generate
 * N random int values in the range [0:N ). As each int is generated, insert
 * it into a vector<int> (which grows by one element each time). Keep the
 * vector sorted; that is, a value is inserted after every previous value that 
 * is less than or equal to the new value and before every previous value that
 * is larger than the new value. Now do the same experiment using a list<int> 
 * to hold the int s. For which N is the list faster than the vector ? 
 * Try to explain your result. This experiment was first suggested by 
 * John Bentley.
 *
 * Note: 
 * Compile this program by doing
 * g++ Chapter20_02.cc -g -pthread -o Chapter20_02
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <chrono>
#include <vector>
#include <random>
#include <algorithm>
#include <list>
#include <thread>


using namespace std;
unsigned long max_int = 100000;

void test_list(void){
    list<unsigned long> lst;
    
    std::random_device rand;
    std::mt19937 merse{rand()};
    std::uniform_int_distribution<unsigned long> dist(0, max_int);

    unsigned long val;
    cout << "Inserting and then Sorting " << max_int
		 << " random integers for the list:\n";
    
    auto t1 = std::chrono::system_clock::now();
    for (unsigned long i = 0; i < max_int; i++){
		val = dist(merse);
		lst.push_back(val);
		lst.sort();
    }    
   
    auto t2 = std::chrono::system_clock::now();
    cout << "It took "
		 << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count()
		 << " milliseconds to insert and then sort "
		 << max_int << " numbers into a list.\n";
    
}

void test_vector(void){
    vector<unsigned long> vec;
    std::random_device rand;
    std::mt19937 merse{rand()};
    std::uniform_int_distribution<unsigned long> dist(0, max_int);

    unsigned long val;
    cout << "Inserting and then Sorting " << max_int
		 << " random integers for the vector.\n";
    auto t1 = std::chrono::system_clock::now();
    for (unsigned long i = 0; i < max_int; i++){
		val = dist(merse);
		vec.push_back(val);
		sort(vec.begin(), vec.end());
    }
    
    auto t2 = std::chrono::system_clock::now();
    cout << "It took "
		 << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count()
		 << " milliseconds to insert and then sort "
		 << max_int << " numbers into a vector.\n";


}

int main(void){
    thread thread1(test_list);
    thread thread2(test_vector);

    // test_list();
    // test_vector();
    thread1.join();
    thread2.join();
    
}
