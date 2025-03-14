#include "../src/dijkstras.h"
#include <algorithm>
#include <queue>
#include <utility>

//finds shortest path from source vertex to all other vertices using dijkstra's algorithm
vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous)
{
    int numVert = G.size();
    vector<int> dist(numVert, INF);
    vector<bool> visitedVert(numVert, false);

    dist[source] = 0;
    previous[source] = -1;

    priority_queue<pair<int,int>> minHeap; //pair<weight,vertex>

    minHeap.push({source, 0});//starting and zero weight
    while(!minHeap.empty())
    {
        int currentEdge = extract_shortest_path(dist, prev, );

        if(visitedVert[currentEdge]) continue;
        visitedVert[currentEdge] = true;

        for(const Edge& edge: G[currentEdge])
        {
            int vert = edge.dst;
            int weight = edge.weight;

            if(!visitedVert[vert] && dist[currentEdge] + weight < dist[vert])
            {
                dist[vert]  = dist[currentEdge] + weight;
                previous[vert] = currentEdge;
                minHeap.push({vert, dist[vert]});
            }
        }
    }

    return dist;//complexiy is O((E+V)logV)
}

//extracts shortest path from source vertex to a given destination
vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination)
{
    vector<int> path;

    for(int atVert = destination; atVert != -1; atVert = previous[atVert])
    {
        path.push_back(atVert);
    }

    reverse(path.begin(), path.end());

    return path;
}

////print shortest path
void print_path(const vector<int>& v, int total)
{
    for(auto element: v)
    {
        cout << element << " ";
    }
    cout << "\n";
    cout << "Total cost is " << total << endl;
}