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
    // tester si les noeud ont ete trouvé
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
        L'utilisation de unordered_map est très utile car la vitesse d'insertion et
        de recuperation est plus importante que celle de map
    */
    // Distance minimale depuis le départ:
    unordered_map<string, int> distances;
    // Prédécesseur pour reconstruire le chemin
    unordered_map<string, string> previous;
    unordered_map<string, bool> visited; // Nœuds visités

    // Initialisation de tous les noeud
    Node* current = root;
    while (current)
    {
        distances[current->value] = INT_MAX;// distance infinie
        visited[current->value] = false; // sommet non encore visité

        current = current->next;
    }


    // initialisation du noeud de debut
    distances[start] = 0;
    int iteration = 0;

    // Boucle principale
    while (true)
    {
        // Chercher le nœud minimal non visité
        Node* minNode = getMinDistanceNode(distances, visited);
        if (!minNode) break; // noeud non trouvé
        visited[minNode->value] = true; // marquer ce noeud minimal comme visité

        // affichage des iterations
        std::cout << "\n---------------- Iteration " << iteration++ << " ----------------" << std::endl;
        std::cout << "Nœud courant : " << minNode->value << std::endl;

        // Parcourir les successeurs du nœud courant
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
                    // mettre à jour la distance du noeud suivant si la nouvelle distance est inferieure a la distance actuelle
                    distances[neighbor] = newDist;
                    // mettre a jour le noeud precedent
                    previous[neighbor] = minNode->value;

                }
            }
            // passer au voisin suivant
            edge = edge->next;
        }



        // Afficher l'état actuel des distances
        std::cout << "Distances :\n";
        for (const auto& pair : distances)
        {
            std::cout << pair.first << " : ";
            if (pair.second == INT_MAX)
                std::cout << "INF";
            else
                std::cout << pair.second;
            std::cout << (visited[pair.first] ? " (visité)" : " (non visité)") << std::endl;
        }
    }


    if (distances[end] == INT_MAX)
    {
        cout << "Aucun chemin trouvé de " << start << " à " << end << endl;
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



// Trouver un nœud par sa valeur
Node* Graph::findNode(const string& val) const {
    Node* current = head;
    while (current) {
        if (current->value == val) return current;
        current = current->next;
    }
    return nullptr;
}


// Obtenir le nœud avec la distance minimale non encore visité
Node* Graph::getMinDistanceNode(const unordered_map<string, int>& distances, const unordered_map<string, bool>& visited) const {
    int minDist = INT_MAX;
    Node* minNode = nullptr;

    // on doit parcourir les noeud non visités pour trouver le minimum
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