#include "Graph.h"
#include <iostream>
#include <vector>

using namespace std;

// This is a helper function 
const GraphEdge* findExistingEdge(nodekey_t gnFrom, nodekey_t gnTo, vector<vector<GraphEdge *>> adjList)
{
	if(adjList.size() == 0)
	{
		return nullptr;
	}

	for(size_t rowIDX = 0; rowIDX < adjList.size(); rowIDX++)
	{
		vector<GraphEdge*> row = adjList.at(rowIDX);
		for(size_t i = 0; i < row.size(); i++)
		{
			GraphEdge *cur = row.at(i);
			if(cur->from == gnFrom && cur->to == gnTo)
			{
				return cur;
			}
		}
	} 

	return nullptr;
}

// Turns a GraphEdge into a string so we can print it easily
string GraphEdgeToString(const GraphEdge* e)
{
	return "((" + to_string(e->from) + ")->(" + to_string(e->to) + ") w:" + to_string(e->weight) + ")";
}

// Adds a node to the graph
void Graph::AddNode(nodekey_t key)
{
	if(this->IsPresent(key))
	{
		throw invalid_argument("Duplicate node cannot be added: " + to_string(key));
	}

	nodes.push_back(key); 
	// create an empty list of edges for this node
	vector<GraphEdge*> *newRow = new vector<GraphEdge*>;
	adjList.push_back(*newRow);
	delete newRow;
}

// Adds an edge from one node to another with a given weight
const GraphEdge *Graph::AddEdge(nodekey_t gnFrom, nodekey_t gnTo, unsigned int w)
{
	// Check if the edge already exists
	const GraphEdge* dup = findExistingEdge(gnFrom, gnTo, this->adjList);
	if(dup != nullptr)
	{
		throw invalid_argument("Duplicate edge cannot be added: " + GraphEdgeToString(dup));
	}

	if(!this->IsPresent(gnFrom) || !this->IsPresent(gnTo))
	{
		throw invalid_argument("One or both nodes don't exist.");
	}

	// Create a new edge
	GraphEdge *ge = new GraphEdge;
	ge->from = gnFrom;
	ge->to = gnTo;
	ge->weight = w;

	// Find the index of the 'from' node in the nodes list
	size_t fromIndex = 0;
	while (nodes.at(fromIndex) != gnFrom) {
		fromIndex++;
	}

	// Add this edge to the correct row in the adjacency list
	adjList.at(fromIndex).push_back(ge);

	return ge;
}

// Checks if a node is in the graph
bool Graph::IsPresent(nodekey_t key) const {
	for (auto n : nodes) {
		if (n == key) return true;
	}
	return false;
}

// Returns all edges going out from a specific node
set<const GraphEdge*> Graph::GetOutwardEdgesFrom(nodekey_t node) const 
{
	size_t idx = 0;
	while(idx < this->nodes.size() && (this->nodes.at(idx) != node))
	{
		idx++;
	}
	if(idx == this->nodes.size()){
		throw invalid_argument("No such node: " + to_string(node));
	}

	set<const GraphEdge*> result;
	vector<GraphEdge*> row = this->adjList.at(idx);
	for (size_t i = 0; i < row.size(); i++) {
		GraphEdge* edge = row.at(i);
		if (edge->from == node) {
			result.insert(edge);
		}
	}

	return result;
}

// Returns a set of all node keys in the graph
set<nodekey_t> Graph::GetNodes() const {
	set<nodekey_t> nodeSet;
	for (auto n : nodes) {
		nodeSet.insert(n);
	}
	return nodeSet;
}

// Returns how many nodes the graph has
size_t Graph::Order() const 
{
	return nodes.size();
}

// Returns how many total edges the graph has
size_t Graph::Size() const 
{
	size_t total = 0;
	for(size_t i = 0; i < adjList.size(); i++){
		vector<GraphEdge*> row = adjList.at(i);
		for(size_t j = 0; j < row.size(); j++){
			total++;
		}
	}
	return total;
}

// Turns the list of nodes into a string for printing
string Graph::NodesToString() const 
{
	if(nodes.size() == 0)
	{
		return "[]";
	}

	string str = "[";
	for(size_t i = 0; i < (nodes.size() - 1); i++)
	{
		str = str + "(" + to_string(nodes.at(i)) + "), ";
	}

	str = str + "(" + to_string(nodes.at(nodes.size()-1)) + ")]";
	return str;
}

// Turns all the edges in the graph into a string for printing
string Graph::EdgesToString() const 
{
	if(this->adjList.size() == 0)
	{
		return "[]";
	}

	size_t count = 0;
	string str = "[";
	for(size_t rowIDX = 0; rowIDX < this->adjList.size(); rowIDX++)
	{
		vector<GraphEdge*> row = this->adjList.at(rowIDX);
		for(size_t i = 0; i < row.size(); i++)
		{
			GraphEdge *cur = row.at(i);
			str = str + GraphEdgeToString(cur);

			if(count < (this->Size() - 1)){
				 str = str + ", ";
			}
			count++;
		}
	} 

	str = str +  "]";
	return str;
}

// Destructor to clean up memory
Graph::~Graph() {
	for (auto& row : adjList) {
		for (auto edgePtr : row) {
			delete edgePtr;
		}
	}
}
