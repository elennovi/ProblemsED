// Elena Novillo Luceño
// A51


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

using pib = pair<int, bool>; // El entero es el número de 
// descendientes que tiene el arbol y el bool indica si es
// o no zurdo

pib resolver(bintree<char> const& b) {
    if (b.empty()) return { 0, true };
    else {
        pib izquierda = resolver(b.left());
        pib derecha = resolver(b.right());
        return { izquierda.first + derecha.first + 1,
                 (izquierda.second && derecha.second &&
                  izquierda.first > (izquierda.first + derecha.first) / 2) ||
                 (b.left().empty() && b.right().empty()) };
    }
}

void resuelveCaso() {
    char aux;
    cin.get(aux); // Leemos el salto de linea
    bintree<char> b = leerArbol('.');
    pib sol = resolver(b);
    if (sol.second)
        cout << "SI";
    else
        cout << "NO";
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