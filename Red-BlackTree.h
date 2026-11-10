#ifndef PROG_3_TAREA_6_RED_BLACKTREE_H
#define PROG_3_TAREA_6_RED_BLACKTREE_H

#include <algorithm>
#include <iostream>
#include <stack>
#include <utility>

using namespace std;

enum Color { ROJO, NEGRO };

struct NodoRB {
  int dato;
  Color color;
  NodoRB* left;
  NodoRB* right;
  NodoRB* parent;

  NodoRB(int dato, NodoRB* parent = nullptr) {
    this->dato = dato;
    this->color = ROJO;
    left = nullptr;
    right = nullptr;
    this->parent = parent;
  }
};

class RedBlackTree {
private:
  NodoRB* raiz = nullptr;

  static bool esRojo(NodoRB* n) { return n != nullptr && n->color == ROJO; }

  void rotarIzquierda(NodoRB* x) {
    NodoRB* y = x->right;
    x->right = y->left;
    if (y->left != nullptr) y->left->parent = x;

    y->parent = x->parent;
    if (x->parent == nullptr) raiz = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;

    y->left = x;
    x->parent = y;
  }

  void rotarDerecha(NodoRB* x) {
    NodoRB* y = x->left;
    x->left = y->right;
    if (y->right != nullptr) y->right->parent = x;

    y->parent = x->parent;
    if (x->parent == nullptr) raiz = y;
    else if (x == x->parent->right) x->parent->right = y;
    else x->parent->left = y;

    y->right = x;
    x->parent = y;
  }

  void corregirInsercion(NodoRB* z) {
    while (esRojo(z->parent)) {
      NodoRB* padre = z->parent;
      NodoRB* abuelo = padre->parent;

      if (padre == abuelo->left) {
        NodoRB* tio = abuelo->right;
        if (esRojo(tio)) {
          padre->color = NEGRO;
          tio->color = NEGRO;
          abuelo->color = ROJO;
          z = abuelo;
        } else {

          if (z == padre->right) {
            z = padre;
            rotarIzquierda(z);
            padre = z->parent;
          }
          padre->color = NEGRO;
          abuelo->color = ROJO;
          rotarDerecha(abuelo);
        }
      } else {
        NodoRB* tio = abuelo->left;
        if (esRojo(tio)) {
          padre->color = NEGRO;
          tio->color = NEGRO;
          abuelo->color = ROJO;
          z = abuelo;
        } else {
          if (z == padre->left) {
            z = padre;
            rotarDerecha(z);
            padre = z->parent;
          }
          padre->color = NEGRO;
          abuelo->color = ROJO;
          rotarIzquierda(abuelo);
        }
      }
    }
    raiz->color = NEGRO;
  }

public:
  RedBlackTree() = default;
  RedBlackTree(const RedBlackTree&) = delete;
  RedBlackTree& operator=(const RedBlackTree&) = delete;

  ~RedBlackTree() {
    if (raiz == nullptr) return;
    stack<NodoRB*> pila;
    pila.push(raiz);
    while (!pila.empty()) {
      NodoRB* nodo = pila.top();
      pila.pop();
      if (nodo->left) pila.push(nodo->left);
      if (nodo->right) pila.push(nodo->right);
      delete nodo;
    }
  }

  bool insertar(int dato) {
    NodoRB* padre = nullptr;
    NodoRB* actual = raiz;
    while (actual != nullptr) {
      padre = actual;
      if (dato < actual->dato) actual = actual->left;
      else if (dato > actual->dato) actual = actual->right;
      else return false;
    }

    NodoRB* nuevo = new NodoRB(dato, padre);
    if (padre == nullptr) raiz = nuevo;
    else if (dato < padre->dato) padre->left = nuevo;
    else padre->right = nuevo;

    corregirInsercion(nuevo);
    return true;
  }

  int altura() {
    if (raiz == nullptr) return -1;
    int maxProf = 0;
    stack<pair<NodoRB*, int>> pila;
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

  void imprimirPreOrden() {
    if (raiz == nullptr) {
      cout << endl;
      return;
    }
    stack<NodoRB*> pila;
    pila.push(raiz);
    while (!pila.empty()) {
      NodoRB* nodo = pila.top();
      pila.pop();
      cout << nodo->dato << (nodo->color == ROJO ? "(R) " : "(N) ");
      if (nodo->right) pila.push(nodo->right);
      if (nodo->left) pila.push(nodo->left);
    }
    cout << endl;
  }

  bool verificarPropiedades(bool verbose = true) {
    bool p1 = true, p2 = true, p3 = true, p4 = true, p5 = true;
    bool bst = true, punteros = true;

    if (raiz == nullptr) return true;

    p2 = (raiz->color == NEGRO);
    if (raiz->parent != nullptr) punteros = false;

    int negrosReferencia = -1;
    stack<pair<NodoRB*, int>> pila;
    pila.push({raiz, 0});
    while (!pila.empty()) {
      auto [nodo, negros] = pila.top();
      pila.pop();

      if (nodo->color != ROJO && nodo->color != NEGRO) p1 = false;
      if (nodo->color == ROJO && (esRojo(nodo->left) || esRojo(nodo->right)))
        p3 = false;

      int negrosAqui = negros + (nodo->color == NEGRO ? 1 : 0);
      NodoRB* hijos[2] = {nodo->left, nodo->right};
      for (NodoRB* h : hijos) {
        if (h == nullptr) {
          if (negrosReferencia == -1) negrosReferencia = negrosAqui;
          else if (negrosReferencia != negrosAqui) p4 = false;
        } else {
          if (h->parent != nodo) punteros = false;
          pila.push({h, negrosAqui});
        }
      }
    }

    stack<NodoRB*> s;
    NodoRB* actual = raiz;
    bool hayPrevio = false;
    int previo = 0;
    while (actual != nullptr || !s.empty()) {
      while (actual != nullptr) {
        s.push(actual);
        actual = actual->left;
      }
      actual = s.top();
      s.pop();
      if (hayPrevio && actual->dato <= previo) bst = false;
      previo = actual->dato;
      hayPrevio = true;
      actual = actual->right;
    }

    bool ok = p1 && p2 && p3 && p4 && p5 && bst && punteros;
    if (verbose) {
      auto linea = [](const char* nombre, bool v) {
        cout << "  " << nombre << ": " << (v ? "OK" : "FALLA") << endl;
      };
      linea("P1 cada nodo es rojo o negro   ", p1);
      linea("P2 la raiz es negra            ", p2);
      linea("P3 rojo no tiene hijo rojo     ", p3);
      linea("P4 mismos negros en cada camino", p4);
      linea("P5 hojas nulas negras          ", p5);
      linea("Orden BST (in-order creciente) ", bst);
      linea("Punteros padre consistentes    ", punteros);
    }
    return ok;
  }
};

#endif //PROG_3_TAREA_6_RED_BLACKTREE_H
