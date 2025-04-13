#ifndef BETTER_PRIORITY_QUEUE_H
#define BETTER_PRIORITY_QUEUE_H

#include <queue>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Define your BPQNode struct here (or include it from a .txt/.h file if provided)
struct BPQNode {
    int node;
    int priority;

    // This makes priority_queue work with greater<>
    bool operator>(const BPQNode& other) const {
        return this->priority > other.priority;
    }

    // Optional: operator== if needed for comparison in Contains/Update
    bool operator==(const BPQNode& other) const {
        return this->node == other.node;
    }
};

// Custom priority queue class
class BetterPriorityQueue : public priority_queue<
    BPQNode,
    vector<BPQNode>,
    greater<BPQNode>
> {
public:
    bool Contains(const BPQNode& n) const;
    bool Update(const BPQNode& n);
    string ToString() const;
    static string BPQNodeToString(const BPQNode& n);
};

#endif
