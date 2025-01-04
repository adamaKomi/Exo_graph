#pragma once

#include "Graph.h"


class Dijkstra
{
public:
	Dijkstra();
	void dijkstra(Graph& graph, const string& start, const string& end) const;
private:
    // Trouver un n�ud par sa valeur
    Node* findNode(const string& val) const;

    // Obtenir le n�ud avec la distance minimale non encore visit�
    Node* getMinDistanceNode(const unordered_map<string, int>& distances, const unordered_map<string, bool>& visited) const;
};

