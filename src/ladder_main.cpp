#include <iostream>
#include <set>
#include <vector>
#include "ladder.h"

using namespace std;

int main()
{
    set<string> wordList;

    //loadwords
    load_words(wordList, "src/words.txt");

    //define test case

    //run test 
    string word1 = "car";
    string word2 = "cheat";

    cout << "Finding word ladder from " << word1 << " to " << word2 << endl;

    vector<string> ladder = generate_word_ladder(word1, word2, wordList);

    print_word_ladder(ladder);


    cout << "--------------------------" << endl;
    return 0;
}