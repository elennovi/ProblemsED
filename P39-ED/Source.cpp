// Elena Novillo Luceño
// A51


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

struct tSol {
    int navegables;
    int caudal;
};

tSol resolver(bintree<int> const& b) {
    // El caso base
    if (b.empty())
        return {0, 0};
    // El caso recursivo
    else {
        tSol izq = resolver(b.left());
        tSol der = resolver(b.right());
        int caudalActual = max(der.caudal + izq.caudal - b.root(), 0);
        // Si es el primer nodo
        if (b.left().empty() && b.right().empty())
            caudalActual = 1;
        int navegablesActual = izq.navegables + der.navegables;
        if (caudalActual >= 3)
            navegablesActual++;
        return { navegablesActual, caudalActual };
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    bintree<int> b = leerArbol(-1);
    tSol sol = resolver(b);
    if (sol.caudal >= 3)
        cout << sol.navegables - 1 << endl;
    else
        cout << sol.navegables << endl;
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