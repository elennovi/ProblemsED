// Elena Novillo Luceño
// A51

#pragma once
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

class Complejo {
public: 
	Complejo() {}
	Complejo(float r, float i) : pReal(r), pImag(i) {}
	float getReal() const { return pReal; }
	float getImag() const { return pImag; }
	float mod() const {
		return (float) sqrt(pReal * pReal + pImag * pImag);
	}
	Complejo operator+(Complejo const& c2) const {
		return Complejo(pReal + c2.pReal, pImag + c2.pImag);
	}
	Complejo operator*(Complejo const& c2) const {
		return Complejo(pReal * c2.pReal - pImag * c2.pImag, pReal * c2.pImag + c2.pReal * pImag);
	}
private:
	float pReal, pImag; // Las partes reales e imaginaria del número
};

inline istream& operator>>(istream& in, Complejo& c) {
	float a, b;
	in >> a >> b;
	c = Complejo(a, b);
	return in;
}