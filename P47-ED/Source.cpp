// Elena Novillo Luceño
// A51


#include "CarnetPuntos.h"
#include <fstream>

bool resuelveCaso() {
    string operacion;
    cin >> operacion;
    if (!std::cin)
        return false;
    
    carnet_puntos carnets;
    while (operacion != "FIN") {
        if (operacion == "nuevo") {
            dni DNI;
            cin >> DNI;
            try {
                carnets.nuevo(DNI);
            }
            // Si se produce error
            catch (exception& ex) {
                cout << "ERROR: " << ex.what() << endl;
            }
        }
        else if (operacion == "cuantos_con_puntos") {
            puntos ptos;
            cin >> ptos;
            try {
                int conductores = carnets.cuantos_con_puntos(ptos);
                cout << "Con " << ptos << " puntos hay " << conductores << endl;
            }
            catch (exception & ex) {
                cout << "ERROR: " << ex.what() << endl;
            }
        }
        else if (operacion == "quitar") {
            dni DNI;
            puntos ptos;
            cin >> DNI >> ptos;
            try {
                carnets.quitar(DNI, ptos);
            }
            catch (exception & ex) {
                cout << "ERROR: " << ex.what() << endl;
            }
        }
        else if (operacion == "recuperar") {
            dni DNI;
            puntos ptos;
            cin >> DNI >> ptos;
            try {
                carnets.recuperar(DNI, ptos);
            }
            catch (exception& ex) {
                cout << "ERROR: " << ex.what() << endl;
            }
        }
        else if (operacion == "consultar") {
            dni DNI;
            cin >> DNI;
            try {
                puntos ptos = carnets.consultar(DNI);
                cout << "Puntos de " << DNI << ": " << ptos << endl;
            }
            catch (exception& ex) {
                cout << "ERROR: " << ex.what() << endl;
            }
        }
        else if (operacion == "lista_por_puntos") {
            puntos ptos;
            cin >> ptos;
            try {
                list<dni> conductores = carnets.lista_por_puntos(ptos);
                cout << "Tienen " << ptos << " puntos:";
                for (dni d : conductores)
                    cout << " " << d;
                cout << endl;
            }
            catch (exception& ex) {
                cout << "ERROR: " << ex.what() << endl;
            }
        }
        cin >> operacion;
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