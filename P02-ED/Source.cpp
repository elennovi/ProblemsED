// Elena Novillo Luceño
// A51

#include <fstream>
#include "Pelicula.h"

bool resuelveCaso() {
    int numPelis;
    cin >> numPelis;
    if (numPelis == 0)
        return false;
    vector <Pelicula> cartelera(numPelis);
    try { // Hacemos un try porque puede dar error la lectura de los datos
        for (Pelicula& p : cartelera)
            cin >> p; 
        sort(cartelera.begin(), cartelera.end());
        for (Pelicula p : cartelera)
            cout << p << endl;
        cout << "---" << endl;
    }
    catch (invalid_argument& ia) { cout << ia.what() << endl; }
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 

    while (resuelveCaso());

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
