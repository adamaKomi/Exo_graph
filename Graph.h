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
    bool isDerected;// si le graphe est orient� ou non
public:
    // constructeur
	Graph(bool isDirected = false); 
    // ajouter une ar�te
    void addEdge(const string& start, const string& end, int weight = 0);
    // pour recuperer la liste d'adjacence
    unordered_map<string, vector<pair<string, int>>> getList() const;
    // pour afficher le graphe
    void printGraph() const;
};


/*

// Structure d'une ar�te
struct Edge {
    // Pointeur vers le n�ud de destination
    struct Node* destination; 
    int weight;// Poids de l'ar�te               
    // Pointeur vers l'ar�te suivante
    Edge* next;               
};

// Structure d'un n�ud
struct Node {
    string value; // nom du n�ud
    // Liste cha�n�e des ar�tes (successeurs)
    Edge* successors; 
    // Pointeur vers le prochain n�ud dans la liste globale
    Node* next; 
};

// Classe Graphe Orient�
class Graph {
private:
    Node* head; // Racine du graphe (premier n�ud)
public:
    Graph();

    Node* getRoot()const;
    // Ajouter un n�ud au graphe
    void addNode(const string& val);

    // Ajouter une ar�te orient�e
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
    // Trouver un n�ud par sa valeur
    Node* findNode(const string& val) const;

    // Obtenir le n�ud avec la distance minimale non encore visit�
    Node* getMinDistanceNode(const unordered_map<string, int>& distances, const unordered_map<string, bool>& visited) const;
};


*/