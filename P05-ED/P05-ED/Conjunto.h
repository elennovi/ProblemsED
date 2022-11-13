#pragma once
// Elena Novillo Luce�o
// A51
#include <iostream>
#include <stdexcept>
#include <algorithm>
using namespace std;

template <typename T>
class Conjunto {
public:
	Conjunto(int c): cont(0), cantidad(c), a(new T[cantidad]){}
	~Conjunto() { delete[] a; }
	void insert(T const& nuevoE) {
		bool existe = binary_search(a, a + cont, nuevoE); // Busca el elemento en el array dinamico
		if (!existe) {
			try {
				if (consultaMinimo() < nuevoE) eliminaMinimo(nuevoE); // Se elimina el anterior m�nimo
			}
			catch (invalid_argument& ia){ 
				a[cont] = nuevoE; // Insertamos el elemento a la derecha del todo
				cont++;
				desplaza(); // y lo desplazamos hasta que vuelva a estar ordenado el vector
			}
		}
	}
	T getElemEn(int posi) {
		return a[posi];
	}
	int getCont() {
		return cont;
	}
private:
	int cont;
	int cantidad;
	T* a; // El array dinamico del tipo 
	T consultaMinimo() {
		if (cont < cantidad) throw invalid_argument("ERROR"); 
		return a[0]; // Si hay m�nimo siempre ser� el primer elmento del array
	}
	void eliminaMinimo(T const& nuevoE) {
		a[0] = nuevoE; // Se sustituye el m�nimo por el nuevo elemento
		for (int i = 1; i < cont && a[i] < a[i - 1]; i++) // Se desplaza el elemento hasta la
			swap(a[i], a[i - 1]); // posici�n que le corresponde
	}
	void desplaza() {
		for (int i = cont - 1; i > 0 && a[i] < a[i - 1]; i--)
			swap(a[i], a[i - 1]);
	}
};

template <typename T>
inline ostream& operator<<(ostream& out, Conjunto<T>& c) {
	for (int i = 0; i < c.getCont(); i++)
		out << c.getElemEn(i) << " ";
	return out;
}