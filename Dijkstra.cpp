
// This function finds the shortest path from start to finish using Dijkstra's algorithm
// The time it takes depends on how many edges and nodes there are (roughly O(E * VlogV))

#include "Graph.h"
#include "BetterPriorityQueue.h"
#include "Dijkstra.h"
#include <climits>
#include <set>
#include <unordered_map>
#include <stdexcept>
#include <vector>
using namespace std;



int dijkstra(nodekey_t start, nodekey_t end, const Graph* g) {
    // Make sure both start and end nodes exist in the graph
    if (!(g->IsPresent(start) && g->IsPresent(end))) {
        throw invalid_argument("The start and end nodes must exist in the graph.");
    }

    BetterPriorityQueue pq; // This helps us always get the closest node next
    set<nodekey_t> nodes = g->GetNodes(); 
    unordered_map<nodekey_t, int> distances;

    // Set up the distances
    for (nodekey_t node : nodes) {
        BPQNode entry;
        entry.gnode = node;
        if (node == start) {
            entry.pri = 0; 
            distances[node] = 0;
        } else {
            entry.pri = INT_MAX;
            distances[node] = INT_MAX;
        }
        pq.push(entry); 
    }

    // Start visiting nodes in order of closeness
    while (!pq.empty()) {
        BPQNode curr = pq.top(); 
        pq.pop();

        // Look at all the edges going out from this node
        set<const GraphEdge*> edges = g->GetOutwardEdgesFrom(curr.gnode);

        for (const GraphEdge* edge : edges) {
            nodekey_t neighbor = edge->to;
            int newDist = curr.pri + edge->weight; // Calculate new possible shorter path

            // If the new distance is better, update it
            if (newDist < distances[neighbor]) {
                distances[neighbor] = newDist;

                BPQNode updated;
                updated.gnode = neighbor;
                updated.pri = newDist;

             
                if (pq.Contains(updated)) {
                    pq.Update(updated);
                } else {
                    pq.push(updated); 
                }
            }
        }
    }

    // If we never found a path to the end node, return -1
    return (distances[end] == INT_MAX) ? -1 : distances[end];
}


