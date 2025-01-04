#pragma once
#include <unordered_map>
#include "Graph.h"

class Algorithms
{
public:

	// algorithme de dijskstra
	void dijkstra(Graph& graph, const string& start) const;
	// parcours en largeur
	void bfs(const Graph& graph, const string& start) const;
	// parcours en profondeur
	void dfs(const Graph& graph, const string& start) const;

	// fonction pour trouver le noeud de plus courte distance dans l'algorithme de dijkstra
	string getMinDistanceNode(const unordered_map<string, vector<pair<string, int>>>& list, 
							  const unordered_map<string, int>& distances, 
							  const unordered_map<string, bool>& visited
							) const;
};

