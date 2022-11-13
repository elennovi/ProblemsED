// Elena Novillo Luceño
// A51


#include <iostream>
#include <iomanip>
#include <fstream>
#include <list> // La libreria de la stl para utilizar la list
using namespace std;

template <class T>
T Mysearch(T const& ini1, T const& fin1, T const& ini2, T const& fin2) {
    T i1 = ini1;
    T i2 = ini2;
    // La variable que guarda la primera aparición de la secuencia
    T primer = fin1;
    // El bucle que recorre la lista
    while (i1 != fin1 && i2 != fin2) {
        // Si se cumple la secuencia y es el primer elemento de la secuencia
        if (*i1 == *i2 && primer == fin1) {
            // Guardamos el iterador que apunta al principio del iterador
            // en la lista 1
            primer = i1;
            ++i2;
        }
        // Si pertenece a la secuencia pero no es el primero
        else if (*i1 == *i2)
            ++i2;
        // Si no se cumple la secuencia
        else {
            i2 = ini2;
            // Si el elemento en el que ha fallado es el primero de la
            // secuensia
            if (*i2 == *i1) {
                primer = i1;
                ++i2;
            }
            // Si el elemento en el que ha fallado no es el primero 
            // en la secuencia
            else
                primer = fin1;
        }
        ++i1;
    }
    // Si no ha terminado de recorrerse correctamente
    if (i2 != fin2)
        return fin1;
    return primer;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int numL1, numL2;
    cin >> numL1 >> numL2;
    if (numL1 == 0 && numL2 == 0)
        return false;
    list<int> l1, l2;
    int elem;
    // Leemos los elementos de la primera lista
    for (int i = 0; i < numL1; i++) {
        cin >> elem;
        l1.push_back(elem);
    }
    // Leemos los elementos de la segunda lista (la secuencia)
    for (int i = 0; i < numL2; i++) {
        cin >> elem;
        l2.push_back(elem);
    }

    // Ahora resolvemos el problema utilizando la funcion MySearch que hemos
    // creado
    auto it = Mysearch(l1.begin(), l1.end(), l2.begin(), l2.end());
    // Hasta que ya no quede la secuencia
    while (it != l1.end()) {
        auto i1 = it;
        auto i2 = l2.begin();
        while (i2 != l2.end()) {
            i1 = l1.erase(i1);
            // Ahora el iterador apunta al siguiente elemento
            ++i2;
        }
        it = Mysearch(l1.begin(), l1.end(), l2.begin(), l2.end());
    }

    // Mostramos la lista que nos ha quedado al eliminar todos los patrones
    // de l1
    for (auto e : l1)
        cout << e << " ";
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
