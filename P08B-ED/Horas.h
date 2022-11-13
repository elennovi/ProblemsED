// Elena Novillo Luceño
// A51
#pragma once

#include <iostream>
#include <stdexcept>
#include <iomanip>
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
	Hora proximaHora(vector <Hora> const& hs, bool& encontrado) const {
		auto pos = lower_bound(hs.begin(), hs.end(), *this);
		if (pos != hs.end()) {
			encontrado = true;
			return *pos;
		}
		else return *this;
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
	Hora operator+(Hora const& h2) {
		int h, m, s;
		int cHoras = 0, cMins = 0;
		// Para los segundos
		if (h2.segundos + segundos >= MAX_MIN_SEC) {
			cMins++; // Un minuto más si se excede de 60
			s = (h2.segundos + segundos) % MAX_MIN_SEC; // El valor es el resto de dividir
			// entre 60
		}
		else s = h2.segundos + segundos; 

		// Para los minutos
		if (h2.minutos + minutos + cMins >= MAX_MIN_SEC) {
			cHoras++;
			m = (h2.minutos + minutos + cMins) % MAX_MIN_SEC;
		}
		else m = h2.minutos + minutos + cMins;

		// Para las horas
		if (h2.horas + horas + cHoras >= MAX_HORAS) throw invalid_argument("ERROR");
		else h = h2.horas + horas + cHoras; 

		return Hora(h, m, s); // Devolvemos una nueva hora con la suma de ambas
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

inline ostream& operator<<(ostream& out, Hora const& h) {
	out << setw(2) << setfill('0') << h.getHoras() << ":";
	out << setw(2) << setfill('0') << h.getMinutos() << ":";
	out << setw(2) << setfill('0') << h.getSegundos();
	return out;
}