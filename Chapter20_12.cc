/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 08/24/2020 at 11:48 PM
 * 
 * Chapter20_12.cc
 * Complete the definition of list from §20.4.1–2 and get the high() example
 * to run. Allocate a Link to represent one past the end.
 * -----------------------------------------------------------------------------
 */

#include <iostream>

using namespace std;
//------------------------------------------------------------------------------
// Function declarations
//------------------------------------------------------------------------------
template<typename Iter> void advance_to(Iter i1, Iter i2);

//------------------------------------------------------------------------------
// Link class
//------------------------------------------------------------------------------
template<typename Elem> struct Lonk{
    Lonk *prev{nullptr};
    Lonk *succ{nullptr};
    Elem val{Elem{}};
    
    Lonk()=default;
    Lonk(Elem value) : val{value} { }
};


//------------------------------------------------------------------------------
// List class
//------------------------------------------------------------------------------
template<typename Elem> class list{
public:
    // Default constructor
    list() {
	// Just make a tail
	tail = new Lonk<Elem>(Elem());
	tail->succ = tail->prev = nullptr;
    }
    class iterator;

    iterator begin() { return iterator(head); }
    iterator end() { return iterator(tail); }
    
    iterator insert(iterator p, const Elem &v);
    iterator erase(iterator p);

    void push_back(const Elem &v);
    void push_front(const Elem &v);

    void pop_front();
    void pop_back();

    Elem& front();
    Elem& back();
    
    void clear();
    [[nodiscard]] int size() const { return sz; }
    // Destructor
    ~list() { clear(); }
private:
    Lonk<Elem> *head{nullptr};
    Lonk<Elem> *tail{nullptr};
    int sz{0};
};

//------------------------------------------------------------------------------
// Class definitions
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Iterator definition
//------------------------------------------------------------------------------

template<typename Elem> class list<Elem>::iterator{
public:
    iterator(Lonk<Elem> *p) : curr{p} { }

    iterator& operator++() { curr = curr->succ; return *this; }
    // Define Postfix as well
    iterator& operator++(int) { curr = curr->succ; return *this; }
    iterator& operator--() { curr = curr->prev; return *this; }
    iterator& operator--(int) { curr = curr->prev; return *this; }
    
    Elem& operator*() { return curr->val; }

    const Lonk<Elem>& get_pointer() const { return *curr; }
    bool operator==(const iterator &b) const { return curr == b.curr; }
    bool operator!=(const iterator &b) const { return curr != b.curr; }
    
private:
    Lonk<Elem> *curr;
};


//------------------------------------------------------------------------------
// Class function definitions
//------------------------------------------------------------------------------

template<typename Elem> void list<Elem>::pop_back(){
    if (begin() == end()) return; // If empty
    if (tail->prev == nullptr) return; // If tail is the only
    
    auto last = tail->prev;
    if (last == head){
	// Delete head and set to null
	delete last;
	head = tail->prev = nullptr;
	sz--;
	return;
	
    }
    
    auto second_last = tail->prev->prev;

    // Remove all pointers to last and delete it
    last->prev = last->succ = nullptr; 
    second_last->succ = tail;
    tail->prev = second_last;
    delete last;    
    sz--;
    
}

template<typename Elem> void list<Elem>::pop_front(){
    if (begin() == end()) return;
    if (head == nullptr) return;

    
    auto next = head->succ;
    // Handles head case
    if (next == tail){ // Delete head and set it to nullptr.
	delete head;
	head = tail->prev = nullptr;
	return;
    }

    // Otherwise
    next->prev = head->succ = nullptr;
    delete head;
    head = next;
    
}

template<typename Elem> void list<Elem>::push_front(const Elem &v){
    // Create a new lonk
    // Set the prev of head to lonk
    // Set the succ of lonk to head
    // Set head to lonk
    
    Lonk<Elem> *l = new Lonk<Elem>(v); // Create a new lonk
    
    if (tail == nullptr){ // Create tail
	Lonk<Elem> *last = new Lonk<Elem>();
	tail = last;
    }
    
    if (head == nullptr){
	l->succ = tail;
	l->prev = nullptr;
	head = l;
	return;
	sz++;
    }
    
    l->succ = head; // Set succ to head
    l->prev = nullptr; // Set prev to null
    
    head->prev = l; // Set head's prev to lonk
    head = l;
    sz++;
}

template<typename Elem> void list<Elem>::push_back(const Elem &v){
    Lonk<Elem> *l = new Lonk<Elem>(v);
    
    if (tail == nullptr){
	// Create tail
	Lonk<Elem> *last = new Lonk<Elem>();
	tail = last;
    }
       
    auto prev_link = tail->prev;
    if (prev_link == nullptr){ // make link head
	tail->prev = head = l;
	l->prev = nullptr;
	l->succ = tail;
	sz++;
	return;
    }
    
    l->succ = tail;
    l->prev = prev_link;
    prev_link->succ = tail->prev = l;
    sz++;
}

template<typename Elem> void list<Elem>::clear(){
    if (begin() == end()) return;

    auto start = head;
    auto end = tail;
    auto temp = head;

    while (start != end){
	temp = start->succ;
	delete start;
	start = temp;
    }

    // Now delete tail
    delete end;

    // reset list atributes
    head = tail = nullptr;
    sz = 0;
}

template<typename Elem>
typename list<Elem>::iterator list<Elem>::insert(list::iterator p, const Elem &v) {
    // Return head if p is begin
    if (p == begin()){
	push_front(v);
	return head;
    }

    if (p == end()){
	push_back(v);
	return tail->prev;
    }
    
    //otherwise,
    Lonk<Elem> l = new Lonk<Elem>(v);
    auto prev = p->prev;
    l->succ = p;
    l->prev = prev;
    p->prev = l;
    prev->succ = p;

    return l;           
}

template<typename Elem> Elem& list<Elem>::front() {
    return *begin();
}

template<typename Elem> Elem& list<Elem>::back(){
    return *--end();
}
//------------------------------------------------------------------------------
// Advance_to function() --> iter it1, it2
// Assume that the iterators are AT LEAST forward iterators
// Advance it to it2, Assuming that both iterators are in the same sequence.
//------------------------------------------------------------------------------
template<class Iter> void advance_to(Iter i1, Iter i2){
    while (i1 != i2)
	i1++;
}

//------------------------------------------------------------------------------
// High function
//------------------------------------------------------------------------------
template<class Iter> Iter high(Iter begin, Iter end){
    if (begin == end) return end;

    Iter high = begin;
    Iter p = begin;
    for (Iter p = begin++; p != end; p++)
	if (*p > *high) high = p;

    return high;
}



int main(void){
    list<double> my_list;

    // Now print the list:
    double temp;
    for (int i = 0; i < 10; i++){
	temp = 1.05 * i;
	my_list.push_back(temp);
    }

    // Print contents of list:
    cout << "Contents of List:\n";
    for (auto &i : my_list)
	cout << i << " ";
    cout << endl;
    auto result = high(my_list.begin(), my_list.end());
    cout << "Highest value in list: " << *result << "\n";

    // Now pop the front and back of the list
    my_list.pop_back();
    my_list.pop_front();

    // Now restore them
    my_list.push_front(0);
    my_list.push_back(1.05 * 10);
    
}


    
