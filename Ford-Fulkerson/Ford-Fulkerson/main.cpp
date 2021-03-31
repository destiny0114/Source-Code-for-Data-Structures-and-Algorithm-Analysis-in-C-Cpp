//
//  main.cpp
//  Ford-Fulkerson
//
//  Created by Rockabye Saw on 15/03/2021.
//  Copyright © 2021 Rockabye Saw. All rights reserved.
//

#include <limits.h>
#include <string.h>

#include <iostream>
#include <queue>
using namespace std;

#define V 6

bool bfs(int graph[V][V], int s, int t, int parent[]) {
    bool visited[V];
    
    for (int i = 0; i < V; i++)
        visited[i] = false;
    
    queue<int> q;
    q.push(s);
    
    visited[s] = true;
    parent[s] = -1;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v = 0; v < V; v++) {
          if (visited[v] == false && graph[u][v] > 0) {
            q.push(v);
            parent[v] = u;
            visited[v] = true;
          }
        }
    }
    
    return visited[t] == true;
}

int fordFulkerson(int graph[V][V], int s, int t) {
    int u, v;
    
    int rGraph[V][V];
    for (u = 0; u < V; u++)
      for (v = 0; v < V; v++)
        rGraph[u][v] = graph[u][v];

    int parent[V];
    int max_flow = 0;
    
    while (bfs(rGraph, s, t, parent)) {
        int path_flow = INT_MAX;
        
        for (v = t; v != s; v = parent[v]) {
          u = parent[v];
          path_flow = min(path_flow, rGraph[u][v]);
        }
        
        for (v = t; v != s; v = parent[v]) {
          u = parent[v];
          rGraph[u][v] -= path_flow;
          rGraph[v][u] += path_flow;
        }
        max_flow += path_flow;
    }
    
    return max_flow;
}

int main(int argc, const char * argv[]) {
    int graph[V][V] = {{0, 8, 0, 0, 3, 0},
               {0, 0, 9, 0, 0, 0},
               {0, 0, 0, 0, 7, 2},
               {0, 0, 0, 0, 0, 5},
               {0, 0, 7, 4, 0, 0},
               {0, 0, 0, 0, 0, 0}};

    cout << "Max Flow: " << fordFulkerson(graph, 0, 5) << endl;
    return 0;
}
