// Elena Novillo Luceño
// A51


#include <iostream>
#include <iomanip>
#include <fstream>
#include <deque> // La implementación de deque de la libreria STL
#include <stack> // La implementación de stack de la librería STL
#include <string>
using namespace std;

bool esVocal(char l) {
    return l == 'a' || l == 'e' || l == 'i' || l == 'o' || l == 'u'
        || l == 'A' || l == 'E' || l == 'I' || l == 'O' || l == 'U';
}

bool resuelveCaso() {
    string frase;
    getline(cin, frase); // Guardamos la frase
    if (!cin)
        return false;

    // Para conseguir X' a partir de X''---------------
    stack<char> s1, s2; // Los stacks que utilizaremos para guardar las dos
    // mitades
    int i = 0;
    for (char c: frase) {
        if (i % 2 == 0) s1.push(c); // Las posiciones pares al 
        // primer stack
        else s2.push(c); // Las posiciones impares al segundo stack
        i++;
    }
    deque<char> d1;
    // Volcamos la pila 1 utilizando el push_front() mientras vaciamos la
    // pila
    while (!s1.empty()){
        d1.push_front(s1.top());
        s1.pop();
    }
    // Volcamos la pila 2 utilizando el push_back() mientras vaciamos
    // la pila
    while (!s2.empty()) {
        d1.push_back(s2.top());
        s2.pop();
    }

    // Para conseguir X a partir de X'---------------
    while (!d1.empty()) {
        // Si no es vocal la guardamos en una pila auxiliar
        if (!esVocal(d1.front())) s1.push(d1.front());
        else {
            while (!s1.empty()) {
                cout << s1.top();
                s1.pop();
            }
            cout << d1.front();
        }
        d1.pop_front();
    }
    // Si la pila sigue llena la vaciamos
    while (!s1.empty()) {
        cout << s1.top();
        s1.pop();
    }
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
