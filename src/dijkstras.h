#include <iostream>//used for I/O
#include <fstream>//file handling
#include <vector>
#include <queue>//needed for bfs and dijkstras
#include <limits>//define maximum value for a data type
#include <stack>

using namespace std;

constexpr int INF = numeric_limits<int>::max();//final upperbound of int data type

//weighted edge in a graph
struct Edge {
    int src=0;//source vertex
    int dst=0;//destination vertex
    int weight=0;//weight of edge
    Edge(int s = 0, int d = 0, int w = 0) : src(s), dst(d), weight(w) {}
    
    //reads edge from input
    friend istream& operator>>(istream& in, Edge& e)
    {
        return in >> e.src >> e.dst >> e.weight;
    }

    //prints edge in format (src,dest,weight)
    friend ostream& operator<<(ostream& out, const Edge& e)
    {
        return out << "(" << e.src << "," << e.dst << "," << e.weight << ")";
    }
};

//represent graph using adjacency list
struct Graph : public vector<vector<Edge>> {
    int numVertices=0;
};

class CompareWeights
{
public: 
    int operator()(const pair<int,int>& p1, const pair<int,int>& p2)
    {
        return p1.second > p2.second;
    }
};

//reads a graph from input stream
inline istream& operator>>(istream& in, Graph& G) {
    if (!(in >> G.numVertices))
        throw runtime_error("Unable to find input file");
    G.resize(G.numVertices);
    for (Edge e; in >> e;)
        G[e.src].push_back(e);
    return in;
}

//reads a graph from a file
inline void file_to_graph(const string& filename, Graph& G) {
    ifstream in(filename);
    if (!in) {
        throw runtime_error("Can't open input file");
    }
    in >> G;
    in.close();
}

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous);
vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination);
void print_path(const vector<int>& v, int total);