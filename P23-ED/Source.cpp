// Elena Novillo Luceño
// A51

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <list>
using namespace std;

bool esEspecial(char c) {
    return c == '*' || c == '+' || c == '-' || c == '3';
}

void escribir(string linea, list<char>& l) {
    auto it = l.begin();
    for (int i = 0; i < linea.length(); i++) {
        if (!esEspecial(linea[i])) { // Si no es uno de los caracteres erróneos
            // lo insertamos
            if (it == l.begin()) l.push_front(linea[i]);
            else if (it == l.end()) l.push_back(linea[i]);
            else l.insert(it, linea[i]);

        }
        else {
            if (linea[i] == '-') // El iterador tiene que ser l.begin()
                it = l.begin();
            else if (linea[i] == '+') // El iterador tiene que ir al final
                it = l.end();
            else if (linea[i] == '*') {
                if (it != l.end()) ++it; // Comprobamos que el elemento no pase
                // del final de la lista
            }
            else if (linea[i] == '3') { // Tiene que borrar la posición en la que estamos
                if (it != l.end()) {
                    auto aux = it;
                    ++it;
                    l.erase(aux);
                }
            }
        }
    }
}

void mostrar(list<char> const& l) {
    if (!l.empty()) // Solo recorremos la lista si no está vacía
        for (char c: l) cout << c;
    cout << endl;
}

bool resuelveCaso() {
    list<char> l; // Creamos una lista de caracteres que contendrá el mensaje
    // final
    string linea;
    getline(cin, linea); // Extraemos la linea
    if (!std::cin)
        return false;
    escribir(linea, l); // Escribimos en la lista la solución
    mostrar(l); // Mostramos la linea con la solución
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