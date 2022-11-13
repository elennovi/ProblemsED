// Elena Novillo Luceño
// A51

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "bintree_eda.h"
using namespace std;

template <class T>
T resolver(bintree<T> const& b) {
    T minimo = b.root();
    if (!(b.left().empty())) { // No accedemos a ramas vacías porque no podemos proporcionar un mínimo
        T minIzquierda = resolver(b.left());
        if (minIzquierda < minimo)
            minimo = minIzquierda;
    }
    if (!(b.right().empty())) { // No accedemos a ramas vacías porque no podemos proporcionar un mínimo
        T minDerecha = resolver(b.right());
        if (minDerecha < minimo)
            minimo = minDerecha;
    }
    return minimo;
}

bool resuelveCaso() {
    string aux;
    cin >> aux; // Leemos el tipo de dato del arbol que vamos a leer
    if (!std::cin)
        return false;
    if (aux == "N") {
        bintree<int> b = leerArbol(-1); // Leemos el arbol de números
        int min = resolver(b);
        cout << min;
    }
    else {
        string vacio = "#";
        bintree<string> b = leerArbol(vacio); // Leemos los datos del arbol de strings
        string min = resolver(b);
        cout << min;
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


    while (resuelveCaso())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}