#include "../src/ladder.h"
#include <fstream>

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

//print error message
void error(string word1, string word2, string msg)
{
    cout << "[ERROR for " << word1 << " and " << word2 << "]: " << msg << endl;
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
    ifstream inFile(file_name);
    string line;

    if(!inFile)
    {
        cout << "[ERROR]: " << file_name << " cannot be opened" << endl;
        return;
    }

    if(inFile.is_open())
    {
        while(getline(inFile, line)) word_list.insert(line);
    }

    inFile.close();
}

//prints found word ladder
void print_word_ladder(const vector<string>& ladder)
{

}

//tests correctness of generate_word_ladder using assertions
void verify_word_ladder()
{
    set<string> wordList;

    load_words(wordList, "words.txt");
    my_assert(generate_word_ladder("cat", "dog", wordList).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", wordList).size() == 6);

    my_assert(generate_word_ladder("code", "data", wordList).size() == 6);

    my_assert(generate_word_ladder("work", "play", wordList).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", wordList).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", wordList).size() == 4);

}