#pragma once
#include "Graph.h"

class bfs
{
public:
	bfs();

	void bfs_algo(Node* node,string& start);

private:
	// Trouver un n�ud par sa valeur
	Node* findNode(const string& val) const;
};

