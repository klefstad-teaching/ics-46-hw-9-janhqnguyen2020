#include "../src/ladder.h"
#include <algorithm>
#include <cctype>
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

    int difference = 0;
    int index1 = 0, index2 = 0;
    //cat dog
    while(index1 < len1 && index2 < len2)
    {

        if(str1[index1] != str2[index2])
        {
            ++difference;

            if(difference > d) return false;//end early if difference is too great

            if(len1 > len2) ++index1;//starting word is too long, delete needed
            else if(len2 > len1) ++index2;//starting word too short, insert needed
            else
            {
                ++index1;
                ++index2;
            }
        }
        else
        {
            ++index1;
            ++index2;
        }
    }

    difference += (len1 - index1) + (len2 - index2);

    return difference <= d;
}


//checks if two words are adjacent in word ladder graph
bool is_adjacent(const string& word1, const string& word2)
{
    return edit_distance_within(word1, word2, 1);
}


//find shortest word ladder between two words using BFS
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    
    set<string> visited;
    visited.insert(begin_word);
    
    while(!ladder_queue.empty()) 
    {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();

        for(const string& word : word_list)
        {
            vector<string> ladder = ladder_queue.front();
            ladder_queue.pop();
            string lastWord = ladder.back();

            for(const string& word: word_list)
            {
                if(is_adjacent(lastWord, word))
                {
                    if(visited.find(word) == visited.end())
                    {
                        visited.insert(word);

                        vector<string> new_Ladder = ladder;
                        new_Ladder.push_back(word);

                        if(word == end_word) return new_Ladder;

                        ladder_queue.push(new_Ladder);
                    }
                }
            }
        }

    }
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

    while(getline(inFile, line))
    {            
        for(char &c : line) 
        {
            c = std::tolower(c);
        }

        word_list.insert(line);
    }

    inFile.close();
}

//prints found word ladder
void print_word_ladder(const vector<string>& ladder)
{
    if(ladder.empty())
    {
        cout << "No word ladder found." << endl;
        return;
    }
    cout << "Word Ladder found: ";
    for(size_t index = 0; index < ladder.size(); ++index)
    {
        cout << ladder[index] << " ";
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