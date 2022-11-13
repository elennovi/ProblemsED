// Elena Novillo Luceño
// A51

#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

struct tSol {
    int diametro, altura;
};

tSol resolver(bintree<char> const& b) {
    if (b.empty()) return { 0, 0 }; // Si esta vacío el resultado es 0
    else {
        tSol actual;
        tSol izquierda = resolver(b.left());
        tSol derecha = resolver(b.right());
        actual.diametro = izquierda.altura + derecha.altura + 1; // Suponemos que el diámetro encontrado es el de ese arbol
        if (izquierda.diametro > izquierda.altura + derecha.altura + 1) // Si el máximo ya lo hemos encontrado entonces 
            actual.diametro = izquierda.diametro; // lo sustituimos
        if (derecha.diametro > izquierda.altura + derecha.altura + 1) // Si el máximo ya lo hemos encontrado entonces
            actual.diametro = derecha.diametro; // lo suistituimo
        actual.altura = max(izquierda.altura, derecha.altura) + 1;  // La altura siempre será la rama más larga + 1
        return actual;
    }
}

void resuelveCaso() {
    char aux;
    cin.get(aux); // Leemos el intro
    bintree<char> b = leerArbol('.'); // Leemos el arbol
    tSol sol = resolver(b); // Obtenemos el diametro
    cout << sol.diametro << endl;
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


#ifndef DOMJUDGE 
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}