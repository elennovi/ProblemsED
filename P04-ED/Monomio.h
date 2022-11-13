#pragma once
#include <iostream>
using namespace std;

using lli = long long int;

class Monomio {
public:
	Monomio() {}
	Monomio(lli c, lli e) : coef(c), expo(e), valor(0) {}
	lli getCoef() const { return coef; }
	lli getExpo() const { return expo; }
	lli getValor() const { return valor; }
	void setValor(lli v) { valor = v; }
	bool operator==(Monomio const& m2) const {
		if (m2.expo == expo) return true; // Identificamos a un monomio por su 
		// exponente
		else return false;
	}
	bool operator<(Monomio const& m2) const {
		if (expo < m2.expo) return true; 
		else return false;
	}
	Monomio& operator=(Monomio const& m2) {
		if (this != &m2) { // Si no son iguales
			coef = m2.coef;
			expo = m2.expo;
			valor = m2.valor;
		}
		return *this;
	}
	void addCoef(lli num) {
		coef += num;
	}
private:
	lli coef, expo, valor;
};