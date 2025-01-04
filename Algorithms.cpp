#include "Algorithms.h"
#include <stack>
#include <queue>


void Algorithms::dijkstra(Graph& graph, const string& start) const
{
	// Récupérer la liste d'adjacence du graphe
	unordered_map<string, vector<pair<string, int>>> list = graph.getList();

	// Vérifier si le graphe ou le nœud de départ ne sont pas vides
	if (list.empty() || start.empty()) {
		std::cout << "Graphe ou le nœud de départ vide" << std::endl;
		return;
	}

	// Vérifier si le nœud de départ existe dans le graphe
	if (list.find(start) == list.end()) {
		std::cout << "Le nœud '" << start << "' n'existe pas !!!" << std::endl;
		return;
	}

	std::cout << std::endl;
	std::cout << "================================================================= " << std::endl;
	std::cout << "---------------------ALGORITHME DE DIJKSTRA---------------------" << std::endl;
	std::cout << "Sommet de départ : " << start << std::endl;
	std::cout << "================================================================= " << std::endl;

	// Les structures de données
	unordered_map<string, int> distances; // Pour les distances minimales
	unordered_map<string, bool> visited;  // Pour marquer les nœuds déjà visités
	unordered_map<string, string> previous; // Pour enregistrer le prédécesseur d'un nœud

	// Initialisation des structures
	for (auto elem : list) {
		distances[elem.first] = INT_MAX;
		visited[elem.first] = false;
	}

	// Initialiser le nœud de départ
	distances[start] = 0;
	previous[start] = "";

	// Boucle principale
	while (true)
	{
		// Récupérer le nœud de plus petite distance et non visité
		string minNode = getMinDistanceNode(list, distances, visited);

		// Arrêter le traitement si tous les nœuds ont été visités
		if (minNode.empty()) break;

		// Marquer le nœud trouvé comme visité
		visited[minNode] = true;

		// Récupérer les successeurs du nœud 
		vector<pair<string, int>> successors = list[minNode];

		// Traitement des successeurs
		for (auto successor : successors)
		{
			// Si le successeur n'a pas été visité, on calcule la nouvelle distance
			if (!visited[successor.first])
			{
				int minDist = distances.at(minNode) + successor.second;

				// Si la nouvelle distance est inférieure à la distance courante, on met à jour
				if (minDist < distances.at(successor.first))
				{
					distances.at(successor.first) = minDist;
					previous[successor.first] = minNode; // Sauvegarder le prédécesseur
				}
			}
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

	// Affichage des chemins à la fin
	std::cout << "\n=================================================================" << std::endl;
	std::cout << "Chemins trouvés depuis le sommet de départ '" << start << "':" << std::endl;
	std::cout << "=================================================================\n";

	for (const auto& pair : distances) {
		if (pair.second != INT_MAX) {
			// Reconstituer le chemin pour chaque nœud atteint
			string currentNode = pair.first;
			std::vector<string> path;

			while (!currentNode.empty()) {
				path.push_back(currentNode);
				currentNode = previous[currentNode];
			}

			// Afficher le chemin (inverser le vecteur pour partir du début)
			std::reverse(path.begin(), path.end());
			std::cout << "Chemin vers " << pair.first << " [Distance: " << pair.second << "] : ";
			for (size_t i = 0; i < path.size(); ++i) {
				std::cout << path[i];
				if (i < path.size() - 1) std::cout << " -> ";
			}
			std::cout << std::endl;
		}
	}
}


void Algorithms::bfs(const Graph& graph, const string& start) const
{
	// Récupérer la liste d'adjacence du graphe
	unordered_map<string, vector<pair<string, int>>> list = graph.getList();

	// Vérifier si le graphe ou le nœud de départ sont vides
	if (list.empty() || start.empty())
	{
		std::cout << "Graphe ou le nœud de départ vide" << std::endl;
		return;
	}

	// Vérifier si le nœud de départ existe dans le graphe
	if (list.find(start) == list.end())
	{
		std::cout << "Le nœud '" << start << "' n'existe pas !!!" << std::endl;
		return;
	}

	// Affichage de l'entête
	std::cout << std::endl;
	std::cout << "================================================================= " << std::endl;
	std::cout << "---------------------PARCOURS EN LARGEUR-------------------------" << std::endl;
	std::cout << "Sommet de départ : " << start << std::endl;
	std::cout << "================================================================= " << std::endl;

	// Initialisation des structures de données
	unordered_map<string, int> distances;   // Distance de chaque nœud par rapport au nœud de départ
	unordered_map<string, string> colors;  // Couleurs des nœuds : blanc (non visité), gris (en cours), noir (traité)
	unordered_map<string, string> parent;  // Prédécesseur de chaque nœud pour reconstruire les chemins

	queue<string> Queue;  // File pour gérer les nœuds à visiter

	// Initialisation des distances, couleurs et parents pour tous les nœuds
	for (auto elem : list)
	{
		distances[elem.first] = INT_MAX; // Distance infinie par défaut
		colors[elem.first] = "blanc";   // Tous les nœuds sont initialement blancs
		parent[elem.first] = "";        // Pas de prédécesseur initial
	}

	// Initialiser le nœud de départ
	distances[start] = 0;   // La distance du nœud de départ à lui-même est 0
	colors[start] = "gris"; // Le nœud de départ devient gris (en cours de traitement)
	parent[start] = "";     // Pas de prédécesseur pour le nœud de départ
	Queue.push(start);      // Ajouter le nœud de départ à la file

	int it = 0; // Compteur pour numéroter les itérations

	// Boucle principale : traiter les nœuds tant que la file n'est pas vide
	while (!Queue.empty())
	{
		// Récupérer et retirer le premier nœud de la file
		string currentNode = Queue.front();
		Queue.pop();

		// Parcourir tous les successeurs du nœud actuel
		for (auto elem : list[currentNode])
		{
			// Si un successeur n'est pas encore visité (blanc)
			if (colors[elem.first] == "blanc")
			{
				// Mettre à jour sa couleur, distance et prédécesseur
				colors[elem.first] = "gris";
				distances[elem.first] = distances[currentNode] + 1;
				parent[elem.first] = currentNode;

				// Ajouter le successeur à la file pour le traiter plus tard
				Queue.push(elem.first);
			}
		}

		// Marquer le nœud actuel comme traité (noir)
		colors[currentNode] = "noir";

		// Affichage de l'état des nœuds après chaque itération
		std::cout << "\n------------------ Iteration " << it++ << " ------------------\n";

		// Afficher les nœuds noirs (traités)
		std::cout << "Nœuds noirs :\n" << std::endl;
		for (auto x : list)
		{
			if (colors[x.first] == "noir")
			{
				std::cout << "- " << x.first << " [Distance: " << distances[x.first] << "] [Couleur: " << colors[x.first] << "]";
				if (!parent[x.first].empty()) std::cout << " [Parent: " << parent[x.first] << "]";
				std::cout << std::endl;
			}
		}
		std::cout << std::endl;

		// Afficher les nœuds gris (en cours de traitement)
		std::cout << "Nœuds gris :\n" << std::endl;
		for (auto x : list)
		{
			if (colors[x.first] == "gris")
			{
				std::cout << "- " << x.first << " [Distance: " << distances[x.first] << "] [Couleur: " << colors[x.first] << "]";
				if (!parent[x.first].empty()) std::cout << " [Parent: " << parent[x.first] << "]";
				std::cout << std::endl;
			}
		}
		std::cout << std::endl;

		// Afficher les nœuds blancs (non visités)
		std::cout << "Nœuds blancs :\n" << std::endl;
		for (auto x : list)
		{
			if (colors[x.first] == "blanc")
			{
				std::cout << "- " << x.first << " [Distance: " << distances[x.first] << "] [Couleur: " << colors[x.first] << "]";
				if (!parent[x.first].empty()) std::cout << " [Parent: " << parent[x.first] << "]";
				std::cout << std::endl;
			}
		}
	}
}



void Algorithms::dfs(const Graph& graph, const string& start) const {
	// Récupération de la liste d'adjacence du graphe
	unordered_map<string, vector<pair<string, int>>> list = graph.getList();

	// Vérification si le graphe ou le nœud de départ est vide
	if (list.empty() || start.empty()) {
		std::cout << "Graphe ou le noeud de depart vide" << std::endl;
		return;
	}

	// Vérification si le nœud de départ existe dans le graphe
	if (list.find(start) == list.end()) {
		std::cout << "Le noeud '" << start << "' n'existe pas!!!" << std::endl;
		return;
	}

	// Affichage de l'entête pour le parcours en profondeur
	std::cout << std::endl;
	std::cout << "================================================================= " << std::endl;
	std::cout << "---------------------PARCOURS EN PROFONDEUR---------------------" << std::endl;
	std::cout << "Sommet de depart : " << start << std::endl;
	std::cout << "================================================================= " << std::endl;

	// Initialisation des structures de données
	unordered_map<string, string> colors; // Suivi des couleurs des nœuds (blanc, gris, noir)
	unordered_map<string, string> parent; // Suivi du parent de chaque nœud
	stack<string> Stack; // Pile pour la gestion des nœuds à visiter

	// Initialisation des nœuds du graphe
	for (auto elem : list) {
		colors[elem.first] = "blanc"; // Tous les nœuds sont initialement blancs
		parent[elem.first] = "";      // Pas de parent initialement
	}

	// Initialisation du nœud de départ
	colors[start] = "gris"; // Le nœud de départ devient gris
	parent[start] = "";     // Pas de parent pour le nœud de départ
	Stack.push(start);      // Ajout du nœud de départ dans la pile

	int it = 0; // Pour numéroter les itérations

	// Parcours en profondeur
	while (!Stack.empty()) {
		string currentNode = Stack.top(); // Récupération du nœud au sommet de la pile
		Stack.pop(); // Suppression du nœud de la pile

		bool foundNeighbor = false; // Indique si un voisin blanc a été trouvé

		// Exploration des voisins du nœud courant
		for (auto elem : list[currentNode]) {
			if (colors[elem.first] == "blanc") {
				colors[elem.first] = "gris";         // Marque le voisin comme gris
				parent[elem.first] = currentNode;   // Définit le nœud courant comme parent
				Stack.push(elem.first);             // Ajoute le voisin à la pile
				foundNeighbor = true;               // Indique qu'un voisin a été trouvé
			}
		}

		colors[currentNode] = "noir"; // Marque le nœud courant comme visité (noir)

		// Affichage de l'état des nœuds pour cette itération
		std::cout << "\n------------------ Iteration " << it++ << " ------------------\n";

		// Afficher les nœuds noirs
		std::cout << "Noeuds noirs :\n";
		for (auto x : list) {
			if (colors[x.first] == "noir") {
				std::cout << "- " << x.first << " [Couleur: " << colors[x.first] << "]";
				if (!parent[x.first].empty()) std::cout << " [Parent: " << parent[x.first] << "]";
				std::cout << std::endl;
			}
		}

		// Afficher les nœuds gris
		std::cout << "\nNoeuds gris :\n";
		for (auto x : list) {
			if (colors[x.first] == "gris") {
				std::cout << "- " << x.first << " [Couleur: " << colors[x.first] << "]";
				if (!parent[x.first].empty()) std::cout << " [Parent: " << parent[x.first] << "]";
				std::cout << std::endl;
			}
		}

		// Afficher les nœuds blancs
		std::cout << "\nNoeuds blancs :\n";
		for (auto x : list) {
			if (colors[x.first] == "blanc") {
				std::cout << "- " << x.first << " [Couleur: " << colors[x.first] << "]";
				if (!parent[x.first].empty()) std::cout << " [Parent: " << parent[x.first] << "]";
				std::cout << std::endl;
			}
		}

		// Si aucun voisin blanc trouvé, afficher le chemin complet jusqu'au nœud courant
		if (!foundNeighbor) {
			std::cout << "\nChemin complet jusqu'au noeud '" << currentNode << "': ";
			string pathNode = currentNode;
			vector<string> path;

			// Reconstruction du chemin depuis le nœud courant jusqu'au nœud de départ
			while (!pathNode.empty()) {
				path.push_back(pathNode);
				pathNode = parent[pathNode];
			}

			// Affichage du chemin dans l'ordre
			reverse(path.begin(), path.end());
			for (size_t i = 0; i < path.size(); ++i) {
				std::cout << path[i];
				if (i < path.size() - 1) std::cout << " -> ";
			}
			std::cout << std::endl;
		}
	}
}


string Algorithms::getMinDistanceNode(
	const unordered_map<string, vector<pair<string, int>>>& list,// la list d'adjacence
	const unordered_map<string, int>& distances, // les distances
	const unordered_map<string, bool>& visited // pour verifier si un noeud est visité
) const
{
	// Initialisation du nœud avec la distance minimale
	string minNode = "";
	int minDist = INT_MAX; // Distance minimale initialisée à la valeur maximale d'un entier

	// Parcours de tous les nœuds de la liste d'adjacence
	for (auto x : list) {
		// Vérifie si le nœud n'a pas été visité et si sa distance est inférieure à la distance minimale trouvée jusqu'ici
		if (!visited.at(x.first) && distances.at(x.first) < minDist) {
			minDist = distances.at(x.first); // Met à jour la distance minimale
			minNode = x.first;               // Met à jour le nœud ayant cette distance minimale
		}
	}

	// Retourne le nœud avec la distance minimale
	return minNode;
}


