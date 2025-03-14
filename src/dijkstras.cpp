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
    priority_queue<pair<int,int>> minHeap; //pair<vertex,weight>

    minHeap.push({source,0});//starting and zero weight
    while(!minHeap.empty())
    {
        int currentEdge = extractVertMinWeight(minHeap);

        if(visitedVert[currentEdge]) continue;
        visitedVert[currentEdge] = true;

        for(Edge edge: G[currentEdge])
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

int extractVertMinWeight(priority_queue<pair<int,int>> minHeap)
{
    priority_queue<pair<int,int>> minHeapCopy = minHeap;

    pair<int,int> lowestVertex = minHeapCopy.top();
    minHeapCopy.pop();

    while(!minHeapCopy.empty())
    {
        pair<int, int> currentVertex = minHeapCopy.top();
        minHeapCopy.pop();
        if(lowestVertex.second > currentVertex.second) lowestVertex = currentVertex;
    }

    return lowestVertex.first;
}


//extracts shortest path from source vertex to a given destination
vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination)
{
    int size = distances.size();
    ++size;
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
        cout << element << " --> ";
    }

    cout << "Total: " << total << endl;
}