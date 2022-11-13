// Elena Novillo Luceño
// A51


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

using pii = pair<int, int>;
// El primer elemento se corresponde con el camino más largo
// encontrado que está formado al completo por números pares.
// El segundo elemento se corresponde con el camino actual
// encontradoq que está formado al completo por números pares.

pii resolver(bintree<int> const& b) {
    if (b.empty())
        return {0, 0}; 
    else {
        pii izq = resolver(b.left()); // Devuelve el camino más largo y el actual de pares de la izquierda
        pii der = resolver(b.right()); // Devuelve el camino más largo y el actual de pares de la derecha
        pii act;

        if (b.root() % 2 == 0) { // Si la raiz es par
            act.second = der.second + izq.second + 1;
            act.first = max(max(izq.first, der.first), act.second);

            if (izq.second != 0 && der.second != 0) // Ya se ha completado el camino 
                act.second = max(izq.second, der.second) + 1;
        }
        else {
            act.second = 0;
            act.first = max(izq.first, der.first);
        }
        return act;
    }

}

void resuelveCaso() {
    bintree<int> b = leerArbol(-1);
    pii sol = resolver(b);
    cout << sol.first << endl; 
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); 
#endif 


    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}