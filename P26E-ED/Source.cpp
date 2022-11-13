// Elena Novillo Luceño
// A51


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h" // Para poder extender de la clase
using namespace std;

struct tSol { // El struct solucion que contiene la información pedida
    int nodos, altura, hojas;
};

template <class T>
tSol resolver(bintree<T> const& b) { // La función externa que resuelve el problema
    if (b.empty()) return { 0, 0, 0 };
    else {
        tSol sIzquierda = resolver(b.left());
        tSol sDerecha = resolver(b.right());
        return { sIzquierda.nodos + sDerecha.nodos + 1, // Tenemos un nodo más
            max(sIzquierda.altura, sDerecha.altura) + 1, // El máximo de la altura
            (b.left().empty() && b.right().empty()) + sIzquierda.hojas + sDerecha.hojas};
        // Es hoja si no tiene más ramas
    }
}

void resuelveCaso() {
    char aux;
    cin.get(aux);
    bintree<char> b = leerArbol<char>('.'); // ????????
    tSol s = resolver(b); // La función que resuelve el problema
    cout << s.nodos << " " << s.hojas << " " << s.altura << endl;
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