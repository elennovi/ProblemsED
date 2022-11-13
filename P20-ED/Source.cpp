// Elena Novillo Luceño
// A51


#include <iostream>
#include <iomanip>
#include <fstream>
#include <list> // Utilizamos la lista de la STL
using namespace std;

void duplicaNodos(list<int>& l) {
    auto it = l.begin();
    int numElems = l.size();
    for (int i = 0; i < numElems; i++) {
        l.push_front(*it);
        l.push_front(*it);
        auto aux = ++it;
        l.erase(--it);
        it = aux;
    }
}

void mostrar(list<int> const& l) {
    for (int elem : l) cout << elem << " ";
    cout << endl;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int e;
    cin >> e; // Leemos el primer elemento de la lista
    if (!std::cin)
        return false;
    list<int> l;
    while (e != 0) {
        l.push_front(e);
        cin >> e;
    }
    // Duplicamos los nodos
    duplicaNodos(l);
    // Mostramos los elementos desde el primero hasta el último
    mostrar(l);
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