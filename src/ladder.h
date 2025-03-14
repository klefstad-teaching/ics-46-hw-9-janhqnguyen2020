#include <iostream>//functionality for I/O
#include <fstream>//file input and output operations
#include <queue>//queue and priority queue for bfs and dijkstras
#include <set>//collection of unique sorted elements
#include <map>//maps keys to values, needed for prev nodes in dijkstras
#include <vector>
#include <string>
#include <cmath>

using namespace std;

void error(string word1, string word2, string msg);
bool edit_distance_within(const std::string& str1, const std::string& str2, int d);
bool is_adjacent(const string& word1, const string& word2);
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list);
void load_words(set<string> & word_list, const string& file_name);
void print_word_ladder(const vector<string>& ladder);
void verify_word_ladder();
