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
    previous.resize(numVert, -1);
    
    // Use a min heap
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
    minHeap.push({source, 0});//starting and zero weight
    dist[source] = 0;

    while(!minHeap.empty())
    {
        int currentEdge = minHeap.top().second; // Extract the vertex with the smallest weight
        minHeap.pop();

        if(visitedVert[currentEdge]) continue;//if we already visited
        visitedVert[currentEdge] = true;//if not visited

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

int extractShortestWeight(priority_queue<pair<int, int>>& minHeap)
{
    vector<pair<int, int>> tempVec;

    // Extract all elements from the heap
    while (!minHeap.empty())
    {
        tempVec.push_back(minHeap.top());
        minHeap.pop();
    }

    // Find the element with the smallest weight
    auto minElement = min_element(tempVec.begin(), tempVec.end(), 
                                  [](const pair<int, int>& a, const pair<int, int>& b) {
                                      return a.second < b.second; // Compare weights
                                  });

    int smallestVertex = minElement->first; // Get vertex with smallest weight

    // Reinsert all elements except the extracted one
    for (const auto& elem : tempVec)
    {
        if (elem.first != smallestVertex)  // Skip the extracted element
            minHeap.push(elem);
    }

    return smallestVertex;
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
        cout << element << " ";
    }
    cout << "\n";
    cout << "Total cost is " << total << endl;
}