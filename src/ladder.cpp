#include "../src/ladder.h"
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
    int len1 = str1.size(), len2 = str2.size();

    if(abs(len1 - len2) > d)
    {
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

            if(difference > d) return false;

            if(len1 > len2) ++index1;//deltion needed
            else if(len1 < len2) ++index2;//insertion needed
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

    difference += abs((len1 - index1) - (len2 - index2));
    
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

    /*Givens: string word1, string word2, set
    - All passed by constant reference(direct access to memory but we cannot alter address)*/
    /** if(begin_word == end_word)
    {
        error(begin_word, end_word, "The words are the same.");
        return {};
    }*/
    
    if(word_list.find(begin_word) == word_list.end() || word_list.find(end_word) == word_list.end())
    {
        error(begin_word, end_word, "The words are not in the dictionary.");
        return {};
    }
    
    //declarations of what we need
    queue<vector<string>> ladderQueue;
    ladderQueue.push({begin_word});//since this is a queue of vector of strings, add the string as a vector
    
    set<string> visitedWords;
    visitedWords.insert(begin_word);

    while(!ladderQueue.empty())
    {
        vector<string> ladder = ladderQueue.front();
        ladderQueue.pop();//update the loop, ensure we get out eventually

        string wordComparison = ladder.back();//current comparsion since lastword is vector os strings

        //loop thru given set of words
        for(const string& word : word_list)
        {
            if(is_adjacent(wordComparison, word) && visitedWords.find(word) == visitedWords.end())
            {
                visitedWords.insert(word);
                vector<string> newLadder = ladder;

                newLadder.push_back(word);
                if(word == end_word) return newLadder;

                ladderQueue.push(newLadder);
            }
        }
    }

    return {};//if no ladder is found, but this will never run
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
        line[0] = std::tolower(line[0]);

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
    cout << "Word ladder found: ";
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