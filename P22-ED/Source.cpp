// Elena Novillo Luceño
// A51

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stack> // La pila de la librería STL
using namespace std;

bool esPrincipio(string p) {
    return p == "<p>" || p == "<b>" || p == "<q>" || p == "<i>"; 
}

bool resolver(string linea, int& p, int& b, int& i, int& q) {
    stack<string> s;
    for (int it = 0; it < linea.length() - 4; it++) {
        if (linea[it] == '<') {
            string pi = linea.substr(it, 3); // <l>
            string f = linea.substr(it, 4); // </l>
            if (esPrincipio(pi)) s.push(pi);
            if (f == "</p>") {
                if (!s.empty() && s.top() == "<p>") p++, s.pop();
                else return false;
            }
            else if (f == "</b>") {
                if (!s.empty() && s.top() == "<b>") b++, s.pop();
                else return false;
            }
            else if (f == "</i>") {
                if (!s.empty() && s.top() == "<i>") i++, s.pop();
                else return false;
            }
            else if (f == "</q>") {
                if (!s.empty() && s.top() == "<q>") q++, s.pop();
                else return false;
            }
        }
    }
    return s.empty(); // Si está vacía entonces todos tienen pareja encontrada
}

bool resuelveCaso() {
    string linea;
    getline(cin, linea); // Leemos la linea
    if (!std::cin)
        return false;
    int p = 0, b = 0, i = 0, q = 0;
    if (resolver(linea, p, b, i, q)) // Si es correcto
        cout << "SI " << p << " " << b << " " << i << " " << q << endl;
    else // Si no es correcto
        cout << "NO" << endl;
    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif 


    while (resuelveCaso());
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}