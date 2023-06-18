/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 03/25/2020 at 09:49 PM
 * 
 * Chapter20_06.cc
 * 
 * Write a find-and-replace operation for Documents based on §20.6.2.
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iterator>

// Adding this for logging:
//#include <spdlog/spdlog.h>


using namespace std;
using Line = vector<char>;


//------------------------------------------------------------------------------
// Text_iterator
//------------------------------------------------------------------------------

class Text_iterator : public std::iterator<std::bidirectional_iterator_tag, char, char, const long*, long>{
    list<Line>::iterator ln;
    Line::iterator pos;
public:
    Text_iterator(list<Line>::iterator ll, Line::iterator pp)
		: ln{ll}, pos{pp} { }

    char& operator*()  { return *pos; }
    Line::iterator get_position() { return pos;}
    Line& getLine() { return *ln; }
    Text_iterator& operator++();
    Text_iterator& operator--();
    bool operator==(const Text_iterator &other) const
		{ return ln == other.ln && pos == other.pos; }
    bool operator!=(const Text_iterator &other) const
		{ return !(*this == other); }
    
};

Text_iterator& Text_iterator::operator++(){
    ++pos;
    
    if (pos == (*ln).end()){
		++ln;
		pos = (*ln).begin();
    }
    
    return *this;
}

Text_iterator& Text_iterator::operator--(){
    if (pos == (*ln).begin()){
		--ln;
		pos = (*ln).end();
    }
    else
		--pos;
    
    return *this;
}


template<typename Iter> void my_advance(Iter &p, int n){
    if (!n) return;
    if (n < 0){
		for (int i = 0; i > n; i--)
			--p;
    }
    else{
		for (int i = 0; i < n; i++)
			++p;
    }
}

//------------------------------------------------------------------------------
// Document
//------------------------------------------------------------------------------

struct Document{
    
    list<Line> line;
    Document() { line.push_back(Line{}); }
    Text_iterator begin() { return Text_iterator(line.begin(), line.begin()->begin()); }
    Text_iterator end(){
		auto last = line.end();
		--last;
		return Text_iterator(last, last->end());
    }

};

istream& operator>>(istream &is, Document &d){
    char stop = '~';
    for (char ch; is.get(ch);){
		if (ch == stop) // Break if null character is inputted.
			break;

		d.line.back().push_back(ch); // Add the character
		if (ch == '\n')
			d.line.push_back(Line{}); // Add another line.
	
    }
    if (d.line.back().size())
		d.line.push_back(Line{}); // Add final empty line.
    return is;


}
bool match(Text_iterator p, Text_iterator &last, const string &s){

    for (auto i = 0; i < s.length() && p != last; i++){
		if (*p == s[i])
			++p;
		else return false;
    }

    if (p == last) return false;
	
    return true;
    

}



Text_iterator find_txt(Text_iterator first, Text_iterator last, const string& s){

    if (s.size()==0) return last; // can’t find an empty string
    char first_char = s[0];
    while (true) {
		auto p = find(first,last,first_char);
		if (p==last || match(p,last,s)) return p;
		first = ++p; // look at the next character
    }
}

void replace_text(Text_iterator result, const string &search, const string &replace) {
	size_t search_size = search.size();
	size_t replace_size = replace.size();
		
	auto replace_iterator = replace.begin();
	Text_iterator start = result;

	// Choose the smaller size of the two so that the other 
	Text_iterator end = result;
	my_advance(end, min(search_size, replace_size));
	

	

	if (search_size == replace_size) {
		Text_iterator end = result;
		my_advance(end, search_size);

		auto string_it = replace.begin();
		for (Text_iterator it = result; result != end; ++it) {
			*it = *string_it++;
			++it;
		}		   			
	}

	else if (search_size > replace_size) {
		// You'll have to shrink some of the size
		auto string_it = replace.begin();
		Text_iterator end = result;
		my_advance(end, search_size + 1);

		Text_iterator it = result;
		for (; result != end; ++it) {
			*it = *string_it++;
			++it;
		}

		size_t new_end = replace_size - search_size;
		Text_iterator next = it;
		for (size_t i = 0; i < new_end; i++) {
			++next;
			auto current_position = it.get_position();
			it.getLine().erase(current_position);
			it = next;
		}
		   		 			
	}

	else {
		// You'll have to add some to the size:
		auto string_it = replace.begin();
			
		Text_iterator end = result;
		my_advance(end, replace_size + 1);

		Text_iterator it = result;
		for (; result != end; ++it) {
			*it = *string_it++;
			++it;
		}
			

		size_t new_end = search_size - replace_size;
		auto position = it.get_position();

		for (size_t i = replace_size; i < search_size; i++) {
			it.getLine().insert(++position, *string_it++);
		}
			

			
	}
					

}




Text_iterator find_and_replace_txt(Text_iterator first, Text_iterator last,
								   const string &search, const string &replace){

    Text_iterator result = find_txt(first, last, search);
    if (result == last)
		return last;
    else {


		
		
		auto start = result.get_position();
		my_advance(start, 1);
	   
		auto stop = result.get_position();
		my_advance(stop, search.length());

		// You'll have to overide it:

		// If the search is smaller then the replace,
		// you'll have to insert some space into the line.
		

		// Otherwise, if they're exactly the same size,
		// replacement is straight forward.


		// if the search is greater than the replace,
		// you'll have to remove some of the extra space.
		
		result.getLine().erase(start, stop);


		
		*result = replace[0];
	
		for (int i = 1; i < replace.size(); i++)
			result.getLine().inser t(replace[i]);

		return result;
    }
}



uint64_t count_words(Text_iterator first, Text_iterator last){
    return 0;
}


void print(Document &d){
    for (char & p : d){
        cout << p;
    }

}

int main(void){
    //spdlog::info("Creating the damn Document object:");
    Document d;

    // Remember to end your line with an ~
    cin >> d;
    find_and_replace_txt(d.begin(), d.end(), "little bitch?", "miserable pile of secrets?");
    //find_and_replace_txt(d.begin(), d.end(), "bitch?", "HARLOT?");
    print(d);

}


