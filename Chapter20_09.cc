/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 03/28/2020
 * 
 * Chapter20_09.cc
 *
 * Define a program that counts the number of words in a Document . Provide
 * two versions: one that defines word as “a whitespace-separated sequence of
 * characters” and one that defines word as “a sequence of consecutive alpha-
 * betic characters.” For example, with the former definition, alpha.numeric
 * and as12b are both single words, whereas with the second definition they
 * are both two words.
 *
 * Addendum
 * This is basically Chapter20_10.cc, with the ability to add any character
 * as a delimiter. So, I will count this as both.
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
// string file_name = "../Chapter20_09.txt";
// string alt_file_name = "./Chapter20_09.txt";

//------------------------------------------------------------------------------
// handle_file is a function that handles the opening of either file_name
// or alt_file_name.
//------------------------------------------------------------------------------

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


//------------------------------------------------------------------------------
// Punctuation class to handle whitespace, and any other characters in
// the document class.
// Fuck, how should I think about this?

// Shorthand for alphabetical : \a
// Shorthand for numerical: \n
// Shorthand for alphanumerical: \b

//------------------------------------------------------------------------------

/*
  So how will this work? If not consecutive alphabetical or numerical, then increment count.
  Or if 

 */

class Punct{
public:
    Punct()=default;
    
    explicit Punct(vector<char> c) : accepted{c} { }
    void add_char(char c);
    void add_vector(vector<char> s);
    bool remove_char(char c);
    void clear() { accepted.clear(); }
    vector<char>::iterator begin() { return accepted.begin();}
    vector<char>::iterator end() { return accepted.end(); }
private:
    vector<char> accepted{' ', '\n', EOF}; // Whitespace as default
};


void Punct::add_char(char c){
    accepted.push_back(c);
    // Remove any duplicate characters from the list.
    unique(accepted.begin(), accepted.end());
}

void Punct::add_vector(vector<char> s){
    accepted.insert(accepted.end(), s.begin(), s.end());
    // Remove any duplicate characters from the list.
    unique(accepted.begin(), accepted.end());

}

bool Punct::remove_char(char c){
    auto it = find(accepted.begin(), accepted.end(), c);
    if (it == accepted.end())
	return false;
    else
	accepted.erase(it);
    return true;
}

//------------------------------------------------------------------------------
// Check_word_end: Determines if character defines the end of a word by
// applying any character in Punct as a word definer. By default, whitespace is
// considered a word-ender.
//------------------------------------------------------------------------------
bool check_word_end(Punct &p, char ch){ 

    // Ok, so go through the punctation list
    // If whitespace, yes
    // If \a , then check for is alphabetical
    // If \n , then check for isdigit
    // If \b, then check both
    // Otherwise, if chracter is a specific character, then return true.

    for (auto it = p.begin(); it != p.end(); it++){
	switch(*it){
	case '\a':
	    return !isalpha(ch);
	case '\b':
	    return !isalnum(ch);
	case 'd':
	    return !isdigit(ch);
	default:
	    if (ch == *it)
		return true;

	    // If character is at 
	}

    }

    return false;
}

uint64_t count_words(Text_iterator begin, Text_iterator end, Punct &p){
    if (begin == end) return 0;
    
    uint64_t count = 0;
    bool check;
    char temp;
    while (begin != end){
        temp = *begin;
	check = check_word_end(p, *begin);
	if (check) count++;
	++begin;
	
	// Count the last word if no delimiter was found.
	if (!check && begin == end)
	    count++;
    }
    // If the end is reached, count the last word.
    return count;
}


int main(void){
    Document d;
    ifstream is;
    
    handle_file(is);
    is >> d;
    is.close();

    Punct p;
    uint64_t result = count_words(d.begin(), d.end(), p);
    cout << "Number of words (using whitespace as delimiter) : " << result << "\n";
    // Now considering consecutive alphabetical characters.
    p = Punct({'\a'});
    result = count_words(d.begin(), d.end(), p);
    cout << "Number of words (Using consecutive characters as delimiter) : " << result << "\n";
    

}
