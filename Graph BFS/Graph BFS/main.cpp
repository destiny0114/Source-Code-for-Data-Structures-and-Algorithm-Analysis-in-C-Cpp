//
//  main.cpp
//  Graph BFS
//
//  Created by Rockabye Saw on 10/03/2021.
//  Copyright © 2021 Rockabye Saw. All rights reserved.
//

#include <iostream>
#include <list>

using namespace std;

class Graph {
  int numVertices;
  list<int>* adjLists;
  bool* visited;

public:
  Graph(int vertices);
  void addEdge(int src, int dest);
  void BFS(int startVertex);
};

Graph::Graph(int vertices) {
    numVertices = vertices;
    adjLists = new list<int>[vertices];
}

void Graph::addEdge(int src, int dest) {
  adjLists[src].push_back(dest);
  adjLists[dest].push_back(src);
}

void Graph::BFS(int startVertex) {
    visited = new bool[numVertices];
    for (int i = 0; i < numVertices; i++)
        visited[i] = false;
    
    list<int> queue;
    
    visited[startVertex] = true;
    queue.push_back(startVertex);

    list<int>::iterator i;
    
    while (!queue.empty()) {
        int currVertex = queue.front();
        // at here also we can say if we reach dest then we can break the loop
        cout << "Visited " << currVertex << " ";
        queue.pop_front();
        
        for (i = adjLists[currVertex].begin(); i != adjLists[currVertex].end(); ++i) {
            int adjVertex = *i;
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                queue.push_back(adjVertex);
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    g.BFS(2);
    return 0;
}
