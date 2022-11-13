// Elena Novillo Luceño
// A51

#include <iostream>
#include <fstream>
#include "bintree_eda.h"
using namespace std;
using pbi = pair<bool, int>;

pbi resolver(bintree<int> const& b) {
	if (b.empty()) return { true, 0 };
	else {
		pbi izquierda = resolver(b.left());
		pbi derecha = resolver(b.right());
		pbi act = { izquierda.first && derecha.first && abs(izquierda.second - derecha.second) <= 1,
					izquierda.second + derecha.second };
		if (b.root() % 2 == 0) act.second++;
		return act;
	}
}
void resuelveCaso() {
	bintree<int> b = leerArbol(-1);
	pbi sol = resolver(b);
	if (sol.first) cout << "SI";
	else cout << "NO";
	cout << endl;
}
int main() {
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
	int numCasos = 1; std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i) resuelveCaso();
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}