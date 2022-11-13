// Elena Novillo Luceño
// A51


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

void resolver(bintree<int> const& b) {
    if (!b.empty()) { // Solo guardamos el arbol si no es nulo (es decir, si no está vacío)
        queue<pair<int, bintree<int>>> cola;

        // El primer elemento del arbol siempre va a pertenecer al perfil izquierdo
        cout << b.root() << " ";
        int ultAltura = 1; // La altura del perfil que llevamos recorrida es la 1

        // Si los hijos del arbol no son vacíos los colocamos a la cola
        if (!b.left().empty())
            cola.push({ 2, b.left() });
        if (!b.right().empty())
            cola.push({ 2, b.right() });

        // Recorremos todos los elementos
        while (!cola.empty()) {
            int altura = cola.front().first;
            bintree<int> sub = cola.front().second;
            if (ultAltura < altura) {// Si hasta ahora no hemos guardado esa altura
                cout << sub.root() << " ";
                ++ultAltura;
            }
            // Si los hijos del arbol no son vacíos los colocamos a la cola
            if (!sub.left().empty())
                cola.push({ altura + 1, sub.left() });
            if (!sub.right().empty())
                cola.push({ altura + 1, sub.right() });
            // El elemento que ya hemos analizado lo sacamos de la cola
            cola.pop();
        }
    }
    cout << endl;
}

void resuelveCaso() {
    bintree<int> b = leerArbol(-1); // Leemos el arbol
    resolver(b); // Lo exploramos y escribimos el resultado en la función
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