#include "Graph.h"

Graph::Graph(int vertices)
{
    V = vertices;
    adj = new vector<pair<int,int>>[V];
}

void Graph::addEdge(int u,int v,int weight)
{
    adj[u].push_back({v,weight});
    adj[v].push_back({u,weight});
}
