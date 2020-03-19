// Copyright 2019 Cocor Miruna-Alondra grupa 312CA

#ifndef GRAPH_H_
#define GRAPH_H_
#include <vector>
#include <list>
#include <string>
#include <utility>
#include <stack>
#include <queue>
#include <algorithm>

template <typename T> class Graph {
 private:
	int numIntersections;
	int numStreets;
	std::vector<std::vector<T> > streets;

 public:
// Constructor
	Graph(int N, int M) {
		this->numIntersections = N;
		this->numStreets = M;
		streets.resize(numIntersections, std::vector<T>());
	}
	// Adauga drum intre 2 noduri.
	void addEdge(int i, int j) {
	    streets[i].push_back(j);
	}
	// Verifica daca exista drum intre 2 noduri.
	bool isEdge(int i, int j) {
	    return std::find(streets[i].begin(),
	     streets[i].end(), j) != streets[i].end();
	}
	// Sterge drumul dintre 2 noduri.
	void removeEdge(int i, int j) {
		int aux;
		for (auto x : streets[i]) {
			if (j == x) {
				aux = x;
			}
		}
		for (int k = aux; k < streets[i].size(); k++) {
			for (int l = k + 1; l < streets[i].size(); l++) {
				int temp = streets[i][k];
				streets[i][k] = streets[i][l];
				streets[i][l] = temp;
			}
		}
		streets[i].pop_back();
	}
// Metoda returneaza o stiva care contine
// toate nodurile parcurse in timpul bfs-ului
// de la sursa la destinatie.
	std::stack<int> Path(int source, int dest) {
	// Initializari
	std::vector<int> parent(numIntersections, -1);
	std::vector<bool> visited(numIntersections, false);
	std::stack<int> path;
	std::queue<int> queue;
	// Introduc sursa si vecinii ei in coada si cat timp
	// nu este goala, vizitez nodurile vecine.
	queue.push(source);
	while (!queue.empty()) {
		int node = queue.front();
		queue.pop();
		visited[node] = true;
		// Iterez pe fiecare vector al fiecarui vecin
		// si umplu vectorul de parinti.
		for (auto street : streets[node]) {
			if (!visited[street]) {
				queue.push(street);
				parent[street] = node;
			}
		}
	}
	if (parent[dest] == -1) {
		return path;
	}
	// Incep realizarea drumul de la destinatie spre sursa.
	while (dest != -1) {
		path.push(dest);
		dest = parent[dest];
	}
	return path;
    }
    // Calculez distanta drumului dintre intersectii,
    // utilizand bfs-ul si un vector de distante.
    // Metoda e asemanatoare celei care realizeaza
    // drumul de la sursa la destinatie.
	int distance(int source, int dest) {
	std::vector<int> parent(numIntersections, -1);
	std::vector<bool> visited(numIntersections, false);
	std::vector<int> distance(numIntersections, 0);
	std::stack<int> path;
	std::queue<int> queue;
	if (source == dest) {
		distance[dest] = 0;
		return distance[dest];
	}
	queue.push(source);
	while (!queue.empty()) {
		int node = queue.front();
		queue.pop();
		visited[node] = true;
		if (node == dest) {
			break;
		}
		for (auto street : streets[node]) {
			if (!visited[street]) {
				visited[street] = true;
				parent[street] = node;
				distance[street] = distance[node] + 1;
				parent[street] = node;
				queue.push(street);
				if (street == dest) {
					return distance[dest];
				}
			}
		}
	}
	if (parent[dest] == -1) {
		return -1;
	}
	while (dest != -1) {
			path.push(dest);
			dest = parent[dest];
	}

	return distance[dest];
    }
};
#endif  // GRAPH_H_
