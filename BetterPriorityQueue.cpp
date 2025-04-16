#include "BetterPriorityQueue.h"
#include <algorithm>
#include <sstream>

using namespace std;

// Checks if the given node is already in the queue
bool BetterPriorityQueue::Contains(const BPQNode& n) const {
    for (const auto& item : this->c) {
        if (item == n) return true;
    }
    return false;
}

// Updates the node's priority only if the new one is smaller (better)
bool BetterPriorityQueue::Update(const BPQNode& n) {
    bool didUpdate = false;

    for (auto& item : this->c) {
        if (item == n) {
            if (n.pri < item.pri) {
                item.pri = n.pri;
                didUpdate = true;
            }
            break;
        }
    }

    // If we changed anything, rebuild the heap
    if (didUpdate) {
        make_heap(this->c.begin(), this->c.end(), this->comp);
    }

    return didUpdate;
}

// Returns a sorted string version of the queue (for testing/debug)
string BetterPriorityQueue::ToString() const {
    stringstream ss;
    ss << "[";

    // Copy the contents so we don’t change the original queue
    vector<BPQNode> copy = this->c;

    // Sort by priority, then by node ID if tied
    sort(copy.begin(), copy.end(), [](const BPQNode& a, const BPQNode& b) {
        return (a.pri != b.pri) ? a.pri < b.pri : a.gnode < b.gnode;
    });

    for (size_t i = 0; i < copy.size(); ++i) {
        ss << BPQNodeToString(copy[i]);
        if (i < copy.size() - 1) ss << ", ";
    }

    ss << "]";
    return ss.str();
}

// Converts one node to a readable format like (4, pri: 7)
string BetterPriorityQueue::BPQNodeToString(const BPQNode& n) {
    stringstream ss;
    ss << "(" << n.gnode << ", pri: " << n.pri << ")";
    return ss.str();
}
