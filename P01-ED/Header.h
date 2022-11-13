// Elena Novillo Luceño
// A51
#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

class Hora {
public:
	Hora() {};
	Hora(int h, int m, int s) : horas(h), minutos(m), segundos(s) {
		if (h >= MAX_HORAS || m >= MAX_MIN_SEC || s >= MAX_MIN_SEC || h < 0 || m < 0 || s < 0)
			throw invalid_argument("ERROR"); // Lanzamos una excepción si
		// encontramos un argumento inválido
	}
	Hora& operator=(Hora const& h2) {
		if (this != &h2) { // Si no son iguales los sustituimos correctamente
			horas = h2.horas;
			minutos = h2.minutos;
			segundos = h2.segundos;
		}
		return *this;
	}
	int getHoras() const { return horas; }
	int getMinutos() const { return minutos; }
	int getSegundos() const { return segundos; }
	Hora proximaHora(vector <Hora> const hs, bool& encontrado) const {
		int i = 0;
		while (i < hs.size() && !encontrado) {
			if (*this <= hs[i]) {
				encontrado = true;
				return hs[i];
			}
			i++;
		}
		return Hora();
	}
	bool operator<(Hora const& h2) const {
		if (horas < h2.horas) return true;
		else if (horas == h2.horas && minutos < h2.minutos) return true;
		else if (horas == h2.horas && minutos == h2.minutos && segundos < h2.segundos) return true;
		else return false;
	}
	bool operator==(Hora const& h2) const {
		return horas == h2.horas && minutos == h2.minutos && segundos == h2.segundos;
	}
	bool operator<=(Hora const& h2) const {
		return *this == h2 || *this < h2;
	}
private:
	int horas, minutos, segundos;
	const int MAX_HORAS = 24; // Máximo de horas que pueden aparecer
	const int MAX_MIN_SEC = 60; // Máximo de minutos y segundos que pueden aparecer
};

inline istream& operator>>(istream& in, Hora& h) {
	int horas, minutos, segundos;
	char aux;
	in >> horas;
	in.get(aux);
	in >> minutos;
	in.get(aux);
	in >> segundos;
	h = Hora(horas, minutos, segundos);
	return in;
}

inline ostream& operator<<(ostream& out, Hora& h) {
	if (h.getHoras() < 10) out << 0;
	out << h.getHoras() << ":";
	if (h.getMinutos() < 10) out << 0;
	out << h.getMinutos() << ":";
	if (h.getSegundos() < 10) out << 0;
	out << h.getSegundos();
	return out;
}