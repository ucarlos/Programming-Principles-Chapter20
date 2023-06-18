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

class Text_iterator : public std::iterator<std::bidirectional_iterator_tag, char, char, const long*, long> {
    list<Line>::iterator ln;
    Line::iterator pos;
public:
    Text_iterator(list<Line>::iterator ll, Line::iterator pp)
		: ln{ll}, pos{pp} { }

    char& operator*()  { return *pos; }
    Line::iterator get_position() { return pos;}
    list<Line>::iterator get_ln_iterator() const { return ln; };
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
bool match(Text_iterator p, Text_iterator last, const string &s){

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

void replace_text(Document &d, Text_iterator &result, const string &search, const string &replace) {
	size_t search_size = search.size();
	size_t replace_size = replace.size();
	size_t size_difference = max(search_size, replace_size) - min(search_size, replace_size);
		
	auto replace_iterator = replace.begin();
	Text_iterator begin = result;
	// Choose the smaller size of the two so that we can copy all of that over.
	Text_iterator end = result;

    size_t advance_size = min(search_size, replace_size);
	my_advance(end, advance_size);
	
	for (; begin != end; ++begin) {
		*begin = *replace_iterator++;
        std::string temp(begin, end);
	}
	
	// If search_size > replace_size, shrink the size
	if (search_size > replace_size) {
		my_advance(end, size_difference);

		Text_iterator temp = begin;
        my_advance(temp, -1);

		for (size_t i = 0; i < size_difference; i++) {
			auto current_position = begin.get_position();
			begin.get_ln_iterator()->erase(current_position);
			begin = temp;
            ++begin;
            //std::string temp(begin, end);
		}

        begin.get_ln_iterator()->shrink_to_fit();

	}

	else if (search_size < replace_size) {
		// If search_size < replace_size, increase the size
		auto position = begin.get_position();
        begin.get_ln_iterator()->insert(position, replace_iterator, replace.end());
        //begin.getLine().insert(position, replace_iterator, replace.end());


	}
	// Otherwise you're done.
}


Text_iterator find_and_replace_txt(Document &d, Text_iterator first, Text_iterator last,
								   const string &search, const string &replace){

    Text_iterator result = find_txt(first, last, search);
    if (result == last) {
		return last;
	}
    else {
		replace_text(d, result, search, replace);
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
	// Example: What the fuck did you just fucking say about me, you little bitch? ~
    cin >> d;
    //find_and_replace_txt(d, d.begin(), d.end(), "little bitch?", "miserable pile of secrets?");
    find_and_replace_txt(d, d.begin(), d.end(), "little bitch?", "slut");
    //find_and_replace_txt(d.begin(), d.end(), "bitch?", "HARLOT?");
    print(d);

}


