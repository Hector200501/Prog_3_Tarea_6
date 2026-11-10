#include "BST.h"

int main() {
    BST bst;
    vector<int> datos = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35,
                         45, 55, 65, 75, 85, 5, 15, 22, 90, 1};
    for (int x : datos) bst.insertarNodo(x);

    cout << "Insertados 20 elementos. Altura: " << bst.altura() << endl;
    cout << "In-order: ";
    bst.imprimirEnOrden();

    cout << "Eliminar 20 (dos hijos): " << (bst.eliminarNodo(20) ? "ok" : "no existe") << endl;
    cout << "Eliminar 1  (hoja)     : " << (bst.eliminarNodo(1) ? "ok" : "no existe") << endl;
    cout << "Eliminar 999 (no existe): " << (bst.eliminarNodo(999) ? "ok" : "no existe") << endl;

    cout << "In-order tras eliminar: ";
    bst.imprimirEnOrden();
    cout << "Altura final: " << bst.altura() << endl;

    cout << "\n--- Degradacion con datos ascendentes ---" << endl;
    cout << "n\tAltura\tAltura minima posible" << endl;
    for (int n : {20, 100, 1000, 5000}) {
        BST b;
        for (int i = 1; i <= n; i++) b.insertarNodo(i);
        int minima = 0;
        while ((1 << (minima + 1)) - 1 < n) minima++;
        cout << n << "\t" << b.altura() << "\t" << minima << endl;
    }
    return 0;
}