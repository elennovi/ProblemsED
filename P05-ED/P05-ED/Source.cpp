// Elena Novillo Luceño
// A51

#include <iomanip>
#include <fstream>
#include "Conjunto.h"

bool resuelveCaso() {
    string letra;
    cin >> letra;
    if (!std::cin)
        return false;
    int numElem;
    cin >> numElem;
    if (letra == "N") {
        Conjunto<int> c(numElem);
        int e;
        cin >> e;
        while (e != -1) {
            c.insert(e);
            cin >> e;
        }
        cout << c;
    }
    else {
        Conjunto<string> c(numElem);
        string e;
        cin >> e;
        while (e != "FIN") {
            c.insert(e);
            cin >> e;
        }
        cout << c;
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