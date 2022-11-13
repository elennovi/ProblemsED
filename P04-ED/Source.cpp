// Elena Novillo Luceño
// A51

#include <iostream>
#include <fstream>
#include "Polinomio.h"

bool resuelveCaso() {
    int numX;
    int x;
    Polinomio p = Polinomio(); // Creamos el polinomio
    int coef, expo;
    cin >> coef >> expo;
    if (!std::cin)
        return false;
    while (coef != 0 || expo != 0) {
        p.insert({coef, expo}); // Inserta el nuevo monomio en el polinomio
        cin >> coef >> expo;
    }
    cin >> numX;
    for (int i = 0; i < numX; i++) {
        cin >> x;
        cout << p.resolver(x) << " ";
    }
    cout << endl;
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 

    while (resuelveCaso());

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}