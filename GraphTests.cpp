

#include "Graph.h"
#include <iostream>
#include <cassert>

using namespace std;



void TestAddNode(){
	cout << "Testing AddNode..." << endl;
	Graph g = Graph();


	g.AddNode(15);

	assert(g.NodesToString() == "[(15)]");


	g.AddNode(12);

	assert(g.NodesToString() == "[(15), (12)]");
	try {
		g.AddNode(12);
		assert(false);
	} catch( const invalid_argument& e ) { }
	cout << "PASSED!" << endl << endl;
}


void TestAddEdge(){
	cout << "Testing AddEdge..." << endl;
	Graph g = Graph();

	g.AddNode(15);
	g.AddNode(12);
	g.AddNode(9);

	assert(g.NodesToString() == "[(15), (12), (9)]");


	const GraphEdge *ge1 = g.AddEdge(15, 9, 2);
	assert(g.NodesToString() == "[(15), (12), (9)]");

	assert(g.EdgesToString() == "[((15)->(9) w:2)]");
	assert(ge1->from == 15);
	assert(ge1->to == 9);
	assert(ge1->weight == 2);
	const GraphEdge *ge2 = g.AddEdge(9, 12);
	assert(g.NodesToString() == "[(15), (12), (9)]");

	assert(g.EdgesToString() == "[((15)->(9) w:2), ((9)->(12) w:0)]");
	assert(ge2->from == 9);
	assert(ge2->to == 12);
	assert(ge2->weight == 0);
	try {
		const GraphEdge *ge3 = g.AddEdge(20, 12);
		cout << "ge3: (" + to_string(ge3->from) + "->" + to_string(ge3->to) + "  w: " + to_string(ge3->weight) + ")" << endl;
		assert(false);
	} catch (const invalid_argument& e) {}
	try {
		const GraphEdge *ge3 = g.AddEdge(15, 9, 7);

		cout << "ge3: (" + to_string(ge3->from) + "->" + to_string(ge3->to) + "  w: " + to_string(ge3->weight) + ")" << endl;
		assert(false);
	} catch (const invalid_argument& e) {}
	// Additional test
	const GraphEdge *ge4 = g.AddEdge(12, 15, 5);
	assert(ge4->from == 12);
	assert(ge4->to == 15);
	assert(ge4->weight == 5);
	cout << "PASSED!" << endl << endl;
}


void TestIsPresentSizeAndOrder() {
	cout << "Testing IsPresent, Size, and Order..." << endl;


	Graph g2 = Graph();
	assert(g2.Size() == 0);
	assert(g2.Order() == 0);
	assert(g2.IsPresent(17) == false);
	// Additional test
	g2.AddNode(30);
	g2.AddNode(40);
	g2.AddEdge(30, 40, 10);
	assert(g2.Order() == 2);
	assert(g2.Size() == 1);
	assert(g2.IsPresent(30) == true);
	cout << "PASSED!" << endl << endl;
}



void TestGetOutwardEdgesFrom(){
	cout << "Testing GetOutwardEdgesFrom..." << endl;
	Graph g = Graph();
	g.AddNode(17);
	g.AddNode(18);
	g.AddNode(22);
	g.AddNode(34);

	const GraphEdge* ge1 = g.AddEdge(17, 18, 3);
	g.AddEdge(22, 18);
	const GraphEdge* ge3 = g.AddEdge(17, 34, 8);
	g.AddEdge(22, 17, 6);
	set<const GraphEdge*> soln;
	soln.insert(ge3);
	soln.insert(ge1);

	set<const GraphEdge*> result = g.GetOutwardEdgesFrom(17);
	assert(result.size() == soln.size());
	assert(result == soln);
	// Additional test
	const GraphEdge* ge4 = g.AddEdge(17, 22, 5);
	soln.insert(ge4);
	result = g.GetOutwardEdgesFrom(17);
	assert(result == soln);
	cout << "PASSED!" << endl << endl;
}


void TestGetNodes(){
	cout << "Testing GetNodes..." << endl;

	Graph g = Graph();
	g.AddNode(51);
	g.AddNode(24);
	g.AddNode(73);


	set<nodekey_t> nodes = g.GetNodes();
	set<nodekey_t> soln = {24, 73, 51};
	assert(nodes.size() == soln.size());
	assert(nodes == soln);

	
	g = Graph();
	nodes = g.GetNodes();
	soln.clear();
	assert(nodes.size() == soln.size());
	assert(nodes == soln);
	// Additional test
	g.AddNode(99);
	nodes = g.GetNodes();
	assert(nodes.size() == 1);
	assert(nodes.count(99) == 1);
	cout << "PASSED!" << endl << endl;
}




void TestDestructor(){
	cout << "Testing Destructor..." << endl;
	Graph *g = new Graph();

	g->AddNode(3);
	g->AddNode(5);
	g->AddEdge(3, 5, 15);
	delete g;


	Graph *g2 = new Graph();
	g2->AddNode(12);
	g2->AddNode(11);
	delete g2;


	Graph *g3 = new Graph();
	delete g3;
	Graph g4 = Graph();
	// Additional test
	g4.AddNode(100);
	g4.AddNode(200);
	g4.AddEdge(100, 200, 20);
	cout << "NO ERRORS.  Use valgrind to check!" << endl << endl;
}



int main(){

	TestAddNode();
	TestAddEdge();
	TestIsPresentSizeAndOrder();
	TestGetOutwardEdgesFrom();
	TestGetNodes();
	TestDestructor();


	cout << "ALL TESTS PASSED!" << endl;
	return 0;
}
