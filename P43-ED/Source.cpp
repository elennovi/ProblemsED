// Elena Novillo Luceño
// A51


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "treemap_eda.h"
using namespace std;

void resuelveCaso() {
    char aux;
    map<string, int> dic1; // Creamos el diccionario para almacenar las palabras
    string frase;
    // Leemos el diccionario inicial
    getline(cin, frase);
    stringstream extractor1(frase);
    string palabra;
    while (extractor1 >> palabra) {
        int numeroS;
        extractor1 >> numeroS;
        dic1.insert({palabra, numeroS});
    }
    // Leemos el diccionario con los cambios modificados
    getline(cin, frase);
    stringstream extractor2(frase);
    vector<string> aniadidos;
    vector<string> modificados;
    map<string, int> dic2; // El segundo diccionario
    while (extractor2 >> palabra) {
        int numeroS;
        extractor2 >> numeroS;
        dic2.insert({ palabra, numeroS });
    }
    for (auto d : dic2) {
        if (dic1.count(d.clave) && dic1[d.clave] != d.valor) { // Si estaba en el diccionario y se ha modificado
            modificados.push_back(d.clave); // Lo guardamos en los modificados
            dic1.erase(d.clave);  
        }
        else if (dic1.count(d.clave)) // Si no se ha modificado
            dic1.erase(d.clave);
        
        else if (!dic1.count(d.clave)) // Si no estaba es porque se ha introducido
            aniadidos.push_back(d.clave);
    }
    if (aniadidos.size() != 0 || modificados.size() != 0 || dic1.size() != 0) {
        // Primero mostramos los que hemos añadidos
        if (aniadidos.size() != 0) {
            cout << "+";
            for (auto e : aniadidos)
                cout << " " << e;
            cout << endl;
        }
        // Ahora mostramos los que hemos eliminado
        if (dic1.size() != 0) {
            cout << "-";
            for (auto d : dic1)
                cout << " " << d.clave;
            cout << endl;
        }
        // Por último los que se han modificado
        if (modificados.size() != 0) {
            cout << "*";
            for (auto e : modificados)
                cout << " " << e;
            cout << endl;
        }
    }
    else
        cout << "Sin cambios" << endl;
    cout << "---" << endl;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    int numCasos;
    std::cin >> numCasos;
    char aux;
    cin.get(aux);
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}