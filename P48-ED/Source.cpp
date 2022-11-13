// Elena Novillo Luceño
// A51


#include "Autoescuela.h"

bool resuelveCaso() {
    string operacion;
    cin >> operacion;
    if (!std::cin)
        return false;
    autoescuela au;
    while (operacion != "FIN") {
        if (operacion == "alta") {
            string a, p;
            cin >> a >> p;
            au.alta(a, p);
        }
        else if(operacion == "es_alumno") {
            string a, p;
            cin >> a >> p;
            try {
                bool esAlumno = au.es_alumno(a, p);
                if (esAlumno)
                    cout << a << " es alumno de " << p << endl;
                else
                    cout << a << " no es alumno de " << p << endl;
            }
            catch (exception& ex) {
                cout << "ERROR" << endl;
            }
        }
        else if (operacion == "examen") {
            string p;
            int n;
            cin >> p >> n;
            try {
                vector<string> v = au.examen(p, n);
                cout << "Alumnos de " << p << " a examen:" << endl;
                for (string a : v)
                    cout << a << endl;
            }
            catch (exception& ex) {
                cout << "ERROR" << endl;
            }
        }
        else if (operacion == "actualizar") {
            string a;
            int n;
            cin >> a >> n;
            try {
                au.actualizar(a, n);
            }
            catch (exception& ex) {
                cout << "ERROR" << endl;
            }
        }
        else if (operacion == "puntuacion") {
            string a;
            cin >> a;
            try {
                int n = au.puntuacion(a);
                cout << "Puntuacion de " << a << ": " << n << endl;
            }
            catch (exception& ex) {
                cout << "ERROR" << endl;
            }
        }
        else if (operacion == "aprobar") {
            string a;
            cin >> a;
            try {
                au.aprobar(a);
            }
            catch (exception& ex) {
                cout << "ERROR" << endl;
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