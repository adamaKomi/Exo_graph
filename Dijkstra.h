#pragma once

#include "Graph.h"


class Dijkstra
{
public:
	Dijkstra();
	void dijkstra(Graph& graph, const string& start, const string& end) const;
private:
    // Trouver un nœud par sa valeur
    Node* findNode(const string& val) const;

    // Obtenir le nœud avec la distance minimale non encore visité
    Node* getMinDistanceNode(const unordered_map<string, int>& distances, const unordered_map<string, bool>& visited) const;
};

