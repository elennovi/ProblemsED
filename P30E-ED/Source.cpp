// Elena Novillo Luceño
// A51


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

using pii = pair<int, int>; // El par que representa la solucion

pii resolver(bintree<int> const& b) {
    if (b.empty()) return { 0, 0 };
    else {
        pii izq = resolver(b.left());
        pii der = resolver(b.right());
        pii sol = { izq.first + der.first, max(izq.second, der.second) + b.root() };
        if (b.root() > 0 && sol.first == 0) // Si todavia no habia ningun equipo de rescate
            // pero hay un grupo atrapado 
            sol.first++; // entonces debe haber un equipo de rescate
        return sol;
    }
}

void resuelveCaso() {
    bintree<int> b = leerArbol(-1);
    pii sol = resolver(b);
    cout << sol.first << " " << sol.second << endl;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
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