
#include "../src/dijkstras.h"

using namespace std;

int main() {
    /**
    cout << "MEOW MEOW\n";
    // Define the graph as an adjacency list
    int numVertices = 6;
    Graph G;
    G.resize(numVertices);

    // Add weighted edges: Graph[src].push_back(Edge(dest, weight))
    G[0].push_back(Edge(1, 4));
    G[0].push_back(Edge(2, 1));
    G[1].push_back(Edge(3, 1));
    G[2].push_back(Edge(1, 2));
    G[2].push_back(Edge(3, 5));
    G[3].push_back(Edge(4, 3));
    G[4].push_back(Edge(5, 2));

    int source = 0;
    vector<int> previous(numVertices, -1);
    vector<int> distances = dijkstra_shortest_path(G, source, previous);

    cout << "Shortest distances from source " << source << ":\n";
    for (size_t i = 0; i < distances.size(); i++) {
        cout << "To " << i << " -> " << (distances[i] == INF ? "INF" : to_string(distances[i])) << endl;
    }

    // Print shortest path to destination
    int destination = 5;
    vector<int> path = extract_shortest_path(distances,previous, destination);
    cout << "\nShortest path from " << source << " to " << destination << ":\n";
    print_path(path, distances[destination]);

    cout << "\nMEWO MEOW\n";*/

    Graph g;
    file_to_graph("src/small.txt", g);

    for(auto edges: g)
    {
        for(auto edge: edges) cout << edge;
    }
    vector<int> prev;
    prev.resize(g.size());

    vector<int> dsp = dijkstra_shortest_path(g, 0, prev);

    cout << endl;

    vector<int> shortest = extract_shortest_path(dsp, prev, 2);

    for(auto i: prev) cout << i << endl;

    print_path(shortest, dsp[2]);

    return 0;
}