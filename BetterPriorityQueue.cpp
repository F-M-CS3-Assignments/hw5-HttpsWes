#include "BetterPriorityQueue.h"

bool BetterPriorityQueue::Contains(const BPQNode& n) const {
    for (const auto& item : this->c) {
        if (item == n) return true;
    }
    return false;
}

bool BetterPriorityQueue::Update(const BPQNode& n) {
    for (auto& item : this->c) {
        if (item == n && n.priority < item.priority) {
            item.priority = n.priority;
            // Re-heapify the queue
            make_heap(this->c.begin(), this->c.end(), this->comp);
            return true;
        }
    }
    return false;
}

string BetterPriorityQueue::ToString() const {
    stringstream ss;
    ss << "[";
    for (size_t i = 0; i < this->c.size(); ++i) {
        ss << BPQNodeToString(this->c[i]);
        if (i < this->c.size() - 1) ss << ", ";
    }
    ss << "]";
    return ss.str();
}

string BetterPriorityQueue::BPQNodeToString(const BPQNode& n) {
    stringstream ss;
    ss << "(" << n.node << ", pri: " << n.priority << ")";
    return ss.str();
}
