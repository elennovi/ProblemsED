
// Nombre del alumno: Elena Novillo Luceño
// Usuario del juez de clase: A51

#include <iostream>
#include <stack>
#include <fstream>
using namespace std;

bool resuelveCaso() {
	int nElem; std::cin >> nElem;
	if (nElem == 0) return false;
	stack<pair<int, int>> s; // creamos la pila
	int e;
	for (int i = 0; i < nElem; i++) {
		cin >> e;
		if (s.empty() || s.top().first > e)
			cout << 0 << " ";
		else {
			while (!s.empty() && s.top().first <= e) s.pop();
			if (!s.empty())
				cout << i - s.top().second - 1 << " ";
			else
				cout << i << " ";
		}
		s.push({ e, i });
	}
	cout << endl;
	return true;
}
int main() {
#ifndef DOMJUDGE

	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
	while (resuelveCaso()) {} //Resolvemos todos los casos
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}