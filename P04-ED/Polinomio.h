#pragma once
#include <cstddef>
#include <utility>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

using p = pair<int, int>;

class comparaDatos {
public:
	bool operator()(p const& m1, p const& m2) const {
		return m1.second < m2.second;
	}
};

class Polinomio {
public:
	Polinomio() {} // El constructor sin parámetros
	void insert(p const& nuevoE) { // Se inserta ordenadamente
		bool encontrado = binary_search(v.begin(), v.end(), nuevoE, comparaDatos());
		if (!encontrado) // Si el elemento no se encuentra en el vector
			desplaza(nuevoE);
		else // si está en el vector solo sumamos los coeficientes 
			(*lower_bound(v.begin(), v.end(), nuevoE, comparaDatos())).first += nuevoE.first;
	}
	int64_t resolver(int x) { // Comprobar función
		int64_t resultado = 0;
		int64_t calculaXs = 1;
		int expo = 0;
		for (int i = 0; i < v.size(); i++) {
			for (int j = expo; j < v[i].second; j++) // Calcula la diferencia de x's que hay en 
				// entre el último exponente calculado
				calculaXs *= x; 
			expo = v[i].second; 
			resultado += v[i].first * calculaXs;
		}
		return resultado;
	}
private:
	vector<p> v; // el vector de pares enteros
	void desplaza(p const& nuevoE) { // Desplaza los elementos y coloca el nuevo elemento
		v.push_back(nuevoE); // El nuevo elemento al final de la lista
		int i = v.size() - 1;
		while (i > 0 && v[i - 1].second > v[i].second) {
			swap(v[i], v[i - 1]); // Intercambiamos los elementos
			i--;
		}
	}
};

