// Copyright 2019 Cocor Miruna-Alondra grupa 312CA

#ifndef HASHTABLE_H_
#define HASHTABLE_H_
#include <vector>
#include <list>
#include <string>
#include <utility>
#include <stack>
#include <queue>
#include <iterator>
// Folosesc aceasta structura de tip info
// ca fiind un element al Hashtable-ului.
template <typename Tkey, typename Tvalue> struct info {
  Tkey key;
  Tvalue value;
  info(Tkey key, Tvalue value) {
    this->key = key;
    this->value = value;
  }
};

template <typename Tkey, typename Tvalue> class Hashtable {
 private:
  std::list<struct info<Tkey, Tvalue> > *H;
  int size;
  int capacity;
  int (*hash)(Tkey);

 public:
// Constructor
  Hashtable(int capacity, int (*h)(Tkey)) {
    this->capacity = capacity;
    H = new std::list<struct info<Tkey, Tvalue> >[capacity];
    size = 0;
    hash = h;
  }
  // Destructor
  ~Hashtable() {
    delete[] H;
  }
// Metoda insereaza in structura o cheie
// si o valoare. Daca exista deja cheia,
// se va actualiza valoarea.
  void put(Tkey key, Tvalue value) {
    struct info<Tkey, Tvalue> x(key, value);
    int hkey = hash(key) % capacity;
    int count = 0;
    for (auto x : H[hkey]) {
      if (x.key == key) {
        x.value = value;
        count++;
      }
    }
    if (count  == 0) {
      H[hkey].push_back(x);
      size++;
    }
  }
// Metoda returneaza valoarea
// corespunzatoare cheii date
// ca parametru, iterand in
// pe ficare element din hashtable.
  Tvalue get(Tkey key) {
    int hkey = hash(key) % capacity;
    int count = 0;
    for (auto x : H[hkey]) {
      if (x.key == key) {
        return x.value;
        count++;
      }
    }
    if (count == 0) {
      return Tvalue();
    }
  }
// Metoda verifica daca exista cheia
// pe care o cautam.
  bool has_key(Tkey key) {
    int hkey = hash(key) % capacity;
    for (auto x : H[hkey]) {
      if (x.key == key) {
        return true;
      }
    }
    return false;
  }
};
#endif  // HASHTABLE_H_
