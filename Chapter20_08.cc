/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 03/25/2020 at 10:57 PM
 * 
 * Chapter20_08.cc
 * 
 * Define a function that counts the number of characters in a Document.
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cstdint>
#include <experimental/filesystem>
#include <fstream>
#include <memory>

using namespace std;
using Line = vector<char>;
string file_name = "../Navy Seals Copypasta.txt";
string alt_file_name = "./Navy Seals Copypasta.txt";


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
    if (p == last) return false;

    for (auto i = 0; i < s.length() && p != last; i++){
		if (*p == s[i])
			++p;
		else return false;
    }

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

Text_iterator find_and_replace_txt(Text_iterator first, Text_iterator last,
								   const string &search, const string &replace){

    Text_iterator result = find_txt(first, last, search);
    if (result == last)
		return last;
    else{
		auto start = result.get_position();
		my_advance(start, 1);
		auto stop = result.get_position();
		my_advance(stop, search.length());

		result.getLine().erase(start, stop);

		*result = replace[0];
	
		for (int i = 1; i < replace.size(); i++)
			result.getLine().push_back(replace[i]);

		return result;
    }
}

uint64_t count_characters(Text_iterator first, Text_iterator last){
    uint64_t count = 0;

    while (first != last){
		count++;
		++first;
    }
    
    return count;

}

void print(Document &d){
    for (char & p : d){
        cout << p;
    }

}

int main(void){
    Document d;
    ifstream is;
    handle_file(is);
    is >> d;
    // find_and_replace_txt(d.begin(), d.end(), "little bitch?", "miserable pile of secrets?");
    // find_and_replace_txt(d.begin(), d.end(), "bitch?", "HARLOT?");
    is.close();
    uint64_t value = count_characters(d.begin(), d.end());
    cout << "Number of characters in Document: " << value << endl;
    

}



