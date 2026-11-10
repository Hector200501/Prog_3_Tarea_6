//
// Created by sebas on 10/11/2026.
//

#ifndef PROG_3_TAREA_6_BST_H
#define PROG_3_TAREA_6_BST_H

#include <algorithm>
#include <iostream>
#include <stack>
#include <utility>
#include <vector>

using namespace std;

struct Nodo {
  int dato;
  Nodo* left;
  Nodo* right;

  Nodo(int dato) {
    this->dato = dato;
    left = nullptr;
    right = nullptr;
  }
};

class BST {
private:
  Nodo* raiz = nullptr;

public:
  BST() = default;
  BST(const BST&) = delete;
  BST& operator=(const BST&) = delete;

  ~BST() {
    if (raiz == nullptr) return;
    stack<Nodo*> pila;
    pila.push(raiz);
    while (!pila.empty()) {
      Nodo* nodo = pila.top();
      pila.pop();
      if (nodo->left) pila.push(nodo->left);
      if (nodo->right) pila.push(nodo->right);
      delete nodo;
    }
  }

  bool insertarNodo(int dato) {
    if (raiz == nullptr) {
      raiz = new Nodo(dato);
      return true;
    }
    Nodo* actual = raiz;
    while (true) {
      if (dato < actual->dato) {
        if (actual->left == nullptr) {
          actual->left = new Nodo(dato);
          return true;
        }
        actual = actual->left;
      } else if (dato > actual->dato) {
        if (actual->right == nullptr) {
          actual->right = new Nodo(dato);
          return true;
        }
        actual = actual->right;
      } else {
        return false;
      }
    }
  }

  Nodo* buscarNodo(int dato) {
    Nodo* actual = raiz;
    while (actual != nullptr && actual->dato != dato) {
      actual = (dato < actual->dato) ? actual->left : actual->right;
    }
    return actual;
  }

  bool eliminarNodo(int dato) {
    Nodo* padre = nullptr;
    Nodo* actual = raiz;
    while (actual != nullptr && actual->dato != dato) {
      padre = actual;
      actual = (dato < actual->dato) ? actual->left : actual->right;
    }
    if (actual == nullptr) return false;

    if (actual->left != nullptr && actual->right != nullptr) {
      Nodo* padreSucesor = actual;
      Nodo* sucesor = actual->right;
      while (sucesor->left != nullptr) {
        padreSucesor = sucesor;
        sucesor = sucesor->left;
      }
      actual->dato = sucesor->dato;
      padre = padreSucesor;
      actual = sucesor;
    }

    Nodo* hijo = (actual->left != nullptr) ? actual->left : actual->right;
    if (padre == nullptr) {
      raiz = hijo;
    } else if (padre->left == actual) {
      padre->left = hijo;
    } else {
      padre->right = hijo;
    }
    delete actual;
    return true;
  }

  vector<int> enOrden() {
    vector<int> resultado;
    stack<Nodo*> pila;
    Nodo* actual = raiz;
    while (actual != nullptr || !pila.empty()) {
      while (actual != nullptr) {
        pila.push(actual);
        actual = actual->left;
      }
      actual = pila.top();
      pila.pop();
      resultado.push_back(actual->dato);
      actual = actual->right;
    }
    return resultado;
  }

  void imprimirEnOrden() {
    for (int x : enOrden()) cout << x << " ";
    cout << endl;
  }

  void imprimirPreOrden() {
    if (raiz == nullptr) {
      cout << endl;
      return;
    }
    stack<Nodo*> pila;
    pila.push(raiz);
    while (!pila.empty()) {
      Nodo* nodo = pila.top();
      pila.pop();
      cout << nodo->dato << " ";
      if (nodo->right) pila.push(nodo->right);
      if (nodo->left) pila.push(nodo->left);
    }
    cout << endl;
  }

  int altura() {
    if (raiz == nullptr) return -1;
    int maxProf = 0;
    stack<pair<Nodo*, int>> pila;
    pila.push({raiz, 0});
    while (!pila.empty()) {
      auto [nodo, prof] = pila.top();
      pila.pop();
      maxProf = max(maxProf, prof);
      if (nodo->left) pila.push({nodo->left, prof + 1});
      if (nodo->right) pila.push({nodo->right, prof + 1});
    }
    return maxProf;
  }
};

#endif //PROG_3_TAREA_6_BST_H
