// Elena Novillo Luceño
// A51


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "treemap_eda.h"
using namespace std;

// La clave es el string
// El valor es el vector con las veces que ha aparecido en cada linea

bool resuelveCaso() {
    int numLineas;
    cin >> numLineas;
    if (numLineas == 0)
        return false;
    map<string, vector<int>> dic;
    int i = 0;
    char aux;
    cin.get(aux);
    while (i < numLineas) {
        string palabra;
        cin >> palabra;
        // transformamos la palabra en minúscula
        transform(palabra.begin(), palabra.end(), palabra.begin(), ::tolower);
        if (palabra.length() > 2) { // Solo contamos las palabras con tamaño mayor que 2
            if (dic.count(palabra)) { // Si la palabra ya está en el diccionario
                vector<int> valor = dic.at(palabra);
                if (valor[valor.size() - 1] != i + 1) // Si la ultima fila insertada no es la actual
                    dic[palabra].push_back(i + 1); // metemos la nueva linea en la que se encuentra
            }
            else
                dic.insert({ palabra, {i + 1} });
        }
        cin.get(aux); // Leemos el espacio para comprobar si hay que pasar
        // de linea o no
        if (aux == '\n') // si es un salto de linea
            i++; // pasamos de linea
    }
    for (auto d : dic) { // Recorremos los elementos que tenemos en el diccionario
        cout << d.clave; // Mostramos la clave
        for (auto e : d.valor)
            cout << " " << e;
        cout << endl;
    }
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
