//
//  main.cpp
//  DisjointSet 2
//
//  Created by Rockabye Saw on 04/03/2021.
//  Copyright © 2021 Rockabye Saw. All rights reserved.
//

#include <iostream>

struct Edge {
    int src, dest;
};

struct Graph {
    int V, E;
    
    struct Edge* edge;
};

struct subset {
    int parent;
    int rank;
};

struct Graph* createGraph(int V, int E)
{
    struct Graph* graph
    = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    
    graph->edge = (struct Edge*)malloc(
                                       graph->E * sizeof(struct Edge));
    
    return graph;
}

int find(struct subset subsets[], int i)
{
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    
    return subsets[i].parent;
}

void Union(struct subset subsets[], int xroot, int yroot)
{
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int isCycle(struct Graph* graph)
{
    int V = graph->V;
    int E = graph->E;
    
    struct subset* subsets = (struct subset*)malloc(V * sizeof(struct subset));
    
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
    
    for (int e = 0; e < E; ++e) {
        int x = find(subsets, graph->edge[e].src);
        int y = find(subsets, graph->edge[e].dest);
        
        if (x == y)
            return 1;
        
        Union(subsets, x, y);
    }
    return 0;
}

int main(int argc, const char * argv[]) {
    int V = 3, E = 3;
    struct Graph* graph = createGraph(V, E);
    
    graph->edge[0].src = 0;
    graph->edge[0].dest = 1;
    
    // add edge 1-2
    graph->edge[1].src = 1;
    graph->edge[1].dest = 2;
    
    // add edge 0-2
    graph->edge[2].src = 0;
    graph->edge[2].dest = 2;
    
    if (isCycle(graph))
        printf("Graph contains cycle");
    else
        printf("Graph doesn't contain cycle");
    return 0;
}
