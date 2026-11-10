#include "BST.h"
#include "Red-BlackTree.h"

int main() {
    BST bst;
    RedBlackTree rbt;
    for (int i = 1; i <= 20; i++) {
        bst.insertarNodo(i);
        rbt.insertar(i);
    }

    cout << "BST (Ejercicio 1)" << endl;
    cout << "  Altura: " << bst.altura() << endl;
    cout << "  Pre-orden: ";
    bst.imprimirPreOrden();

    cout << "\nRed-Black Tree" << endl;
    cout << "  Altura: " << rbt.altura() << endl;
    cout << "  Pre-orden (N=negro, R=rojo): ";
    rbt.imprimirPreOrden();
    cout << "  Verificacion de propiedades:" << endl;
    bool ok = rbt.verificarPropiedades();
    cout << "  Resultado global: " << (ok ? "VALIDO" : "INVALIDO") << endl;

    cout << "\nn\tBST\tRBT\tRBT valido" << endl;
    for (int n : {20, 100, 1000, 5000}) {
        BST b;
        RedBlackTree r;
        for (int i = 1; i <= n; i++) {
            b.insertarNodo(i);
            r.insertar(i);
        }
        cout << n << "\t" << b.altura() << "\t" << r.altura() << "\t"
             << (r.verificarPropiedades(false) ? "si" : "NO") << endl;
    }
    return 0;
}