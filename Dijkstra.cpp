#include "Dijkstra.h"

Dijkstra::Dijkstra()
{
}



void Dijkstra::dijkstra(Graph& graph, const string& start, const string& end) const
{
 
    // recuperer le noeud de debut
    Node* startNode = findNode(start);
    // recuperer le noeud de fin
    Node* endNode = findNode(end);
    // tester si les noeud ont ete trouv�
    if (!startNode || !endNode) {
        cout << "Noeud '" << start << "' ou '" << end << "' introuvable." << endl;
        return;
    }

    std::cout << std::endl;
    std::cout << "================================================================= " << std::endl;
    std::cout << "---------------------DiJKSTRA : Plus court chemin______________________" << std::endl;
    std::cout << "Sommet de depart : " << start << std::endl;
    std::cout << "Sommet de d'arrivee : " << end << std::endl;
    std::cout << "================================================================= " << std::endl;

    // la racine du graphe
    Node* root = graph.getRoot();
    /*
        L'utilisation de unordered_map est tr�s utile car la vitesse d'insertion et
        de recuperation est plus importante que celle de map
    */
    // Distance minimale depuis le d�part:
    unordered_map<string, int> distances;
    // Pr�d�cesseur pour reconstruire le chemin
    unordered_map<string, string> previous;
    unordered_map<string, bool> visited; // N�uds visit�s

    // Initialisation de tous les noeud
    Node* current = root;
    while (current)
    {
        distances[current->value] = INT_MAX;// distance infinie
        visited[current->value] = false; // sommet non encore visit�

        current = current->next;
    }


    // initialisation du noeud de debut
    distances[start] = 0;
    int iteration = 0;

    // Boucle principale
    while (true)
    {
        // Chercher le n�ud minimal non visit�
        Node* minNode = getMinDistanceNode(distances, visited);
        if (!minNode) break; // noeud non trouv�
        visited[minNode->value] = true; // marquer ce noeud minimal comme visit�

        // affichage des iterations
        std::cout << "\n---------------- Iteration " << iteration++ << " ----------------" << std::endl;
        std::cout << "N�ud courant : " << minNode->value << std::endl;

        // Parcourir les successeurs du n�ud courant
        Edge* edge = minNode->successors;
        while (edge)
        {
            string neighbor = edge->destination->value;
            if (!visited[neighbor])
            {
                // calculer la nouvelle distance
                int newDist = distances[minNode->value] + edge->weight;
                if (newDist < distances[neighbor])
                {
                    // mettre � jour la distance du noeud suivant si la nouvelle distance est inferieure a la distance actuelle
                    distances[neighbor] = newDist;
                    // mettre a jour le noeud precedent
                    previous[neighbor] = minNode->value;

                }
            }
            // passer au voisin suivant
            edge = edge->next;
        }



        // Afficher l'�tat actuel des distances
        std::cout << "Distances :\n";
        for (const auto& pair : distances)
        {
            std::cout << pair.first << " : ";
            if (pair.second == INT_MAX)
                std::cout << "INF";
            else
                std::cout << pair.second;
            std::cout << (visited[pair.first] ? " (visit�)" : " (non visit�)") << std::endl;
        }
    }


    if (distances[end] == INT_MAX)
    {
        cout << "Aucun chemin trouv� de " << start << " � " << end << endl;
        return;
    }

    // Reconstruire le chemin
    cout << "\nDistance minimale : " << distances[end] << endl;
    cout << "Chemin : ";
    string path = end;
    while (previous[path] != "")
    {
        cout << path << " <- ";
        path = previous[path];
    }
    cout << start << endl;

}



// Trouver un n�ud par sa valeur
Node* Graph::findNode(const string& val) const {
    Node* current = head;
    while (current) {
        if (current->value == val) return current;
        current = current->next;
    }
    return nullptr;
}


// Obtenir le n�ud avec la distance minimale non encore visit�
Node* Graph::getMinDistanceNode(const unordered_map<string, int>& distances, const unordered_map<string, bool>& visited) const {
    int minDist = INT_MAX;
    Node* minNode = nullptr;

    // on doit parcourir les noeud non visit�s pour trouver le minimum
    Node* current = head;
    while (current) {
        if (!visited.at(current->value) && distances.at(current->value) < minDist) {
            minDist = distances.at(current->value);
            minNode = current;
        }
        current = current->next;
    }
    return minNode;
}