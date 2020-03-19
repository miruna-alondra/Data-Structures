// Copyright 2019 SD_Homework_Team

#ifndef SOLVER_H_
#define SOLVER_H_
#include <fstream>
#include <string>
#include "Hashtable.h"
#include "Graph.h"

int my_hash(std::string str) {
    int hkey = 5381;
    hkey =  (hkey % 5) + str.length();
    return hkey;
}

class solver {
	public:
	int N;
	int M;
	Graph<int> *G;
	Hashtable<std::string, int> *hashtable;
	~solver() {
		delete G;
		delete hashtable;
	}
		void task1_solver(std::ifstream& fin, std::ofstream& fout) {
		// Citesc numarul de intersectii si de strazi si declar
		// 2 variabile de tip string pentru a putea citi strazile.
			fin >> N;
			fin >> M;
			std::string str1, str2;
			// Declar o variabila Q1 pentru numarul de interogari
			// ale intersectiilor intre care trebuie sa verific
			// daca exista drum sau nu.
			int Q1;
			G = new Graph<int>(N, M);
			// Declar un vector de stringuri pentru a memora
			// intersectiile in ordinea in care sunt prezentate.
			std::string intersectii[1000];
			hashtable = new Hashtable<std::string, int>(N, &my_hash);
			for (int i = 0; i < N; i++) {
        		fin >> intersectii[i];
        		// Inserez fiecare intersectie intr-o structura de
        		// tip Hashtable pentru a obtine indecsii
        		// necesari pentru a realiza graful.
       			hashtable->put(intersectii[i], i);
    		}
    		for (int i = 0; i < M; i++) {
    		// Citesc fiecare set de intersectii intre care
    		// exista drum.
        		fin >> str1 >> str2;
        		// Ma folosesc de Hashtable pentru
        		// realizarea grafului.
       			int hkey1 = hashtable->get(str1);
       			int hkey2 = hashtable->get(str2);
       			G->addEdge(hkey1, hkey2);
    		}
    		fin >> Q1;
    		for (int i = 0; i < Q1; i++) {
    		// Citesc intersectiile intre care trebuie verificat
    		// daca exista drum.
        		fin >> str1 >> str2;
        		// Ma folosesc de Hashtable pentru a ma folosi
        		// de indecsii din graf pentru a vedea daca
        		// exista drum. Daca exista, afisez "y",
        		// daca nu afisez "n". Pentru aceasta verificare
        		// ma folosesc de metoda din graf, Path care
        		// returneaza o stiva cu nodurile parcurse
        		// in drumul de la sursa la destinatie.
        		// Daca este goala, inseamna ca nu exista drum.
        		int hkey1 = hashtable->get(str1);
        		int hkey2 = hashtable->get(str2);
        		if (hkey1 == hkey2) {
        			fout << "y" << '\n';
        		} else if (G->Path(hkey1, hkey2).empty()) {
            		fout << "n" << '\n';
        		} else {
            		fout << "y" << '\n';
        		}
    		}
		 }

		void task2_solver(std::ifstream& fin, std::ofstream& fout) {
		// Declar o variabila Q2 care reprezinta numarul de
		// intersectii pentru care trebuie sa afisez distanta
		// dintre ele, daca exista drum.
			int Q2;
			std::string str1, str2;
			fin >> Q2;
			for (int i = 0; i < Q2; i++) {
			// Declar o variabila care va memora distanta
			// dintre intersectii, daca exista drum. Pentru
			// calcularea distantei ma folosesc de o metoda
			// din graf, distance, care imi returneaza
			// lungimea drumului dintre intersectii, daca
			// acesta exista si -1 in caz contrar.
				int distance;
				fin >> str1 >> str2;
				int hkey1 = hashtable->get(str1);
				int hkey2 = hashtable->get(str2);
				distance = G->distance(hkey1, hkey2);
				fout << distance << std::endl;
			}
		}

		void task3_solver(std::ifstream& fin, std::ofstream& fout) {
		// Declar 2 variabile, Q3 - numarul de modificari
		// realizate in graf, nr - care ia valorile de
		// la 0 la 3, reprezentand o caracteristica a
		// tipului de modificare in graf si c - care
		// poate fi c sau q, o alta caracteristica a
		// tipului de modificare.
			int Q3, nr;
			char c;
			// Citesc numarul de modificari din fisier.
			fin >> Q3;
			std::string str1, str2, str3;
			for (int i = 0; i < Q3; i++) {
			// Citesc prima caracteristica, c, si verific
			// daca este 'c' sau 'q'.
				fin >> c;
				if (c == 'c') {
				// Citesc fiecare element de pe linie si
				// ma folosesc de hashtable pentru a lua
				// indexul fiecarei intersectii de pe linie.
					fin >> str1 >> str2 >> nr;
					int hkey1 = hashtable->get(str1);
					int hkey2 = hashtable->get(str2);
					// Daca nr e 0 se va crea un drum intre cele
					// 2 intersectii.
					if (nr == 0) {
						G->addEdge(hkey1, hkey2);
					}
					// Daca nr e 1, se vor bloca toate drumurile
					// directe
					// intre cele 2 intersectii. Ma folosesc
					// de metodele grafului care verifica daca
					// daca exista drum direct (isEdge) si
					// removeEdge care sterge drumul.
					if (nr == 1) {
						if (G->isEdge(hkey1, hkey2) == true) {
							G->removeEdge(hkey1, hkey2);
						} else if (G->isEdge(hkey2, hkey1) == true) {
							G->removeEdge(hkey2, hkey1);
						}
					}
					// Daca nr e 2, se va realiza un drum bidirectional.
					// Daca exista deja, se ignora modificarea.
					if (nr == 2) {
						if (G->isEdge(hkey1, hkey2)) {
							G->addEdge(hkey2, hkey1);
						} else if (G->isEdge(hkey2, hkey1)) {
							G->addEdge(hkey1, hkey2);
						} else {
							G->addEdge(hkey2, hkey1);
							G->addEdge(hkey1, hkey2);
						}
					}
					// Daca nr e 3, se va schimba sensul drumului
					// intre intersectii. Daca nu exista, se
					// ignora modificarea.
					if (nr == 3) {
						if (G->isEdge(hkey1, hkey2)) {
							G->removeEdge(hkey1, hkey2);
							G->addEdge(hkey2, hkey1);
						} else if (G->isEdge(hkey2, hkey1)) {
							G->removeEdge(hkey2, hkey1);
							G->addEdge(hkey1, hkey2);
						} else {
							break;
						}
					}
			}
			if (c == 'q') {
				fin >> str1 >> str2 >> nr;
				int hkey1;
				hkey1 = hashtable->get(str1);
				int hkey2;
				hkey2 = hashtable->get(str2);
				int distance;
				distance = -1;
				// Daca nr e 0 se va realiza acelasi lucru
				// ca la task-ul 1.
				if (nr == 0) {
					if (!G->Path(hkey1, hkey2).empty()) {
						fout << "y" << std::endl;
					} else {
						fout << "n" << std::endl;
					}
				}
				// Daca nr e 1, se va afisa lungimea drumului
				// dintre intersectii, daca acesta exista.
				if (nr == 1) {
					if (!G->Path(hkey1, hkey2).empty()) {
						fout << G->distance(hkey1, hkey2) << std::endl;
					} else {
					fout << distance << std::endl;
					}
				}
				// Daca nr e 2, se va afisa lungimea drumului
				// minim dintre intersectiile a si b, care
				// trece obligatoriu prin c, daca exista.
				if (nr == 2) {
					fin >> str3;
					int hkey3 = hashtable->get(str3);
					int distance = -1;
					if (hkey2 == hkey3) {
						distance = G->distance(hkey1, hkey2);
						fout << distance << std::endl;
					} else if (!G->Path(hkey1, hkey3).empty() &&
					            !G->Path(hkey3, hkey2).empty()) {
						distance = G->distance(hkey1, hkey3) + G->distance(hkey3, hkey2);
						fout <<	distance << std::endl;
					} else {
						fout << distance << std::endl;
					}
				}
			}
		}
	}
		void task4_solver(std::ifstream& fin, std::ofstream& fout) { }

		void task5_solver(std::ifstream& fin, std::ofstream& fout) {
		 }
};
#endif  // SOLVER_H_
