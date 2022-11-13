// Elena Novillo Luceño
// A51


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <map>
using namespace std;

void resuelveCaso() {
    // Para guardar los equipos necesitaremos dos mapas, uno para guardar los
    // equipos y la cantidad de problemas que han resuelto erróneamente
    unordered_map<string, unordered_map<string, int>> problemasNoResueltos;
    // La clave: el nombre del equipo
    // El valor: un unordered_map con los problemas que no se hayan resuelto
    // con éxito como clave y el número de intentos que han hecho para ese problema en con-
    // creto como valor

    // Y otro con los equipos y la cantidad de problemas que se han resuelto
    // correcto
    unordered_map<string, pair<int, unordered_set<string>>> problemasResueltos;
    // La clave: el nombre del equipo
    // El valor: un unordered_set con los problemas que se hayan resuelto con
    // éxito y el tiempo que ha tardado en resolverlos


    string nombre;
    cin >> nombre;
    while (nombre != "FIN") {
        string problema;
        cin >> problema;
        int tiempo;
        cin >> tiempo;
        string nota;
        cin >> nota;
        // Si ha solucionado correctamente el problema
        if (nota == "AC") {
            
            
        }
        // si no se ha solucionado correctamente el problema
        else {
            
        }
        cin >> nombre;
    }

    // Mostramos los equipos que han intentado resolver algún problema sin éxito
    for (auto e1 : problemasNoResueltos)
        if (problemasResueltos.find(e1.first) == problemasResueltos.end())
            cout << e1.first << " 0 0" << endl;
    cout << "---" << endl;
}

int main() {
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