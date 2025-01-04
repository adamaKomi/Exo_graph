#pragma once
#include <iostream>
#include <climits>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <list>
using namespace std;



class Graph
{
private:
    // liste d'adjacence
    unordered_map<string, vector<pair<string, int>>> list;
    bool isDerected;// si le graphe est orienté ou non
public:
    // constructeur
	Graph(bool isDirected = false); 
    // ajouter une arête
    void addEdge(const string& start, const string& end, int weight = 0);
    // pour recuperer la liste d'adjacence
    unordered_map<string, vector<pair<string, int>>> getList() const;
    // pour afficher le graphe
    void printGraph() const;
};


/*

// Structure d'une arête
struct Edge {
    // Pointeur vers le nœud de destination
    struct Node* destination; 
    int weight;// Poids de l'arête               
    // Pointeur vers l'arête suivante
    Edge* next;               
};

// Structure d'un nœud
struct Node {
    string value; // nom du nœud
    // Liste chaînée des arêtes (successeurs)
    Edge* successors; 
    // Pointeur vers le prochain nœud dans la liste globale
    Node* next; 
};

// Classe Graphe Orienté
class Graph {
private:
    Node* head; // Racine du graphe (premier nœud)
public:
    Graph();

    Node* getRoot()const;
    // Ajouter un nœud au graphe
    void addNode(const string& val);

    // Ajouter une arête orientée
    void addEdge(const string& from, const string& to, int weight =0);

    // Afficher le graphe
    void printGraph() const;

    // Trouver le chemin le plus court avec Dijkstra
    void dijkstra(const string& start, const string& end);

    // le DFS
    void dfs(string start = "");
    //void dfs(Node* noeud);

    // Le BFS
    void bfs(string start = "");

private:
    // Trouver un nœud par sa valeur
    Node* findNode(const string& val) const;

    // Obtenir le nœud avec la distance minimale non encore visité
    Node* getMinDistanceNode(const unordered_map<string, int>& distances, const unordered_map<string, bool>& visited) const;
};


*/