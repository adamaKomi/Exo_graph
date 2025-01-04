#include "Graph.h"
#include <stack>
#include <queue>
#include <vector>
#include <exception>


Graph::Graph(bool isDirected)
    : isDerected(isDirected),
      list(unordered_map<string, vector<pair<string, int>>>())
{}

void Graph::addEdge(const string& start, const string& end, int weight)
{
    // ne pas permettre les poids negatifs
    if (weight < 0) throw invalid_argument("Le poids doit être positif !!!");

    this->list[start].push_back({ end,weight });
    // Vérifier si le noeud 'end' existe, sinon l'ajouter avec une valeur vide
    if (list.find(end) == list.end()) {
        list[end] = vector<pair<string, int>>(); // Crée un vecteur vide
    }
    // definir si le gragh est orienté ou non
    if (!this->isDerected) this->list[end].push_back({ start, weight });
}

// pour recuperer le graphe 
unordered_map<string, vector<pair<string, int>>> Graph::getList() const
{
    return this->list;
}


// afficher le graphe sous forme de liste d'adjacence
void Graph::printGraph() const
{
    if (this->list.empty())
    {
        std::cout << "Le graphe est vide !!!" << std::endl;
    }

    for (auto vertex : this->list)
    {
        std::cout << vertex.first<<" ";
        for (auto successor : vertex.second)
        {
            std::cout << "->(" << successor.first << "," << successor.second << ")";
        }
        std::cout << std::endl;
    }
}