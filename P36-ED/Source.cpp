// Elena Novillo Luceño
// A51


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

struct tSol {
    bool completo;
    bool semi;
    int altura;
};

tSol resolver(bintree<char> const& b) {
    if (b.empty()) return { true, true, 0 };
    else {
        tSol izq = resolver(b.left());
        tSol der = resolver(b.right());
        tSol act = { false, false, max(izq.altura, der.altura) + 1 };
        if (izq.completo && der.completo && (izq.altura == der.altura))
            act.completo = true;
        if (act.completo || (izq.semi && der.completo && (izq.altura == der.altura + 1))
            || (izq.completo && der.semi && izq.altura == der.altura))
            act.semi = true;
        return act;
    }
}

void resuelveCaso() {
    bintree<char> arbol = leerArbol('.');
    tSol sol = resolver(arbol);
    if (sol.completo) cout << "COMPLETO" << endl;
    else if (sol.semi) cout << "SEMICOMPLETO" << endl;
    else cout << "NADA" << endl;
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


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}