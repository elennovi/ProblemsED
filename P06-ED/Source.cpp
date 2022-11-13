// Elena Novillo Luceño
// A51


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stack> // La libreria con el tipo pila
using namespace std;

bool esCaracter(char c) {
    return c == '[' || c == ']' || c == '(' || c == ')' || c == '{' || c == '}';
}

bool seCierra(char top, char nuevo) { // Comprueba si se está cerrando un paréntesis/corchete/llaves
    if (top == '{' && nuevo == '}') return true; // se cierra una llave
    else if (top == '(' && nuevo == ')') return true; // se cierra un paréntesis
    else if (top == '[' && nuevo == ']') return true; // se cierra un corchete
    else return false; // de momento no se cierra
}

bool resolver(string linea) {
    stack<char> s;
    for (char c: linea) {
        if ((s.empty() || !seCierra(s.top(), c)) && esCaracter(c))
            s.push(c);
        else if (!s.empty() && seCierra(s.top(), c))
            s.pop();
    }
    return s.empty(); // Si al final está vacía significa que
    // se han cerrado todos los que estaban abiertos o bien que 
    // nunca se han abierto
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    string l;
    getline(cin, l);
    if (!std::cin)
        return false;
    if (resolver(l)) cout << "SI";
    else cout << "NO";
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


    while (resuelveCaso());


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}