// Elena Novillo Luceño
// A51


#include <iostream>
#include <iomanip>
#include <fstream>
#include <deque> // La implementación de deque de la libreria STL
#include <queue>
using namespace std;

bool resuelveCaso() {
    int nelems;
    cin >> nelems;
    if (nelems == 0)
        return false;
    queue<int> q; // La cola que utilizamos
    int e;
    for (int i = 0; i < nelems; i++) { // Guardamos los datos en la
        // cola
        cin >> e;
        q.push(e);
    }
    deque<int> d; // Utilizamos una deque para poder hacer push
    // de los elementos al principio y al final de la lista
    for (int i = 0; i < nelems; i++) {
        // Para los números negativos los ponemos al principio
        if (q.front() < 0) d.push_front(q.front());
        // Para los números positivos los ponemos al final
        else d.push_back(q.front());
        // Borramos los elementos de la queue inicial
        q.pop();
    }
    for (int i = 0; i < nelems; i++) { // Guardamos uno a uno
        // los elementos de la deque ya ordenados en la queue
        q.push(d.front());
        d.pop_front(); 
    }
    for (int i = 0; i < nelems; i++) { // Mostramos los elementos
        // de la lista una vez ordenados
        cout << q.front() << " ";
        q.pop();
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
