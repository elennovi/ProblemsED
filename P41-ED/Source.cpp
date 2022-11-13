// Elena Novillo Luceño
// A51


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "treemap_eda.h"
using namespace std;

bool resuelveCaso() {
    int N;
    cin >> N;
    if (N == 0)
        return false;
    char aux;
    string nombre, resultado;;
    map<string, int> diccionario; // Creamos el diccionario
    for (int i = 0; i < N; i++) {
        cin.get(aux);
        getline(cin, nombre);
        cin >> resultado;
        int puntuacion = -1; // Suponemos que es incorrecta
        if (resultado == "CORRECTO") puntuacion = 1; // Si es correcta lo modificamos
        if (diccionario.count(nombre)) // Si al alumno le han corregido alguna prueba
            diccionario[nombre] = diccionario[nombre] + puntuacion;
        else
            diccionario.insert({nombre, puntuacion});
        if (diccionario.at(nombre) == 0)  // Si la puntuación es 0
            diccionario.erase(nombre); // lo borramos de la lista
    }
    for (auto d : diccionario) // Recorremos todos los elementos
        cout << d.clave << ", " << d.valor << endl;
    
    cout << "---" << endl;
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
