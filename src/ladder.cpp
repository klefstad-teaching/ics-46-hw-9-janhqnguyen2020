#include "../src/ladder.h"
#include <algorithm>
#include <cstddef>
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
    int len1 = str1.length(), len2 = str2.length();

    if(abs(len1 - len2) > d)
    {
        error(str1, str2, "Difference is too great");
        return false;
    }

    int diff = 0;
    int index1, index2;
    //cat dog
    for(index1 = 0, index2 = 0;index1 < min(len1, len2);)
    {
        if(str1[index1] != str2[index2])
        {
            ++diff;

            if(index1 + 1 == len1 || index2 + 1 == len2) break;
            ++index1;
            ++index2;
        }
    }

    if(len1 != len2)
    {
        diff += abs(len1 - len2);
    }

    return diff <= d;
}

//checks if two words are adjacent in word ladder graph
bool is_adjacent(const string& word1, const string& word2)
{
    return edit_distance_within(word1, word2, 1);
}


//find shortest word ladder between two words using BFS
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{
    /**
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;

    visited.insert(begin_word);

    while(!ladder_queue.empty()) 
    {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();

        for(const string& word : word_list)
        {
            if(is_adjacent(last_word, word) && visited.find(word) == visited.end())
            {
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                visited.insert(word);

                if(word == end_word) return new_ladder;

                ladder_queue.push(new_ladder);
            }
        }
    }*/

    return {};
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
        while(getline(inFile, line))
        {
            transform(line.begin(), line.end(), line.begin(), ::tolower);
            word_list.insert(line);
        }
    }

    inFile.close();
}

//prints found word ladder
void print_word_ladder(const vector<string>& ladder)
{
    if(ladder.empty())
    {
        cout << "Word Ladder is empty" << endl;
        return;
    }

    for(size_t index = 0; index < ladder.size(); ++index)
    {
        cout << ladder[index];
        if(index != ladder.size() - 1) cout << " -> ";
    }
    cout << endl;
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