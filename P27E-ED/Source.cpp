// Elena Novillo Luceño
// A51


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector> // Para almacenar la frontera utilizaremos un vector
#include "bintree_eda.h"
using namespace std;

template <class T>
void resolver(bintree<T> const& b, vector<T>& v) {
    if (!b.empty()) { // Si todavía quedan por recorrer
        resolver(b.left(), v);
        resolver(b.right(), v);
        if (b.left().empty() && b.right().empty()) 
            v.push_back(b.root()); // Si el que hemos encontrado es hoja entonces
        // lo metemos en el vector
    }
}

void resuelveCaso() {
    bintree<int> b = leerArbol(-1); // Leemos el árbol de la entrada
    vector<int> v; // Creamos un vector
    resolver(b, v);
    for (int e : v) {
        cout << e << " ";
    }
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