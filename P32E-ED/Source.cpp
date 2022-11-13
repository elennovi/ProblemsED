// Elena Novillo Luceño
// A51

#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

using pii = pair<int, int>; 
// pii.first = es la altura del arbol completo actual
// pii.second = es la altura del arbol completo máximo

pii resolver(bintree<char> const& b) {
    if (b.empty()) return {0, 0};
    else {
        pii izq = resolver(b.left());
        pii der = resolver(b.right());
        pii act = { min(izq.first, der.first) + 1, max(izq.second, der.second) };
        if (izq.first == der.first)
            act.second = max(act.second, izq.first + 1);
        return act;
    }
}

void resuelveCaso() {
    char aux;
    cin.get(aux);
    bintree<char> b = leerArbol('.');
    pii sol = resolver(b);
    cout << sol.second << endl;
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