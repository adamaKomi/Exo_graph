#include "bfs.h"
#include <queue>

bfs::bfs()
{
}

void bfs::bfs_algo(Node* node,string& start) 
{

    if (start.empty()) start = node->value;

    Node* debut = findNode(start);
    if (!debut)
    {
        std::cout << "Le noeud '" << start << "' n'existe pas!!!" << std::endl;
        return;
    }

    std::cout << std::endl;
    std::cout << "================================================================= " << std::endl;
    std::cout << "---------------------PARCOURS EN LARGEUR______________________" << std::endl;
    std::cout << "Sommet de depart : " << start << std::endl;
    std::cout << "================================================================= " << std::endl;

    // pour marquer les couleurs
    unordered_map<Node*, string> color;
    // pour marquer les numeros des deux par rapport au noeud d'origine 
    unordered_map<Node*, int> distances;
    // pour marquer le parent de chaque noeud
    unordered_map<Node*, Node*> parent;
    // pour le traitement en utilisant FIFO
    queue<Node*> Queue;

    // Initialiser tous les n�uds
    Node* current = node;
    while (current)
    {
        color[current] = "blanc";
        distances[current] = INT_MAX;
        parent[current] = nullptr;
        current = current->next;
    }

    // Initialiser le n�ud de d�part
    color[debut] = "gris";// la couleur est gris car il sera ajouter a la queue
    distances[debut] = 0;// mettre le numero du noeud initial a 0
    parent[debut] = nullptr;// le noeud initial n'a pas de parent

    Queue.push(debut);// enfiler l noeud initial

    int it = 0;// pour numeroter les iterations

    // boucler sur la queue et traiter tous les noeuds
    while (!Queue.empty())
    {
        // recuperer le noeud qui est en t�te de la queue
        Node* current = Queue.front();
        // defiler le noeud de t�te
        Queue.pop();

        // recuperer les ar�tes du noeud courant
        Edge* edge = current->successors;

        // pour chaque ar�te, on traite le successeur du noeud courant
        while (edge)
        {
            // recuperer le noeud de destination de l'ar�te courante
            Node* successor = edge->destination;
            // traiter le noeud s'il n'a pas encore �t� visit�
            if (color[successor] == "blanc")
            {
                Queue.push(successor);// ajouter a la queue
                color[successor] = "gris";// mettre la couleur � gris
                parent[successor] = current; // mettre a jour le parent de ce successeur
                distances[successor] = distances[current] + 1; // mette � jour le numero
            }
            edge = edge->next;// passer a l'ar�te suivante
        }
        // mettre la couleur du noeud courant � noir car tous ces fils ont �t� ajout�s a la queue
        color[current] = "noir";


        // Affichage de l'�tat des n�uds � cette it�ration

        std::cout << "\n------------------ Iteration " << it++ << " ------------------\n";

        // Afficher les n�uds noirs
        std::cout << "Noeuds noirs :\n" << std::endl;
        for (Node* tmp = node; tmp != nullptr; tmp = tmp->next)
        {
            if (color[tmp] == "noir")
            {
                std::cout << "- " << tmp->value << " [Distance: " << distances[tmp] << "] [Couleur: " << color[tmp] << "]";
                if (parent[tmp]) std::cout << " [Parent: " << parent[tmp]->value << "]";
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;
        // Afficher les n�uds gris
        std::cout << "Noeuds gris :\n" << std::endl;
        for (Node* tmp = node; tmp != nullptr; tmp = tmp->next)
        {
            if (color[tmp] == "gris")
            {
                std::cout << "- " << tmp->value << " [Distance: " << distances[tmp] << "] [Couleur: " << color[tmp] << "]";
                if (parent[tmp]) std::cout << " [Parent: " << parent[tmp]->value << "]";
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;
        // Afficher les n�uds blancs
        std::cout << "Noeuds blancs :\n" << std::endl;
        for (Node* tmp = node; tmp != nullptr; tmp = tmp->next)
        {
            if (color[tmp] == "blanc")
            {
                std::cout << "- " << tmp->value << " [Distance: " << distances[tmp] << "] [Couleur: " << color[tmp] << "]";
                std::cout << std::endl;
            }
        }
    }

    std::cout << "\nFIN\n";

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
