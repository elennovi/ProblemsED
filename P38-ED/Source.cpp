// Elena Novillo Luceño
// A51


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

struct tSol {
    int menor; // El elemento menor que se ha encontrado en el arbol
    int mayor; // El elemento mayor que se ha encontrado en el arbol
    bool busqueda; // Indica si el arbol es de búsqueda
};

tSol resolver(bintree<int> const& b) {
    if (!b.empty()) {
        tSol act = { b.root(), b.root(), true };
        if (!b.left().empty()) {
            tSol izq = resolver(b.left());
            // Si el mayor de la izquierda es mayor que la raiz
            // no es un árbol de búsqueda.
            if (izq.mayor >= b.root()) act.busqueda = false;
            else act.busqueda = act.busqueda && izq.busqueda;
            // Actualizamos los valores del elemento mayor y menor
            // si procede
            if (izq.mayor > act.mayor) act.mayor = izq.mayor;
            if (izq.menor < act.menor) act.menor = izq.menor;
        }
        if (!b.right().empty()) {
            tSol der = resolver(b.right());
            // Si el menor de la derecha es menor que la raiz no es
            // un árbol de búsqueda
            if (der.menor <= b.root()) act.busqueda = false;
            else act.busqueda = act.busqueda && der.busqueda;
            // Actualizamos los valores del elemento mayor y menor
            // si procede.
            if (der.mayor > act.mayor) act.mayor = der.mayor;
            if (der.menor < act.menor) act.menor = der.menor;
        }
        return act;
    }
    else
        return { 0, 0, true };
}

void resuelveCaso() {
    bintree<int> arbol = leerArbol(-1);
    tSol sol = resolver(arbol);
    if (sol.busqueda) cout << "SI";
    else cout << "NO";
    cout << endl;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}