#include "../src/ladder.h"

//print error message
void error(string word1, string word2, string msg)
{
    if(word1 == word2) cout << "[Error]: Word 1 (" << word1 << ") and Word 2 (" << word2 << ") are the same." << endl;
}

//checks if two words have an edit distance within d
bool edit_distance_within(const std::string& str1, const std::string& str2, int d)
{

}

//checks if two words are adjacent in word ladder graph
bool is_adjacent(const string& word1, const string& word2)
{

}


//find shortest word ladder between two words using BFS
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{

}

//loads words from a dictionary file into a set<string>
void load_words(set<string> & word_list, const string& file_name)
{

}

//prints found word ladder
void print_word_ladder(const vector<string>& ladder)
{

}


//tests correctness of generate_word_ladder using assertions
void verify_word_ladder()
{

}