// Elena Novillo Luceño
// A51


#include <iostream>
#include <iomanip>
#include <fstream>
#include <unordered_map>
using namespace std;

void resuelveCaso() {
    int numCaps;
    cin >> numCaps;
    unordered_map<int, int> map;
    // Siempre va a ser mínimo 1
    int maxSinRep = 1;
    int actSinRep = 1;
    int ultimaPosRepetido = 0;
    int elem;
    cin >> elem;
    // Inserta siempre el primer elemento para que no esté vacía
    map.insert({ elem, 0 });
    for (int i = 1; i < numCaps; i++) {
        // Leemos el siguiente capítulo
        cin >> elem;
        // Comprobamos si el elemento se encuentra en el mapa
        auto it = map.find(elem);
        if (it != map.end()) { // Si ya estaba
            // Comprobamos si 
            actSinRep = i - max(ultimaPosRepetido, it->second);
            ultimaPosRepetido = max(ultimaPosRepetido, it->second); // Solo se puede colocar a partir de esta posición
            // pues antes se han producido repeticiones
            it->second = i; // Modificamos la posición en la que apareció
            // pues ha vuelto a aparecer
        }
        else {
            actSinRep++;
            map.insert({ elem, i });
        }
        if (actSinRep > maxSinRep)
            maxSinRep = actSinRep;
    }
    cout << maxSinRep << endl;
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