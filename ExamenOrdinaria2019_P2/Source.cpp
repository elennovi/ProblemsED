// Elena Novillo Luceño
// A51


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

struct tSol {
    int caminoActual;
    int caminoMax;
};

tSol resolver(bintree<int> const& b) {
    if (b.empty()) {
        return { 0, 0 };
    }
    else {
        tSol izq = resolver(b.left());
        tSol der = resolver(b.right());
        tSol actual;
        // Si el nodo que estamos recorriendo no es par
        if (b.root() % 2 != 0) {
            actual.caminoActual = 0;
            actual.caminoMax = max(izq.caminoMax, der.caminoMax);
        }
        // Si el nodo que estamos recorriendo es par
        else {
            actual.caminoActual = izq.caminoActual + der.caminoActual + 1;
            actual.caminoMax = max(actual.caminoActual, max(izq.caminoMax, der.caminoMax));
        }
        return actual;
    }
}

void resuelveCaso() {
    bintree<int> b = leerArbol(-1);
    tSol sol = resolver(b);
    cout << sol.caminoMax << endl;
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