#include <iostream>
using namespace std;

#include "Graph.h"
#include "Node.h"
int main()

{
	Graph<int> g;
	g.addNode(Node<int>(1));
	g.addEdge(Node<int>(1), Node<int>(3));
	g.deleteEdge(Node<int>(1), Node<int>(3));
	return 0;
}