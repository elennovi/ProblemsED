w// Elena Novillo Luceño
// A51


#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include "bintree_eda.h"
using namespace std;

struct tSol {
    bool haySol;
    int profundidad, multiplo;
};

class multiplo7 {
public:
    bool operator()(int num) { // Es una propiedad que devuelve un valor indicando si un valor dado 
        return num % 7 == 0; // es múltiplo de 7
    }
};

class primo {
public:
    bool operator()(int num) { // Es una propiedad que devuelve un valor indicando si un valor dado es primo
        if (num % 2 == 0) return false;
        else {
            int i = 3;
            while (i < num / 2 && num % i != 0)
                i = i + 2;
            return num % i != 0;
        }
    }
};

tSol resolver(bintree<int> const& b, multiplo7 m, primo p) {
    if (b.empty()) return { false, 0, 0 }; // Si el arbol es vacio entonces no cumple la propiedad
    else if (p(b.root())) // Si la raiz es un número primo ya no va a existir ningún elemento accesible
        return { false, 0, 0 };

    queue<pair<int, bintree<int>>> q; // El entero se corresponde con el nivel en el que se encuentra
    q.push({ 1, b});

    bool found = false;
    int level = 0;
    int nodo = 0;
    while (!found && !q.empty()) {
        int nivel = q.front().first;
        bintree<int> arbol = q.front().second;
        if (arbol.root() != 7 && m(arbol.root())) {
            found = true;
            level = nivel;
            nodo = arbol.root();
        }
        else if (!p(arbol.root())) {
            if (!arbol.left().empty())
                q.push({ nivel + 1, arbol.left() });
            if (!arbol.right().empty())
                q.push({ nivel + 1, arbol.right() });
        }
        q.pop();
    }
    return { found, level, nodo };
}

void resuelveCaso() {
    bintree<int> b = leerArbol(-1);
    multiplo7 m;
    primo p;
    tSol sol = resolver(b, m, p);
    if (sol.haySol) cout << sol.multiplo << " " << sol.profundidad << endl;
    else cout << "NO HAY" << endl;
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