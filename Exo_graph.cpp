// Exo_graph.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//



#include <iostream>
#include <memory>
#include "Algorithms.h"


int main() {
    try {
        // Création d'un graphe
        Graph graph(true);
        auto algo = std::make_unique<Algorithms>();

        // Ajouter des arêtes orientées
        graph.addEdge("S", "R", 7);
        graph.addEdge("S", "W", 3);
        graph.addEdge("R", "V", 1);
        graph.addEdge("W", "T", 2);
        graph.addEdge("W", "X", 8);
        graph.addEdge("T", "X", 4);
        graph.addEdge("T", "U", 11);
        graph.addEdge("X", "U", 8);
        graph.addEdge("X", "Y", 3);
        graph.addEdge("U", "Y", 2);

        // Affichage initial du graphe
        std::cout << "\n================ GRAPHE ================\n";
        graph.printGraph();

        // Menu interactif avec do-while
        int choix;
        std::string startNode = "";

        do {
            std::cout << "\n================ MENU =================\n";
            std::cout << "1. Parcours en largeur (BFS)\n";
            std::cout << "2. Parcours en profondeur (DFS)\n";
            std::cout << "3. Algorithme de Dijkstra\n";
            std::cout << "0. Quitter\n";
            std::cout << "======================================\n";
            std::cout << "Choisissez une option : ";
            std::cin >> choix;


            if (choix > 0 && choix <= 3)
            {
                std::cout << "Choisissez un noeud de depart : ";
                std::cin >> startNode;
            }


            // Traitement des choix
            switch (choix) {
            case 1:
                std::cout << "\n--- Parcours en largeur (BFS) ---\n";
                algo->bfs(graph, startNode);
                break;
            case 2:
                std::cout << "\n--- Parcours en profondeur (DFS) ---\n";
                algo->dfs(graph, startNode);
                break;
            case 3:
                std::cout << "\n--- Algorithme de Dijkstra ---\n";
                algo->dijkstra(graph, startNode);
                break;
            case 0:
                std::cout << "Quitter le programme.\n";
                break;
            default:
                std::cout << "Option invalide. Veuillez réessayer.\n";
                break;
            }
        } while (choix != 0); // Répéter jusqu'à ce que l'utilisateur choisisse de quitter
    }
    catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Erreur inconnue." << std::endl;
    }

    return 0;
}
