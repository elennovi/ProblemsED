#pragma once
#include <algorithm>
#include <string>
#include "Horas.h" // Incluimos la clase implementada

// La clase película:
class Pelicula {
public: 
	Pelicula() {}
	Pelicula(Hora h, string t) : hora(h), titulo(t) {}
	Hora getHora() const { return hora; }
	string getTitulo() const { return titulo; }
	bool operator<(Pelicula const& p) const { // Los operadores para la función sort
		if (hora < p.hora) return true;
		else if (hora == p.hora && titulo < p.titulo) return true;
		else return false;
	}
private:
	Hora hora;
	string titulo;
};
inline istream& operator>>(istream& in, Pelicula& p) {
	Hora hora, duracion;
	char aux;
	string titulo;
	in >> hora >> duracion;
	in.get(aux);
	getline(in, titulo);
	try {
		p = Pelicula(hora + duracion, titulo);
	}
	catch (invalid_argument& ia) {
		throw invalid_argument("ERROR"); // Si da error la suma lanzamos una excepción
	}
	return in;
}
inline ostream& operator<<(ostream& out, Pelicula const& p) {
	out << p.getHora() << " " << p.getTitulo();
	return out;
}